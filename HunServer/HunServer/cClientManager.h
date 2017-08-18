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

private:
	std::vector<cPlayer*> mPlayers;
	int mId;
};

