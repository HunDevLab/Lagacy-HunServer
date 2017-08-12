#include "stdafx.h"
#include "cIocpServer.h"

//class cClientInfo;
//
//cClientInfo gUser[MAX_USER];

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
	for (int i = 0; i < NUM_THREADS; ++i)
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
SOCKET cIocpServer::getListenSocket()
{
	return mListenSock;
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

		if (io_size == 0) {
			//players[id].in_use = false;
			//std::cout << "ID : " << id << "Players[id].in_use = " << players[id].in_use << std::endl;
			//std::cout << "before UpdateDB : " << players[id].name << std::endl;
			//UpdateDB(players[id].name, id, players[id].x, players[id].y, players[id].Level, players[id].Exp);
			//for (int i = 0; i<MAX_USER; ++i) {
			//	if (players[i].in_use == false) continue;
			//	//send_remove_player(i, id);
			//	if (0 != players[i].view_list.count(id)) {
			//		players[i].view_list.erase(id);
			//		send_remove_player(i, id);
			//	}
			//}
			//closesocket(players[id].my_socket);
		}

		if (overlapped->is_send == false) {
			int rest = io_size;
			CHAR *buf = overlapped->IOCPbuf;
			int packet_size = overlapped->curr_packet_size;
			int old_received = overlapped->prev_received;

			while (0 != rest) {
				//if (0 == packet_size) packet_size = buf[0];
				//int required = packet_size - old_received;
				//if (rest >= required) {  // 패킷 제작 가능
				//	memcpy(overlapped->PacketBuf + old_received,
				//		buf, required);
				//	ProcessPacket(id, overlapped->PacketBuf);
				//	packet_size = 0;
				//	old_received = 0;
				//	buf += required;
				//	rest -= required;
				//}
				//else { // 패킷을 완성하기에는 데이타가 부족
				//	memcpy(overlapped->PacketBuf + old_received,
				//		buf, rest);
				//	old_received += rest;
				//	rest = 0;
				//}
			} // 패킷 조립 while 루프
			//overlapped->curr_packet_size = packet_size;
			//overlapped->prev_received = old_received;
			//DWORD recv_flag = 0;
			//int ret = WSARecv(players[id].my_socket,
			//	&players[id].recv_over_ex.wsabuf, 1,
			//	NULL, &recv_flag,
			//	&players[id].recv_over_ex.overlapped, NULL);

			//if (ret) {	// WSAENOTSOCK
			//	int err_code = WSAGetLastError();
			//	if (err_code != ERROR_IO_PENDING) {

			//		cLog::ErrorDisplay("Recv on workerthread\n", err_code);
			//	}
			//}
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

	SOCKET listen_socket = WSASocket(AF_INET, SOCK_STREAM,
		IPPROTO_TCP, NULL, 0,
		WSA_FLAG_OVERLAPPED);

	ZeroMemory(&listen_addr, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	listen_addr.sin_port = htons(MY_SERVER_PORT);
	ZeroMemory(&listen_addr.sin_zero, 8);

	int ret = ::bind(listen_socket,
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
	ret = listen(listen_socket, 10);
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
		SOCKET client_socket = WSAAccept(listen_socket,
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
		// IOCP 연결
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(client_socket),
			mIocp, 0, 0);
		// Recv호출
		unsigned long recv_flag = 0;

		cPlayer* player = cClientManager::getInstance()->FindPlayerById(playerId);
		std::cout << "플레이어 사용가능 여부 : " << player->GetIsUse() << std::endl;
		std::cout << "플레이어 ID" << player->GetId() << std::endl;
		//int ret = WSARecv(client_socket,
		//	&player->GetRecvOverExWsabuf(), 1, NULL, &recv_flag,
		//	&player->GetRecvOverExOverlapped(), NULL);
		//if (ret) {
		//	// WSAENOTSOCK
		//	int err_code = WSAGetLastError();
		//	if (err_code != ERROR_IO_PENDING)
		//		printf("Recv Error [%d]\n", err_code);
		//}
	}
}
