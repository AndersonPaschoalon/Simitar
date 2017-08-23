/*
 * RegressionTests.h
 *
 *  Created on: 4 de abr de 2017
 *      Author: anderson
 */

#ifndef REGRESSIONTESTS_H_
#define REGRESSIONTESTS_H_

#define HLINE "----------"
#define TAB "::"

#include <string>
#include <iostream>
#include <cmath>
#include <list>

using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::list;

string strLog(const string& msg);
template<typename T>
void printLog(T output);

class RegressionTests
{
public:
	RegressionTests();
	virtual ~RegressionTests();
	void printHeader(string testName);
	void printTestResult(string testName, bool result);
	template<typename T> bool isEqual(const T* vet1, const T* vet2,
			const int size);
	template<typename T> bool isEqual(const T val1, const T val2);
	bool compareDouble(double val1, double val2);
	bool compareDouble(double val1, double val2, double acErr);
	void wait_int(string msg);
	void wait_int();
	void print(list<double>& theList);
	void print(list<int>& theList);

};

template<typename T>
void printLog(T output, const string& pretty_function)
{
	cout << output << " @ " << pretty_function << endl;
}



//string strLog(const string& msg, const string& pretty_function)
//{
//	string strf = pretty_function;
//	string strout = msg + " @ " + strf;
//	return (strout);
//}

#endif /* REGRESSIONTESTS_H_ */
