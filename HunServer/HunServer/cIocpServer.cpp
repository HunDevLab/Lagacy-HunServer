#include "stdafx.h"
#include "cIocpServer.h"



cIocpServer::cIocpServer()
{
	int ret = WSAStartup(MAKEWORD(2, 2), &mWsaData);
	if (0 != ret)
	{
		cLog::ErrorDisplay("WSAStartup() func Fail",GetLastError());
		//return 0;
	}
	else {
		cLog::LogMessage("cIocp 생성자 호출, WSAStartup Func Success");
	}
}


cIocpServer::~cIocpServer()
{
	//closesocket(mListenSock);
	WSACleanup();
}

bool cIocpServer::ConnectIoCompletionPort()
{
	mIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	return true;
}
bool cIocpServer::run()
{
	ConnectIoCompletionPort();
	bool ret = cClientManager::getInstance()->InitializePlayers();
	if (ret == false)
	{
		cLog::ErrorDisplay("플레이어 초기화 실패");
	}
	else
	{
		std::cout << MAX_USER << "명 ";
		cLog::LogMessage("플레이어 초기화 성공");
	}
	CreateWorkerThread();
	CreateAcceptThread();
	return true;
}
void cIocpServer::CreateWorkerThread()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	int threadCount = systemInfo.dwNumberOfProcessors * 2;
	for (int i = 0; i < threadCount; ++i)
	{
		mWorkerThread.push_back(new std::thread{std::mem_fun(&cIocpServer::WorkerThread), this});
		std::cout << i + 1 << " ";
		cLog::LogMessage("번째 WorkerThread 생성");
	}
}
void cIocpServer::CreateAcceptThread()
{
	mAcceptThread = new std::thread{ std::mem_fun(&cIocpServer::AcceptThread), this };
	cLog::LogMessage("AcceptThread 생성");
}
HANDLE cIocpServer::getIocpHandle()
{
	return mIocp;
}
void cIocpServer::WorkerThread()
{
	DWORD io_size;
	int id;
	OverlappedEx *overlapped;

	while (true) {
		GetQueuedCompletionStatus(mIocp, &io_size, (PULONG)&id, reinterpret_cast<LPOVERLAPPED *>(&overlapped), INFINITE);
		auto player = cClientManager::getInstance()->FindPlayerById(id);
		if (io_size == 0) {
			player->SetIsUse(false);
			std::cout << "ID : " << id << "Players[id].in_use = " << player->GetIsUse() << std::endl;
			/*std::cout << "before UpdateDB : " << players[id].name << std::endl;
			UpdateDB(players[id].name, id, players[id].x, players[id].y, players[id].Level, players[id].Exp);*/
			//for (int i = 0; i < MAX_USER; ++i) {
			//	if (player->GetIsUse() == false) continue;
				//send_remove_player(i, id);
				//if (0 != players[i].view_list.count(id)) {
					//players[i].view_list.erase(id);
					//send_remove_player(i, id);
				//}
			//}
			closesocket(player->mClientSocket);
			continue;
		}

		if (overlapped->is_send == false) {
			int rest = io_size;
			CHAR *buf = overlapped->IOCPbuf;
			int packet_size = overlapped->curr_packet_size;
			int old_received = overlapped->prev_received;

			while (0 != rest) {
				if (0 == packet_size) packet_size = buf[0];
				int required = packet_size - old_received;
				if (rest >= required) {  // 패킷 제작 가능
					memcpy(overlapped->PacketBuf + old_received,
						buf, required);
					cPacketController::getInstance()->ProcessPacket(player->GetId(), overlapped->PacketBuf);
					packet_size = 0;
					old_received = 0;
					buf += required;
					rest -= required;
				}
				else { // 패킷을 완성하기에는 데이타가 부족
					memcpy(overlapped->PacketBuf + old_received,
						buf, rest);
					old_received += rest;
					rest = 0;
				}
			} // 패킷 조립 while 루프
			overlapped->curr_packet_size = packet_size;
			overlapped->prev_received = old_received;
			DWORD recv_flag = 0;
			int ret = WSARecv(player->mClientSocket,
				&player->mRecvOverlappedEx.wsabuf, 1,
				NULL, &recv_flag,
				&player->mRecvOverlappedEx.overlapped, NULL);

			if (ret) {	// WSAENOTSOCK
				int err_code = WSAGetLastError();
				if (err_code != ERROR_IO_PENDING) {

					cLog::ErrorDisplay("Recv on workerthread\n", err_code);
				}
			}
		}
		else if (overlapped->is_send == true) {
			delete overlapped;
		}
		else {
			printf("Error invalid overlapped\n");
			exit(-1);
		}
	}
}
void cIocpServer::AcceptThread()
{
	struct sockaddr_in listen_addr;
	struct sockaddr_in client_addr;

	SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM,
		IPPROTO_TCP, NULL, 0,
		WSA_FLAG_OVERLAPPED);

	ZeroMemory(&listen_addr, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	listen_addr.sin_port = htons(MY_SERVER_PORT);
	ZeroMemory(&listen_addr.sin_zero, 8);

	int ret = ::bind(listenSocket,
		reinterpret_cast<sockaddr *>(&listen_addr),
		sizeof(listen_addr));
	if (SOCKET_ERROR == ret) {
		cLog::ErrorDisplay("BIND", WSAGetLastError());
		exit(-1);
	}
	else
	{
		cLog::LogMessage("Bind Func Call");
	}
	ret = listen(listenSocket, 10);
	if (SOCKET_ERROR == ret) {
		cLog::ErrorDisplay("LISTEN", WSAGetLastError());
		exit(-1);
	}
	else
	{
		cLog::LogMessage("Listen Func Call");
	}
	
	int addr_size = sizeof(client_addr);
	while (true) {
		SOCKET client_socket = WSAAccept(listenSocket,
			reinterpret_cast<sockaddr *>(&client_addr),
			&addr_size, NULL, NULL);

		if (INVALID_SOCKET == client_socket) {
			cLog::ErrorDisplay("ACCEPT", WSAGetLastError());
			exit(-1);
		}
		else {
			cLog::LogMessage("Accept Func Call Success");
		}

		int playerId = cClientManager::getInstance()->AllocatePlayerId();
		if (playerId == -1) {
			cLog::ErrorDisplay("허용유저 초과");
		}
		cPlayer* player = cClientManager::getInstance()->FindPlayerById(playerId);
		player->mClientSocket = client_socket;
		player->mRecvOverlappedEx.curr_packet_size = 0;
		player->mRecvOverlappedEx.is_send = false;
		player->mRecvOverlappedEx.prev_received = 0;
		ZeroMemory(&player->mRecvOverlappedEx.overlapped, sizeof(WSAOVERLAPPED));
		std::cout << "플레이어 사용가능 여부 : " << player->GetIsUse() << std::endl;
		std::cout << "플레이어 ID" << player->GetId() << std::endl;
		// IOCP 연결
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(client_socket),
			mIocp, playerId, 0);
		// Recv호출
		unsigned long recv_flag = 0;
		int ret = WSARecv(player->mClientSocket,
			&player->mRecvOverlappedEx.wsabuf, 1, NULL, &recv_flag,
			&player->mRecvOverlappedEx.overlapped, NULL);
		if (ret) {
			// WSAENOTSOCK
			int err_code = WSAGetLastError();
			if (err_code != ERROR_IO_PENDING)
				printf("Recv Error [%d]\n", err_code);
		}

		
	}
	closesocket(listenSocket);
}
