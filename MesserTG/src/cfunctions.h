/*
 * cfunctions.h
 *
 *  Created on: 25 de abr de 2017
 *      Author: anderson
 */

#ifndef CFUNCTIONS_H_
#define CFUNCTIONS_H_

#include <iostream>
#include <string.h>
#include <string>
#include <list>
#include <armadillo>

using std::list;
using std::string;
using std::cout;
using std::endl;
using namespace arma;

#include "Defines.h"
#include "RegressionTests.h"


/**
 * @brief
 *
 * @param theVec
 * @param str
 */
void vector2str(vector<double> theVec, char* str);

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
void vector2str(vector<int> theVec, char* str);

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
void vector2str(vector<long int> theVec, char* str);

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
void vector2str(vector<unsigned int> theVec, char* str);

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
void vector2str(vector<unsigned long int> theVec, char* str);


/**
 * @brief Convert a string s to a C string vetc (char vector).
 * Convet a std::string to a C string. The C string must have been
 * instantiated. If the std::string s is larger than the C sting vetc, it is
 * truncated.
 *
 * @param s	 	std::string to be converted
 * @param vetc 	C string output
 */
void string2charvet(const string s, char* vetc);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
void list2str(list<double> theList, char* str);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
void list2str(list<int> theList, char* str);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
void list2str(list<long int> theList, char* str);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
void list2str(list<unsigned int> theList, char* str);

/**
 *
 * @param theList
 * @param str
 */
void list2str(list<unsigned long int> theList, char* str);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
template<typename T>
void list2str(list<T> theList, string str);

/**
 * @brief Convert a integer written in a C string format to int type.
 *
 * @param vetc 	C string integer
 * @param v 	integer output
 */
void charvet2type(const char* vetc, int& v);

/**
 * @brief
 *
 * @param vetc
 * @param v
 */
void charvet2type(const char* vetc, unsigned int& v);

/**
 * @brief Convert a integer written in a C string format to long int type.
 *
 * @param vetc	C string integer
 * @param v		long int integer output
 */
void charvet2type(const char* vetc, long int& v);

/**
 * @brief Convert a integer written in a C string format to long int type.
 *
 * @param vetc	C string integer
 * @param v		long int integer output
 */
void charvet2type(const char* vetc, unsigned long int& v);

/**
 * @brief Convert a float number written in a C string format to double type.
 *
 * @param vetc		C string float
 * @param theList	double output
 */
void charvet2type(const char* vetc, double& v);

/**
 * @brief Convert a list of floats in CSV format to a std::list<double>
 * Takes as input a C string list of integers in CSV format (numbers separated
 * by comma ) and converts it to a std::list<double>
 *
 * @param vetc		C string of integers in CSV format
 * @param theList	an empty list in the format std::list<double>
 */
void charvet2type(const char* vetc, list<double>& theList);

/**
 * @brief Convert a list of integer in CSV format to a std::list<int>
 * Takes as input a C string list of integers in CSV format (numbers separated
 * by comma ) and converts it to a std::list<int>
 *
 * @param vetc		C string of integers in CSV format
 * @param theList	an empty list in the format std::list<int>
 */
void charvet2type(const char* vetc, list<int>& theList);

/**
 * @brief Convert a list of integer in CSV format to a std::list<long int>
 * Takes as input a C string list of integers in CSV format (numbers separated
 * by comma ) and converts it to a std::list<long int>
 *
 * @param vetc		C string of integers in CSV format
 * @param theList	an empty list in the format std::list<long int>
 */
void charvet2type(const char* vetc, list<long int>& theList);


void charvet2type(const char* vetc, vector<long int>& theVector);
//void charvet2type(const char* vetc, vector<unsigned long int>& theVector);
void charvet2type(const char* vetc, vector<int>& theVector);
//void charvet2type(const char* vetc, vector<unsigned int>& theVector);
void charvet2type(const char* vetc, vector<double>& theVector);

/**
 * @brief Pint a list of any type in the standard output.
 * @param theList
 */
template<typename T>
void printList(list<T>& theList);


/**
 *
 * @param theList
 */
void printList(list<double>& theList);

/**
 * @brief check if the character c is a delimiter. Delimiters default are ',',
 * ';' and ' '(white space).
 * @param c char to be tested
 * @return true if it is a delimiter
 */
bool delimiter(char c);

/**
 * @brief Check if the character c is a delimiter.Demilimiter is specified as
 * second argument.
 * @param c 	char to be tested
 * @param d 	true if it is a delimiter
 * @return
 */
bool delimiter(char c, const char& d);

/**
 * @brief Calc a cumulative distribution of a dataset
 * @param dataSample
 * @param cumulativeDat
 */
//template<typename T> void cumulativeDistribution(list<T>& dataSample,
//		list<T>* cumulativeDat);

/**
 *
 * @param dataSample
 * @param cumulativeDat
 */
void cumulativeDistribution(list<double>& dataSample,
		list<double>* cumulativeDat);

////////////////////////////////////////////////////////////////////////////////
/// Tests
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief execute unity tests
 */
void cfunctions_unitytests();

/**
 * Uniy test function
 * @return true if succed
 */
bool test_delimiter();

/**
 * Unity test function
 * @return true if succed
 */
bool test_charvet2type();

/**
 * Unity test function
 * @return true if succed
 */
bool test_cumulativeDistribution();

/**
 * Unity test function
 * @return true if succed
 */
bool test_list2str();

#endif /* CFUNCTIONS_H_ */
