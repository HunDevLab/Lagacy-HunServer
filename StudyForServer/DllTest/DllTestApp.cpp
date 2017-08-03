#include "DllTeat.h"
#pragma comment(lib, "DllTest.lib")

int main()
{
	cMyClass myClass;
	myClass.sum(100, 200);
	myClass.outputSum();

	return 0;
}