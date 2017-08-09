#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
	mHp = 0;
	mLevel = 0;
	mExp = 0;
	mIsAlive = 0;
	mName = nullptr;
	mViewList.clear();
}


cPlayer::~cPlayer()
{
}

int	cPlayer::getLevel()
{
	return mLevel;
}
int cPlayer::getHp()
{
	return mHp;
}
int cPlayer::getExp()
{
	return mExp;
}
int cPlayer::getIsAlive()
{
	return mIsAlive;
}
std::string cPlayer::getName()
{
	return mName;
}
std::set<int> cPlayer::getViewList()
{
	return mViewList;
}
void cPlayer::setLevel(int level)
{
	mLevel = level;
}
void cPlayer::setHp(int hp)
{
	mHp = hp;
}
void cPlayer::setExp(int exp)
{
	mExp = exp;
}
void cPlayer::setIsAlive(int isAlive)
{
	mIsAlive = isAlive;
}
void cPlayer::setName(std::string name)
{
	mName = name;
}
void cPlayer::setViewList(std::set<int> viewList)
{
	mViewList = viewList;
}

int cPlayer::initialize()
{
	mHp = 0;
	mLevel = 0;
	mExp = 0;
	mIsAlive = 0;
	mName = nullptr;
	mViewList.clear();
	mClientInfo.initialize();

	return true;
}