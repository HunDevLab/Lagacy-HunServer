#include "stdafx.h"
#include "cIocpManager.h"



cIocpManager::cIocpManager()
{
	mNetworkSession = cNetworkSession::getInstance();
	mClientManager = cClientManager::getInstance();
	mPacketController = cPacketController::getInstance();
}


cIocpManager::~cIocpManager()
{
	
}

bool cIocpManager::Begin()
{
	mNetworkSession->Initialize();
	mCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);

	if (FALSE == mClientManager->InitailizeClient())
	{
		return FALSE;
	}

	if (FALSE == ResistWorkerThread())
	{
		return FALSE;
	}
	if (FALSE == ResistAcceptThread())
	{
		return FALSE;
	}
	return TRUE;
}
void cIocpManager::End()
{
	delete mClientManager;
	delete mNetworkSession;
	delete mPacketController;
	for (auto workerThread : mWorkerThread)
	{
		workerThread->join();
	}
	mAcceptThread->join();
	CloseHandle(mCompletionPort);
	WSACleanup();
}
bool cIocpManager::ResistWorkerThread()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	int threadCount = systemInfo.dwNumberOfProcessors * 2;
	for (int i = 0; i < threadCount; ++i)
	{
		mWorkerThread.push_back(new std::thread{std::mem_fun(&cIocpManager::WorkerThread), this});
		std::cout << i + 1 << " ";
		cLog::LogMessage("WORKER THREAD CREATE ...");
	}
	if (mWorkerThread.size() != threadCount)
	{
		cLog::LogMessage("WORKER THREAD CREATE FAILURE ...");
		return FALSE;
	}
	cLog::LogMessage("WORKER THREAD CREATE ... [Success]");
	return TRUE;
}
bool cIocpManager::ResistAcceptThread()
{
	mAcceptThread = new std::thread{ std::mem_fun(&cIocpManager::AcceptThread), this };
	if (mAcceptThread == nullptr)
	{
		cLog::LogMessage("ACCEPT THREAD CREATE FAILURE ...");
		return FALSE;
	}
	cLog::LogMessage("ACCEPT THREAD CREATE ... [Success]");
	return TRUE;
}
void cIocpManager::WorkerThread()
{
	DWORD ioSize;
	int completionKey;
	OverlappedEx *overlapped;

	while (true) {
		int ret = GetQueuedCompletionStatus(mCompletionPort, &ioSize, (PULONG)&completionKey, reinterpret_cast<LPOVERLAPPED *>(&overlapped), INFINITE);
		//std::cout << "completion Key : "<< completionKey << std::endl;
		auto player = mClientManager->FindPlayerById(completionKey);
		
		
		//ioSize �� ����� ��
		if (ret == 0 || ioSize == 0) {
			// �ش��ϴ� �÷��̾ ã�Ƽ� vector���� ����
			gLock.lock();
			mClientManager->RemovePlayer(player->GetId());
			closesocket(player->GetSocket());
			gLock.unlock();
			continue;
		}

		if (overlapped->mIoType == IOType::IO_RECV) {
			// ���ú� ������, ��Ŷ ���� ��������
			int rest = ioSize;
			char* buf = overlapped->IOCPbuf;

			while (0 < rest) {
				if (0 == overlapped->mCurrPacketSize)
				{
					overlapped->mCurrPacketSize = buf[0];
				}
				// required ��Ŷ ������ �ʼ��� �ʿ��� ������.
				int required = overlapped->mCurrPacketSize - overlapped->mPrevReceived;
				if (rest >= required) {  // ��Ŷ ���� ����
					memcpy(overlapped->mPacketBuf + overlapped->mPrevReceived, buf, required);
					mPacketController->ProcessPacket(completionKey, overlapped->mPacketBuf);
					
					// ��Ŷ ����� �ʱ�ȭ�Ѵ�.
					overlapped->mCurrPacketSize = 0;
					overlapped->mPrevReceived= 0;

					// ���۸� ���δ�.
					buf += required;
					
					// �ʿ��� ������ ��ŭ �ڸ���.
					rest -= required;
				}
				else { // ��Ŷ�� �ϼ��ϱ⿡�� ����Ÿ�� ����
					memcpy(overlapped->mPacketBuf + overlapped->mPrevReceived, buf, rest);
					// ��Ŷ�� ���ۿ� ����
					overlapped->mPrevReceived += rest;
					// ���μ��� ������ �ʱ�ȭ
					rest = 0;
				}
			} // ��Ŷ ���� while ����
			DWORD recv_flag = 0;
			int ret = WSARecv(player->GetSocket(),
				player->GetRecvOverExWsabuf(), 1, NULL, &recv_flag,
				player->GetRecvOverExOverlapped(), NULL);
			if (ret) {	// WSAENOTSOCK
				int err_code = WSAGetLastError();
				if (err_code != ERROR_IO_PENDING) {

					cLog::ErrorDisplay("Recv on workerthread\n", err_code);
				}
			}
		}
		else if (overlapped->mIoType == IOType::IO_SEND) {
			delete overlapped;
		}
		else if (overlapped->mIoType == IOType::IO_POST) {
			cEventManager* manager = cEventManager::getInstance();
			manager->ProcessEvent(completionKey, overlapped);
		}
		else {
			printf("Error invalid overlapped\n");
			exit(-1);
		}
	}
}
void cIocpManager::AcceptThread()
{
	// ��Ʈ��ũ �ʱ�ȭ, bind, Listen
	mNetworkSession->Begin();
	while (true) {
		int ret = mNetworkSession->Accept();
		if (ret == FALSE)
		{
			exit(1);
		}
		int playerId = mClientManager->SetConnectId();
		if (playerId == -1) {
			cLog::ErrorDisplay("������� �ʰ�");
		}
		mClientManager->AddPlayer(playerId, mNetworkSession->GetClientSocket());
		auto player = mClientManager->FindPlayerById(playerId);
		player->SetXPos(0.0f);
		player->SetYPos(0.0f);
		player->SetZPos(0.0f);
		player->SetHp(1000);
		std::cout << "�÷��̾� ��밡�� ���� : " << player->GetIsUse() << std::endl;
		std::cout << "�÷��̾� ID" << player->GetId() << std::endl;
		
		// IOCP ����
	
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(mNetworkSession->GetClientSocket()),
			mCompletionPort, playerId, 0);
		// ���� Recvȣ��
		unsigned long recv_flag = 0;
		ret = WSARecv(mNetworkSession->GetClientSocket(),
			player->GetRecvOverExWsabuf(), 1, NULL, &recv_flag,
			player->GetRecvOverExOverlapped(), NULL);
		
		if (ret) {
			// WSAENOTSOCK
			int err_code = WSAGetLastError();
			if (err_code != ERROR_IO_PENDING)
				printf("Recv Error [%d]\n", err_code);
		}
		auto playerList = mClientManager->GetPlayerList();
		/*for (auto iter = playerList.begin(); iter != playerList.end(); ++iter) {
			if ((*iter)->GetIsUse() == true) {
				if ((*iter)->GetId() != playerId) {
					mPacketController->SendConnectPlayer(playerId, (*iter)->GetId());
				}
			}
		}*/
		int userCount = mClientManager->GetUserCount();
		for (int i = 0; i < userCount; ++i) {
			for (int j = 0; j < userCount; ++j) {
				if (i != j) {
					mPacketController->SendConnectPlayer(i, j);
				}
			}
		}
	}

	closesocket(mNetworkSession->GetListenSocket());
}
