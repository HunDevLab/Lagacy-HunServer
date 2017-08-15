#include <iostream>

using namespace std;

class CName
{
private:
	int m_iSize;
	char* m_pName;
public:
	CName(char* pName)
	{
		m_iSize = strlen(pName);
		m_pName = new char[m_iSize + 1];
		strcpy(m_pName, pName);
	}
	~CName() {
		delete[] m_pName;
	}
	void PrintName()
	{
		cout << m_pName << endl;
	}
	friend void PrintN(CName name)
	{
		name.PrintName();
	}
};

int main()
{
	CName name("neo-peaple");
	PrintN(name);

	return 0;
}