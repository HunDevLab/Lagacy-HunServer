#pragma once
#include <string>

class CAccount
{
public:
	CAccount();
	~CAccount();
	std::string getName();
	void setName(std::string name);
	int getMoney();
	void setMoney(int money);
	int getId();
	void setId(int id);
private:
	std::string m_sName;
	int m_nMoney;
	int m_nId;
};

