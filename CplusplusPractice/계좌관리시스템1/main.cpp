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
		cout << "���� : ";
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
	cout << "1. ���� ����" << endl;
	cout << "2. ���" << endl;
	cout << "3. �Ա�" << endl;
	cout << "4. ���� ���� ��ü ���" << endl;
	cout << "5. ����" << endl;
} 
void createAccount()
{
	int id;
	int money;
	std::string name;
	cout << "[[���� ����]]" << endl;
	cout << "ID : "; cin >> id;
	cout << "�̸� �Է� : "; cin >> name;
	cout << "ó�� �Աݾ� : "; cin >> money;

	account[AcountNum].setId(id);
	account[AcountNum].setName(name);
	account[AcountNum].setMoney(account[AcountNum].getMoney() + money);
	AcountNum++;

}
void addDeposit()
{
	int addMoney;
	CAccount* acnt = findAccount();
	cout << "�Ա� �ݾ� : "; cin >> addMoney;

	acnt->setMoney(acnt->getMoney() + addMoney);
}
void decreaseDeposit()
{
	int decMoney;
	CAccount* acnt = findAccount();
	cout << "��� �ݾ� : "; cin >> decMoney;

	acnt->setMoney(acnt->getMoney() - decMoney);
}
CAccount* findAccount()
{
	CAccount* acnt;
	std::string name;
	cout << "�� �̸��� �Է��ϼ��� : "; cin >> name;
	for (int i = 0; i < AcountNum; ++i) {
		if (name._Equal(account[i].getName()))
		{
			acnt = &account[i];
			cout << "[[[ �� ���� ]]]" << endl;
			cout << "ID : " << account[i].getId() << endl;
			cout << "�̸� :	" << account[i].getName() << endl;
			cout << "�ܾ� : " << account[i].getMoney() << endl;
			break; 
		}
	}
	return acnt;
}
void printAll()
{
	for (int i = 0; i < AcountNum; ++i)
	{
		cout << "[[ �� ��ȣ : " << i + 1 << "�� ���� ]]" << endl;
		cout << "ID : " << account[i].getId() << endl;
		cout << "�̸� : " << account[i].getName() << endl;
		cout << "�ܾ� : " << account[i].getMoney() << endl;
	}
}