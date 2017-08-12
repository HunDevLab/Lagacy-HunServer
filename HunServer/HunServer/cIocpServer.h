#pragma once
//#include "cPlayer.h"

class cClientManager;
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

	//void		InitializePlayer();
private:
	WSADATA		mWsaData;
	SOCKET		mListenSock;
	HANDLE		mIocp;
	//std::vector<cPlayer*> mPlayers;
	//cClientManager* mClientManager;

	std::vector<std::thread*> mWorkerThread;
	std::thread* mAcceptThread;
};

