#include "stdafx.h"
#include "cClientManager.h"


cClientManager::cClientManager()
{
	mId = -1;
	userCount = 0;
}


cClientManager::~cClientManager()
{
}

void cClientManager::AddPlayer(int playerId, SOCKET sock)
{
	gLock.lock();
	auto player = mPlayers[playerId];
	if (player != nullptr) {
		player->SetId(playerId);
		player->SetIsUse(true);
		player->SetSocket(sock);
	}
	userCount++;
	gLock.unlock();
}
int cClientManager::SetConnectId()
{
	/*for (auto player : mPlayers)
	{
		if (player->GetIsUse() == false)
		{
			player->SetIsUse(true);
			mId++;
			player->SetId(mId);
			return player->GetId();
		}
	}*/
	for (int i = 0; i < MAX_USER; ++i)
	{
		/*if (FindPlayerById(i) == nullptr)
		{
			return i;
		}*/
		auto player = mPlayers[i];
		if (player->GetIsUse() == false)
		{
			return i;
		}
		else {
			continue;
		}
	}
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
	if (player == mPlayers.end()) {
		return nullptr;
	}
	
	return *player;
}
void cClientManager::RemovePlayer(int playerId)
{
	
	auto player = std::find_if(mPlayers.begin(), mPlayers.end(), [=](cPlayer* a) {
		if (a->GetId() == playerId)
		{
			return true;
		}
		return false;
	});
	if (player != mPlayers.end())
	{
		if ((*player)->GetIsUse() == true)
		{
			std::cout << "playerId : " << playerId;
			(*player)->resetClient();
			(*player)->resetPlayer();
			(*player)->SetId(playerId);
			userCount--;
			std::cout << " RemovePlayer Function .. [Success]" << std::endl;
		}
	}
	
}
BOOL cClientManager::InitailizeClient()
{
	for (int i = 0; i < MAX_USER; ++i) {
		cPlayer* player = new cPlayer;
		player->resetPlayer();
		player->resetClient();
		player->SetId(i);
		mPlayers.push_back(player);
	}
	std::cout << "Player's Initialize ... [Success]" << std::endl;
	return true;
}
