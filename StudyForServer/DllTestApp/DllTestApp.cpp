#include "../DllTest/DllTeat.h"
#pragma comment(lib, "DllTest.lib")

int main(int argc, char* argv[]) {
	cMyClass myClass;
	myClass.sum(100, 200);
	myClass.outputSum();
	return 0;
}