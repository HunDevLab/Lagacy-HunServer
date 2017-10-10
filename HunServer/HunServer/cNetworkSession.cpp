#include "stdafx.h"
#include "cNetworkSession.h"


cNetworkSession::cNetworkSession()
{
}


cNetworkSession::~cNetworkSession()
{
}

bool cNetworkSession::Initialize()
{
	//Winsock √ ±‚»≠
	int ret = WSAStartup(MAKEWORD(2, 2), &mWsaData);
	if (0 != ret)
	{
		cLog::ErrorDisplay("WSAStartup() func Fail", GetLastError());
		return FALSE;
	}
	cLog::LogMessage("WINSOCK NETWORK INITIALIZE .... [Success]");
	return TRUE;
}

bool cNetworkSession::Begin()
{
	if (FALSE == CreateSocket())
	{
		cLog::ErrorDisplay("CreateSocket func Fail", GetLastError());
		return FALSE;
	}
	if (FALSE == Bind())
	{
		cLog::ErrorDisplay("Bind func Fail", GetLastError());
		return FALSE;
	}
	if (FALSE == Listen())
	{
		cLog::ErrorDisplay("Listen func Fail", GetLastError());
		return FALSE;
	}
	cLog::LogMessage("CREATE SOCKET .... [Success]");
	cLog::LogMessage("BIND .... [Success]");
	cLog::LogMessage("LISTEN .... [Success]");
	cLog::LogMessage("ACCEPT WAITING .... ");
	return TRUE;
}
bool cNetworkSession::End()
{
	return TRUE;
}

bool cNetworkSession::CreateSocket()
{
	mListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	return TRUE;
}
bool cNetworkSession::Listen()
{
	int ret = listen(mListenSocket, 10);
	if (SOCKET_ERROR == ret) {
		return FALSE;
	}
	return TRUE;
}
bool cNetworkSession::Bind()
{
	ZeroMemory(&mListenAddr, sizeof(mListenAddr));
	mListenAddr.sin_family = AF_INET;
	mListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	mListenAddr.sin_port = htons(MY_SERVER_PORT);
	ZeroMemory(&mListenAddr.sin_zero, 8);

	int ret = ::bind(mListenSocket,
		reinterpret_cast<sockaddr *>(&mListenAddr),
		sizeof(mListenAddr));
	if (SOCKET_ERROR == ret) {
		return FALSE;
	}
	return TRUE;
}
bool cNetworkSession::Accept()
{
	int addr_size = sizeof(mClientAddr);
	mClientSocket = WSAAccept(mListenSocket,
		reinterpret_cast<sockaddr *>(&mClientAddr),
		&addr_size, NULL, NULL);
	if (INVALID_SOCKET == mClientSocket) {
		cLog::ErrorDisplay("Accept func Fail", GetLastError());
		return FALSE;
	}
	cLog::LogMessage("ACCEPT .... [Success]");
	return TRUE;
}


