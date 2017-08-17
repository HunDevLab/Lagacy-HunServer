#pragma once
class cClientManager : public Singleton<cClientManager>
{
public:
	cClientManager();
	~cClientManager();

	// 초기화
	bool InitializePlayers();
	// ID 할당
	int AllocatePlayerId();

	// ID 로 플레이어 찾기
	cPlayer* FindPlayerById(int playerId);

	void PushPlayer(cPlayer* player);

private:
	std::vector<cPlayer*> mPlayers;
	int mId;
};

