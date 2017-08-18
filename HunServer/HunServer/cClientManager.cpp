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
	(*player)->mRecvOverlappedEx.wsabuf.buf = (*player)->mRecvOverlappedEx.IOCPbuf;
	(*player)->mRecvOverlappedEx.wsabuf.len = MAX_BUFF_SIZE;
	return *player;
}