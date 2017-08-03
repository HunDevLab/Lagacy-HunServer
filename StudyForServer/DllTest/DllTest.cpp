#include "DllTeat.h"

void cMyClass::sum(int a, int b) {
	_nSum = a + b;
}

void cMyClass::outputSum() {
	cout << "Sum : " << _nSum;
}