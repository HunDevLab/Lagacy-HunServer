#include "stdafx.h"
#include "cClientManager.h"


cClientManager::cClientManager()
{
	mId = 0;
}


cClientManager::~cClientManager()
{
}

bool cClientManager::InitializePlayers()
{
	mPlayers.reserve(MAX_USER);
	for (int i = 0; i < MAX_USER; ++i)
	{
		auto player = new cPlayer;
		int ret = player->Initialize();
		if (ret == 0) {
			cLog::ErrorDisplay("�÷��̾� �ʱ�ȭ ����");
			return false;
		}
		else {
			cLog::LogMessage("�÷��̾� �ʱ�ȭ ����");
		}
		mPlayers.push_back(player);
	}
	return true;
}

int cClientManager::AllocatePlayerId()
{
	for (auto player : mPlayers)
	{
		if (player->GetIsUse() == false)
		{
			player->SetIsUse(true);
			mId++;
			player->SetId(mId);
			return player->GetId();
		}
	}
	cLog::ErrorDisplay("������ ���� ���� �ʰ� �Ǿ����ϴ�. �������� �ø����� ��û��");
	return -1;
}

cPlayer* cClientManager::FindPlayerById(int playerId)
{
	auto player = std::find_if(mPlayers.begin(), mPlayers.end(), [=](cPlayer* a) {
		if (a->GetId() == playerId)
		{
			return true;
		}
		return false;
	});
	
	return *player;
}
void cClientManager::PushPlayer(cPlayer* player)
{
	mPlayers.push_back(player);
}