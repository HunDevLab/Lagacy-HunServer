#include <iostream>
#include "Employee.h"
using namespace std;
using namespace Records;

int main()
{
	cout << "Test Employee Class" << endl;
	Employee emp;
	emp.setFirstName("Myung Hun");
	emp.setLastName("Kang");
	emp.setEmployeeNumber(102);
	emp.setSalary(80000);
	emp.promote();
	emp.promote(50);
	emp.hire();
	emp.display();
	return 0;
}