#pragma once
class cClientManager : public Singleton<cClientManager>
{
public:
	cClientManager();
	~cClientManager();

	// �ʱ�ȭ
	bool InitializePlayers();
	// ID �Ҵ�
	int AllocatePlayerId();

	// ID �� �÷��̾� ã��
	cPlayer* FindPlayerById(int playerId);

	void PushPlayer(cPlayer* player);

private:
	std::vector<cPlayer*> mPlayers;
	int mId;
};

