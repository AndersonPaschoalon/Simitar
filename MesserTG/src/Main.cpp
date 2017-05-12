//============================================================================
// Name        : CompactTraceDescriptor.cpp
// Author      : Anderson Paschoalon
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DatabaseInterface.h"
#include "DataProcessor.h"
#include "DummyFlow.h"
#include "NetworkTrace.h"
#include "Defines.h"
#include "Protocol.h"
#include "cfunctions.h"
#include "MesserLog.h"

//Mutex example
// http://www.thegeekstuff.com/2012/05/c-mutex-examples/?refcom


#define REGRESSION_TESTS 1

void unity_regression_tests();


int main()
{
	RegressionTests wait;
	MESSER_LOG_INIT(INFO);

#ifdef REGRESSION_TESTS
	unity_regression_tests();
#endif

	string experimentName = "live_background-traffic-1";
	DataProcessor dp;
	DatabaseInterface dbif;
	long int nflows = 0;
	NetworkTrace* trace = NULL;

	//Create Network Trace from database
	//TODO: the data object structure do not have to change.. I just want a
	// constructor that uses a experiment name and a database interface pointer
	// as input.
	dbif.getNumberOfFlows(experimentName, &nflows);
	MESSER_NOTICE("Creating a NetworkTrace. (nflows = %d) @<%s, %s>", nflows);
	trace = new NetworkTrace();



	dp.calculate(experimentName, &dbif, trace);


	trace->setInfoTracename("teste-chapolin");
	trace->setInfoCommentaries("este e um teste do compact trace descriptor");
	trace->setTrafficGenEngine("D-ITG");
	trace->setInfoCaptureInterface("eth0");
	trace->setInfoCaptureDate("07/04/2017");


	trace->writeToFile("kkk.xml");
	trace->writeToFile("data/regression-tests/test-trace.xml");

	MESSER_NOTICE("Executing NetworkTrace: trace->exec(true) @<%s, %s>");
	//trace->exec(true);

	//cout << "sleep before the next trace" << endl;
	//sleep(160);

	MESSER_DEBUG(
			"Check the values of networkFlow inside NetworkTrace class @<%s, %s>");

	MESSER_DEBUG("trace->networkFlow[0]->getNetworkProtocol() = %s @<%s, %s>",
			Protocol(trace->networkFlow[0]->getNetworkProtocol()).str().c_str());

	MESSER_DEBUG("trace->networkFlow[0]->getNetworkDstAddr() = %s @<%s, %s>",
			trace->networkFlow[0]->getNetworkDstAddr().c_str());

	MESSER_DEBUG("trace->networkFlow[0]->getTransportProtocol() = %s @<%s, %s>",
			Protocol(trace->networkFlow[0]->getTransportProtocol()).str().c_str());

	MESSER_DEBUG("trace->networkFlow[0]->getTransportDstPort() = %d @<%s, %s>",
			trace->networkFlow[0]->getTransportDstPort());

	MESSER_DEBUG("trace->networkFlow[2]->getNetworkProtocol() = %s @<%s, %s>",
			Protocol(trace->networkFlow[2]->getNetworkProtocol()).str().c_str());

	MESSER_DEBUG("trace->networkFlow[4]->getNetworkDstAddr() = %s @<%s, %s>",
			trace->networkFlow[4]->getNetworkDstAddr().c_str());

	MESSER_DEBUG("trace->networkFlow[6]->getTransportProtocol()  = %s @<%s, %s>",
			Protocol(trace->networkFlow[6]->getTransportProtocol()).str().c_str());

	MESSER_DEBUG("trace->networkFlow[30]->getTransportDstPort() = %d @<%s, %s>",
			trace->networkFlow[30]->getTransportDstPort());

	MESSER_DEBUG("trace->getNumberOfFlows() = %d @<%s, %s>",
			trace->getNumberOfFlows());
	MESSER_DEBUG("<%s>");



	//wait.wait_int();

	delete trace;

	//MESSER_DEBUG("<%s, %s>");

	NetworkTrace* tracetest = NULL;
	//tracetest = new NetworkTrace("kkk.xml");
	tracetest = new NetworkTrace("data/regression-tests/test-trace.xml");
	//NetworkTrace traceTest = NetworkTrace("kkk.xml");
	tracetest->setInfoTracename("teste-chapolin");
	tracetest->setInfoCommentaries(
			"este e um teste do compact trace descriptor");
	tracetest->setTrafficGenEngine("D-ITG");
	tracetest->setInfoCaptureInterface("eth0");
	tracetest->setInfoCaptureDate("07/04/2017");
	tracetest->writeToFile("copia-kjjjjj.xml");
	tracetest->writeToFile("data/regression-tests/copy-test-trace.xml");

	tracetest->regression_tests();

	delete tracetest;

	MESSER_DEBUG(" @<%s, %s>");

	MESSER_LOG_END();

	return 0;
}


void unity_regression_tests(){
	//MESSER_LOG_INIT(INFO);
	//MESSER_NOTICE("Starting Unitary tests... <%s, %s>");
	RegressionTests rt;

	DataProcessor unity_dp = DataProcessor();
	Protocol unity_proto = Protocol();
	NetworkTrace unity_nt;
	StochasticModelFit unity_smf = StochasticModelFit();

	unity_dp.regression_tests();
	unity_nt.regression_tests();
	unity_proto.regression_tests();
	unity_smf.unity_tests();
	cfunctions_unitytests();

	//wait.wait_int("Finished tests, press any key...");
	//MESSER_NOTICE("Finishing Unity tests...  @<%s, %s>");



}


