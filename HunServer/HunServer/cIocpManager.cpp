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
		
		
		//ioSize 가 비었을 때
		if (ret == 0 || ioSize == 0) {
			// 해당하는 플레이어를 찾아서 vector에서 삭제
			gLock.lock();
			mClientManager->RemovePlayer(player->GetId());
			closesocket(player->GetSocket());
			gLock.unlock();
			continue;
		}

		if (overlapped->mIoType == IOType::IO_RECV) {
			// 리시브 했을때, 패킷 조립 가능한지
			int rest = ioSize;
			char* buf = overlapped->IOCPbuf;

			while (0 < rest) {
				if (0 == overlapped->mCurrPacketSize)
				{
					overlapped->mCurrPacketSize = buf[0];
				}
				// required 패킷 조립에 필수로 필요한 사이즈.
				int required = overlapped->mCurrPacketSize - overlapped->mPrevReceived;
				if (rest >= required) {  // 패킷 제작 가능
					memcpy(overlapped->mPacketBuf + overlapped->mPrevReceived, buf, required);
					mPacketController->ProcessPacket(completionKey, overlapped->mPacketBuf);
					
					// 패킷 사이즈를 초기화한다.
					overlapped->mCurrPacketSize = 0;
					overlapped->mPrevReceived= 0;

					// 버퍼를 붙인다.
					buf += required;
					
					// 필요한 데이터 만큼 자른다.
					rest -= required;
				}
				else { // 패킷을 완성하기에는 데이타가 부족
					memcpy(overlapped->mPacketBuf + overlapped->mPrevReceived, buf, rest);
					// 패킷을 버퍼에 저장
					overlapped->mPrevReceived += rest;
					// 프로세스 데이터 초기화
					rest = 0;
				}
			} // 패킷 조립 while 루프
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
	// 네트워크 초기화, bind, Listen
	mNetworkSession->Begin();
	while (true) {
		int ret = mNetworkSession->Accept();
		if (ret == FALSE)
		{
			exit(1);
		}
		int playerId = mClientManager->SetConnectId();
		if (playerId == -1) {
			cLog::ErrorDisplay("허용유저 초과");
		}
		mClientManager->AddPlayer(playerId, mNetworkSession->GetClientSocket());
		auto player = mClientManager->FindPlayerById(playerId);
		player->SetXPos(0.0f);
		player->SetYPos(0.0f);
		player->SetZPos(0.0f);
		player->SetHp(1000);
		std::cout << "플레이어 사용가능 여부 : " << player->GetIsUse() << std::endl;
		std::cout << "플레이어 ID" << player->GetId() << std::endl;
		
		// IOCP 연결
	
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(mNetworkSession->GetClientSocket()),
			mCompletionPort, playerId, 0);
		// 최초 Recv호출
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
