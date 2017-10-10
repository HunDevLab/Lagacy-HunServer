#include <iostream>
#include <stdexcept>

#include "Database.h"

using namespace std;

namespace Records {
	Database::Database()
	{
		mNextEmployeeNumber = kFirstEmployeeNumber;
	}


	Database::~Database()
	{
	}

	Employee& Database::addEmployee(string inFirstName, string inLastName)
	{
		Employee theEmployee;
		theEmployee.setFirstName(inFirstName);
		theEmployee.setLastName(inLastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);
		return mEmployees[mEmployees.size() - 1];
	}
	Employee& Database::getEmployee(int inEmployeeNumber)
	{
		for (auto emp = mEmployees.begin(); emp != mEmployees.end(); ++emp)
		{
			if (emp->getEmployeeNumber() == inEmployeeNumber)
			{
				return *emp;
			}
		}
		cerr << "No Employee with number " << inEmployeeNumber << endl;
		throw exception();
	}
	Employee& Database::getEmployee(std::string inFirstName, std::string inLastName)
	{
		for (auto emp = mEmployees.begin(); emp != mEmployees.end(); ++emp)
		{
			if (emp->getFirstName() == inFirstName && emp->getLastName() == inLastName) 
			{
				return *emp;
			}
		}
		return *mEmployees.begin();
	}
	void Database::displayAll() const
	{
		for (auto emp = mEmployees.begin(); emp != mEmployees.end(); ++emp)
		{
			emp->display();
		}
	}

	void Database::displayCurrent() const
	{
		for (auto emp = mEmployees.begin(); emp != mEmployees.end(); ++emp)
		{
			if (emp->getIsHired())
			{
				emp->display();
			}
		}
	}
	void Database::displayFormer() const
	{
		for (auto emp = mEmployees.begin(); emp != mEmployees.end(); ++emp)
		{
			if (emp->getIsHired() == false)
			{
				emp->display();
			}
		}
	}
}


