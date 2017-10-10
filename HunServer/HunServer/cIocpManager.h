#pragma once
class cNetworkSession;
class cClientManager;
class cPacketController;
class cIocpManager : public Singleton<cIocpManager>
{
public:
	cIocpManager();
	~cIocpManager();

	bool ResistWorkerThread();
	bool ResistAcceptThread();
	bool Begin();

	void AcceptThread();
	void WorkerThread();

	void End();
	
	HANDLE GetCompletionPort() { return mCompletionPort; };
	HANDLE				mCompletionPort;
private:
	cClientManager*		mClientManager;
	cNetworkSession*	mNetworkSession;
	cPacketController*	mPacketController;

	std::vector<std::thread*> mWorkerThread;
	std::thread* mAcceptThread;
	
};

