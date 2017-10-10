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

void cPlayer::resetPlayer()
{
	mHp = 0;
	mLevel = 0;
	mExp = 0;
	mIsAlive = 0;
	mName = "";
	mViewList.clear();
	resetClient();
}