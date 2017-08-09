#pragma once
#include "cPlayer.h"

class cIocpServer : public Singleton<cIocpServer>
{
public:
	cIocpServer();
	~cIocpServer();

	bool		ConnectIoCompletionPort();
	bool		run();
	void		CreateWorkerThread();
	void		CreateAcceptThread();
	SOCKET		getListenSocket();
	HANDLE		getIocpHandle();

	void		WorkerThread();
	void		AcceptThread();
private:
	WSADATA		mWsaData;
	SOCKET		mListenSock;
	HANDLE		mIocp;
	cPlayer		mPlayer[MAX_USER];

	std::vector<std::thread*> mWorkerThread;
	std::thread* mAcceptThread;
};

