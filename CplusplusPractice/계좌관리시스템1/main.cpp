#include <iostream>
#include <string>

#include "Account.h"

using namespace std;

void drawMenu();
void createAccount();
void addDeposit();
void decreaseDeposit();
CAccount* findAccount();
void printAll();

int AcountNum = 0;
CAccount account[100];

int main()
{
	
	int choice;
	while (1) {
		drawMenu();
		cout << "선택 : ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			createAccount();
			break;
		case 2:
			addDeposit();
			break;
		case 3:
			decreaseDeposit();
			break;
		case 4:
			findAccount();
			break;
		case 5:
			printAll();
			break;
		case 6:
			return 0;
		default:
			continue;
		}
	}
	return 0;
}
void drawMenu()
{
	cout << "---------- MENU -----------" << endl;
	cout << "1. 계좌 개설" << endl;
	cout << "2. 출금" << endl;
	cout << "3. 입금" << endl;
	cout << "4. 계좌 정보 전체 출력" << endl;
	cout << "5. 종료" << endl;
} 
void createAccount()
{
	int id;
	int money;
	std::string name;
	cout << "[[계좌 개설]]" << endl;
	cout << "ID : "; cin >> id;
	cout << "이름 입력 : "; cin >> name;
	cout << "처음 입금액 : "; cin >> money;

	account[AcountNum].setId(id);
	account[AcountNum].setName(name);
	account[AcountNum].setMoney(account[AcountNum].getMoney() + money);
	AcountNum++;

}
void addDeposit()
{
	int addMoney;
	CAccount* acnt = findAccount();
	cout << "입금 금액 : "; cin >> addMoney;

	acnt->setMoney(acnt->getMoney() + addMoney);
}
void decreaseDeposit()
{
	int decMoney;
	CAccount* acnt = findAccount();
	cout << "출금 금액 : "; cin >> decMoney;

	acnt->setMoney(acnt->getMoney() - decMoney);
}
CAccount* findAccount()
{
	CAccount* acnt;
	std::string name;
	cout << "고객 이름을 입력하세요 : "; cin >> name;
	for (int i = 0; i < AcountNum; ++i) {
		if (name._Equal(account[i].getName()))
		{
			acnt = &account[i];
			cout << "[[[ 고객 정보 ]]]" << endl;
			cout << "ID : " << account[i].getId() << endl;
			cout << "이름 :	" << account[i].getName() << endl;
			cout << "잔액 : " << account[i].getMoney() << endl;
			break; 
		}
	}
	return acnt;
}
void printAll()
{
	for (int i = 0; i < AcountNum; ++i)
	{
		cout << "[[ 고객 번호 : " << i + 1 << "번 정보 ]]" << endl;
		cout << "ID : " << account[i].getId() << endl;
		cout << "이름 : " << account[i].getName() << endl;
		cout << "잔액 : " << account[i].getMoney() << endl;
	}
}