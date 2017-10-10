#pragma once
#include "cClientInfo.h"
class cPlayer : public cClientInfo
{
public:
	cPlayer();
	virtual ~cPlayer();

private:
	std::string	mName;
	int			mHp;
	int			mLevel;
	int			mExp;
	int			mIsAlive;
	float		mXPos;
	float		mYPos;
	float		mZPos;
	std::set<int>	mViewList;

public:
	int	GetLevel() { return mLevel; }
	int GetHp() { return mHp; }
	int GetExp() { return mExp; }
	int GetIsAlive() { return mIsAlive; }
	float GetXPos() { return mXPos; }
	float GetYPos() { return mYPos; }
	float GetZPos() { return mZPos; }
	std::string GetName() { return mName; }
	std::set<int> GetViewList() { return mViewList; }

	void SetLevel(int level) { mLevel = level; }
	void SetHp(int hp) { mHp = hp; }
	void SetExp(int exp) { mExp = exp; }
	void SetIsAlive(int isAlive) { mIsAlive = isAlive; }
	void SetName(std::string name) { mName = name; }
	void SetViewList(std::set<int> viewList) { mViewList = viewList; }
	void SetXPos(float xPos) { mXPos = xPos; }
	void SetYPos(float yPos) { mYPos = yPos; }
	void SetZPos(float zPos) { mZPos = zPos; }

	void resetPlayer();
};

