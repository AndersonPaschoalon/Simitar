//============================================================================
// Name        : integration-tests.cpp
// Author      : Anderson Paschoalon
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <DatabaseInterface.h>
#include <DataProcessor.h>
#include <DummyFlow.h>
#include <NetworkTrace.h>
#include <Defines.h>
#include <Protocol.h>
#include <cfunctions.h>
#include <SimitarWorkspace.h>
using namespace std;

int main() {

	bool testDummy = true;
	bool testDitg = false;
	//bool testSetIPAddrs = true;
	//bool testWorkspace = true;

	if (testDummy == true)
	{
		string experimentName = "live_background-traffic-1";
		DataProcessor dp = DataProcessor(milliseconds, 0.1, 30.0, 2,"aic");
		DatabaseInterface dbif;
		long int nflows = 0;
		NetworkTrace* trace = NULL;

		//Create Network Trace from database
		//TODO: the data object structure do not have to change.. I just want a
		// constructor that uses a experiment name and a database interface pointer
		// as input.
		dbif.getNumberOfFlows(experimentName, &nflows);
		//MESSER_NOTICE("Creating a NetworkTrace. (nflows = %d) @<%s, %s>", nflows);
		trace = new NetworkTrace();

		dp.calculate(experimentName, &dbif, trace);



		trace->setInfoTracename("teste-chapolin");
		trace->setInfoCommentaries(
				"este e um teste do compact trace descriptor");
		//trace->setTrafficGenEngine("D-ITG");
		//trace->setInfoCaptureInterface("eth0");
		trace->setInfoCaptureDate("07/04/2017");

		trace->writeToFile("xml/ms-kkk.xml");
		/*
		trace->writeToFile("data/regression-tests/test-trace.xml");

*/
		//trace->exec(true);
		delete trace;
	}
	if (testDitg == true)
	{
		//string experimentName = "live_background-traffic-1";
		//DataProcessor dp;
		//DatabaseInterface dbif;
		//long int nflows = 0;
		//NetworkTrace* trace = NULL;
		//dbif.getNumberOfFlows(experimentName, &nflows);
		//MESSER_NOTICE("Creating a NetworkTrace. (nflows = %d) @<%s, %s>", nflows);
		//trace = new NetworkTrace();
		////dp.calculate(experimentName, &dbif, trace);
		//trace->setTrafficGenEngine("D-ITG");
		//trace->exec(true);
		NetworkTrace traceCdt =  NetworkTrace("kkk.xml", "dummy");
		//NetworkTrace traceCdt =  NetworkTrace("changed-ips-macs-trace.xml", "Dummy");
		traceCdt.exec("stdout");

	}


	return 0;
}
