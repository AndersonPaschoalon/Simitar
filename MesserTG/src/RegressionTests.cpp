/*
 * RegressionTests.cpp
 *
 *  Created on: 4 de abr de 2017
 *      Author: anderson
 */

#include "RegressionTests.h"

RegressionTests::RegressionTests()
{
	// TODO Auto-generated constructor stub

}

RegressionTests::~RegressionTests()
{
	// TODO Auto-generated destructor stub
}

void RegressionTests::printTestResult(string testName, bool result)
{
	string outRes;
	if (result == true)
		outRes = "ok";
	else{
		outRes = "failed";
		//wait_int("test failed. Press any key to continue...\n");
	}
	cout << testName << ":\t\t" << outRes << endl;

}

bool RegressionTests::compareDouble(double val1, double val2)
{
	double error = 0;

	error = fabs(double(val1) - double(val2));
	if (error > double(1e-5))
		return (false);
	else
		return (true);
}

void RegressionTests::printHeader(string testName)
{
	cout << HLINE << HLINE << endl << testName << endl << HLINE << HLINE
			<< endl;
}

bool RegressionTests::compareDouble(double val1, double val2, double acErr)
{
	double error = 0;

	error = fabs(double(val1) - double(val2));
	if (error > double(acErr))
		return (false);
	else
		return (true);
}

template<typename T>
bool RegressionTests::isEqual(const T* vet1, const T* vet2, const int size)
{

	for (int i = 0; i < size; i++)
	{
		if (vet1[i] != vet2[i])
		{
			return (false);
		}
	}

	return (true);

}

template<typename T>
bool RegressionTests::isEqual(const T val1, const T val2)
{
	if (val1 == val2)
		return (true);
	else
		return (false);
}

void RegressionTests::wait_int(string msg)
{
	cout << msg << ":";
	string a;
	cin >> a;
	cout << endl;
}

void RegressionTests::wait_int()
{
	wait_int("Press any key");
}

void RegressionTests::print(list<double>& theList)
{
	cout << "[";
	for (list<double>::iterator it = theList.begin(); it != theList.end(); it++)
	{
		cout << *it << ", ";
	}
	cout << "]" << endl;
}

void RegressionTests::print(list<int>& theList)
{
	cout << "[";
	for (list<int>::iterator it = theList.begin(); it != theList.end(); it++)
	{
		cout << *it << ", ";
	}
	cout << "]" << endl;
}
