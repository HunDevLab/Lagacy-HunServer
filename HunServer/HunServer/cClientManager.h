#pragma once
class cClientManager : public Singleton<cClientManager>
{
public:
	cClientManager();
	~cClientManager();

	// ID 할당
	int SetConnectId();
	BOOL InitailizeClient();
	void AddPlayer(int playerId, SOCKET sock);
	void RemovePlayer(int playerId);
	// ID 로 플레이어 찾기
	cPlayer* FindPlayerById(int playerId);

	std::vector<cPlayer*> GetPlayerList() { return mPlayers; }
	int GetUserCount() { return userCount; }
private:
	std::vector<cPlayer*> mPlayers;
	int mId;
	int userCount;
	std::mutex		mClientLock;
};

