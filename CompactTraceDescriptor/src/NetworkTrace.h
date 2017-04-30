/*
 * NetworkTrace.h
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#ifndef NETWORKTRACE_H_
#define NETWORKTRACE_H_

//external libs
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <vector>

//local libs
#include "NetworkFlow.h"

//namespaces
using std::string;
using std::vector;

class NetworkTrace {
public:

	NetworkTrace();

	/**
	 * Constructor. Creates a void trace
	 */
	//NetworkTrace(long int nflows);
	NetworkTrace(string trafficGen);

	/**
	 * Contructor, autoset from a file
	 */
	NetworkTrace(FILE* CompactTraceDescriptor, string choise);

	/**
	 * Destructor. Free any stored memory
	 */
	virtual ~NetworkTrace();


	//copy cosntructor
	NetworkTrace(const NetworkTrace &rhs);

	//assignment operator
	const NetworkTrace& operator= (const NetworkTrace& rhs);

	//to string operator
	string toString();

	//print method
	void print();


	/**
	 * TODO: this method should be private. I just have to pass a pointer
	 * to the database interface, and the experiment name. The object
	 * DataProcessor should be hide and instantiated by the NetworkTrace
	 * overloaded constructor:
	 * => NetworkTrace(string experimentName, DatabaseInterface db)
	 * -----
	 * This method take as input a network flow object, make a copy by
	 * value of this data structure, and store in the flow list.
	 */
	int pushback_Netflow(NetworkFlow* netFlow);

	/**
	 *
	 *
	 */
	int writeToFile(const string& fileName) const;

	/**
	 * call wirteToFile, but uses getInfoTracename() for the file name.
	 *
	 */
	int writeToFile(void) const;

	//##########################################################################
	//Getters and Setters
	//##########################################################################

	/**
	 * Returns a string information about the class
	 */
	const string toString() const;

	/**
	 *
	 */
	const string& getInfoCaptureDate() const;

	/**
	 *
	 */
	void setInfoCaptureDate(const string& infoCaptureDate);

	/**
	 *
	 */
	const string& getInfoCaptureInterface() const;

	/**
	 *
	 */
	void setInfoCaptureInterface(const string& infoCaptureInterface);

	/**
	 *
	 */
	const string& getInfoCommentaries() const;

	/**
	 *
	 */
	void setInfoCommentaries(const string& infoCommentaries);

	/**
	 *
	 */
	const string& getInfoTracename() const;

	/**
	 *
	 */
	void setInfoTracename(const string& infoTracename);

	/**
	 *
	 */
	long int getNumberOfFlows() const;

	/**
	 *
	 */
	//NetworkFlow* netFlow;
	vector<NetworkFlow*> networkFlow;

	/**
	 *
	 */
	int exec(bool verbose);

	const string& getTrafficGenEngine() const
	{
		return trafficGenEngine;
	}

	void setTrafficGenEngine(const string& trafficGenEngine)
	{
		this->trafficGenEngine = trafficGenEngine;
	}

private:

	string trafficGenEngine;
	string info_tracename;
	string info_captureInterface;
	string info_captureDate;
	string info_commentaries;

};


#endif /* NETWORKTRACE_H_ */
