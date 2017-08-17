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
			cLog::ErrorDisplay("플레이어 초기화 실패");
			return false;
		}
		else {
			cLog::LogMessage("플레이어 초기화 성공");
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
	cLog::ErrorDisplay("유저의 접속 수가 초과 되었습니다. 유저수를 늘리세요 멍청아");
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