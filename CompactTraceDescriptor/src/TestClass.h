/*
 * TestClass.h
 *
 *  Created on: 22 de jun de 2016
 *      Author: apaschoalon
 */

#ifndef TESTCLASS_H_
#define TESTCLASS_H_

#include <iostream>
#include <string>
#include <time.h>

#include "Defines.h"
#include "DatabaseInterface.h"
#include "DataProcessor.h"
#include "Defines.h"

namespace std
{

class TestClass
{
public:
	TestClass(string test);
	virtual ~TestClass();
	void printTestResult(string testName, bool result);
	template<typename T> bool isEqual(const T* vet1, const T* vet2,
			const int size);
	template<typename T> bool isEqual(const T val1, const T val2);
	bool compareDouble(double val1, double val2);
	bool compareDouble(double val1, double val2, double acErr);

};

class ExecutionTime
{
	ExecutionTime()
	{
		tStart = clock();
	}
	~ExecutionTime()
	{
		//do nothing;
	}
	void PrintTime()
	{
		printf("Time taken: %.2fs\n",
				(double) (clock() - tStart) / CLOCKS_PER_SEC);
	}

private:
	clock_t tStart;
};

} /* namespace std */


void waitKey();



#endif /* TESTCLASS_H_ */
