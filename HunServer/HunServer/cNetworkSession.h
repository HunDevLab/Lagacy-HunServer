#pragma once
class cNetworkSession : public Singleton<cNetworkSession>
{
private:
	WSADATA		mWsaData;
	SOCKET		mListenSocket;
	SOCKET		mClientSocket;

	struct sockaddr_in mListenAddr;
	struct sockaddr_in mClientAddr;

public:
	cNetworkSession();
	virtual ~cNetworkSession();

	bool Begin();
	bool End();

	bool Initialize();
	bool CreateSocket();
	bool Listen();
	bool Bind();
	bool Accept();

	// GET, SET FUNCTION
	// GET
	SOCKET GetListenSocket() { return mListenSocket; }
	SOCKET GetClientSocket() { return mClientSocket; }

	// SET
	void SetListenSocket(SOCKET sock) { mListenSocket = sock; }
	void SetClientSocket(SOCKET sock) { mClientSocket = sock; }
};

