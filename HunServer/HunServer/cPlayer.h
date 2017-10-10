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
	std::set<int>	mViewList;

public:
	int	GetLevel() { return mLevel; }
	int GetHp() { return mHp; }
	int GetExp() { return mExp; }
	int GetIsAlive() { return mIsAlive; }
	std::string GetName() { return mName; }
	std::set<int> GetViewList() { return mViewList; }

	void SetLevel(int level) { mLevel = level; }
	void SetHp(int hp) { mHp = hp; }
	void SetExp(int exp) { mExp = exp; }
	void SetIsAlive(int isAlive) { mIsAlive = isAlive; }
	void SetName(std::string name) { mName = name; }
	void SetViewList(std::set<int> viewList) { mViewList = viewList; }

	void resetPlayer();
};

