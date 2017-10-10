#pragma once
class cClientManager : public Singleton<cClientManager>
{
public:
	cClientManager();
	~cClientManager();

	// ID �Ҵ�
	int SetConnectId();
	BOOL InitailizeClient();
	void AddPlayer(int playerId, SOCKET sock);
	void RemovePlayer(int playerId);
	// ID �� �÷��̾� ã��
	cPlayer* FindPlayerById(int playerId);

private:
	std::vector<cPlayer*> mPlayers;
	int mId;
	std::mutex		mClientLock;
};

