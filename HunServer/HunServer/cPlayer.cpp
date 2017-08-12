#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
	mHp = 0;
	mLevel = 0;
	mExp = 0;
	mIsAlive = 0;
	mName = "";
	mViewList.clear();
}


cPlayer::~cPlayer()
{
}

int	cPlayer::GetLevel()
{
	return mLevel;
}
int cPlayer::GetHp()
{
	return mHp;
}
int cPlayer::GetExp()
{
	return mExp;
}
int cPlayer::GetIsAlive()
{
	return mIsAlive;
}
std::string cPlayer::GetName()
{
	return mName;
}
std::set<int> cPlayer::GetViewList()
{
	return mViewList;
}
void cPlayer::SetLevel(int level)
{
	mLevel = level;
}
void cPlayer::SetHp(int hp)
{
	mHp = hp;
}
void cPlayer::SetExp(int exp)
{
	mExp = exp;
}
void cPlayer::SetIsAlive(int isAlive)
{
	mIsAlive = isAlive;
}
void cPlayer::SetName(std::string name)
{
	mName = name;
}
void cPlayer::SetViewList(std::set<int> viewList)
{
	mViewList = viewList;
}

int cPlayer::Initialize()
{
	mHp = 0;
	mLevel = 0;
	mExp = 0;
	mIsAlive = 0;
	mName = "";
	mViewList.clear();
	mClientInfo.Initialize();

	return true;
}