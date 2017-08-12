#pragma once
#include "cClientInfo.h"
class cPlayer : public cClientInfo
{
public:
	cPlayer();
	virtual ~cPlayer();

	int	GetLevel();
	int GetHp();
	int GetExp();
	int GetIsAlive();
	std::string GetName();
	std::set<int> GetViewList();
	void SetLevel(int level);
	void SetHp(int hp);
	void SetExp(int exp);
	void SetIsAlive(int isAlive);
	void SetName(std::string name);
	void SetViewList(std::set<int> viewList);

	int Initialize();

private:
	std::string	mName;
	int			mHp;
	int			mLevel;
	int			mExp;
	int			mIsAlive;
	std::set<int>	mViewList;
	cClientInfo mClientInfo;
};

