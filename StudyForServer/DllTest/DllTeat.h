#ifdef DLLTEST_EXPORTS
#define DLLTEST_API __declspec(dllexport)
#else
#define DLLTEST_API __declspec(dllimport)
#endif // DLLTEST_EXPORTS

#include <iostream>
using namespace std;

class DLLTEST_API cMyClass {
private:
	int _nSum;
public:
	void sum(int a, int b);
	void outputSum();
};
