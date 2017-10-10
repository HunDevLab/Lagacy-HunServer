#include "Account.h"



CAccount::CAccount()
{
	m_nId = 0;
	m_nMoney = 0;
	m_sName = nullptr;
}


CAccount::~CAccount()
{
}

std::string CAccount::getName()
{
	return m_sName;
}
void CAccount::setName(std::string name)
{
	m_sName = name;
}
int CAccount::getMoney()
{
	return m_nMoney;
}
void CAccount::setMoney(int money)
{
	m_nMoney = money;
}
int CAccount::getId()
{
	return m_nId;
}
void CAccount::setId(int id)
{
	m_nId = id;
}