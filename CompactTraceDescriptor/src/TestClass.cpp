/*
 * TestClass.cpp
 *
 *  Created on: 22 de jun de 2016
 *      Author: apaschoalon
 */

#include "TestClass.h"

//#define HLINE "----------"
//#define TAB "::"
namespace std
{

TestClass::TestClass(string test)
{

	//testing DataProcessor class

	if (test == "DatabaseInterface")
	{
		cout << "value" << TAB << "expected" << endl;
		cout << HLINE << HLINE << endl;

		cout << "DatabaseInterface.getTraceData()" << endl;
		DatabaseInterface db;
		string experimentName = "exAbacate";
		string capture;
		long int capture_i;

		db.getTraceData(experimentName, "experimentDate", &capture);
		cout << capture << TAB << "Ter Jun 14 09:00:15 BRT 2016" << endl;
		db.getTraceData(experimentName, "experimentID", &capture);
		cout << capture << TAB << 0 << endl;
		db.getTraceData(experimentName, "Commentaries", &capture);
		cout << capture << TAB << "ex-test-validation" << endl;
		db.getTraceData(experimentName, "experimentID", &capture);
		cout << capture << TAB << 0 << endl;
		cout << "DatabaseInterface.getTraceData()" << endl;

		db.getNumberOfFlows(experimentName, &capture_i);
		cout << capture_i << TAB << 59 << endl;
		cout << "DatabaseInterface.getFlowData()" << endl;

		string strNetworkProtocol;
		double time;
		long int protocol_int;

		db.getFlowData(experimentName, 0, "eth__type", &strNetworkProtocol);
		cout << strNetworkProtocol << TAB << 2048 << endl;
		db.getFlowData(experimentName, 0, "eth__type", &protocol_int);
		cout << protocol_int << TAB << 2048 << endl;
		db.getFlowData(experimentName, 0, "frame__time_relative", &time);
		cout << time << TAB << 0 << endl;

		list<double> time_list;
		db.getFlowData(experimentName, 0, "frame__time_delta", time_list);
		cout << "time_list: ";
		for (list<double>::iterator it = time_list.begin();
				it != time_list.end(); it++)
		{
			cout << *it << ' ';
		}
		cout << endl;

		list<string> ip_list;
		db.getFlowData(experimentName, 0, "ip__dst", ip_list);
		cout << "ip_list: ";
		for (list<string>::iterator it = ip_list.begin(); it != ip_list.end();
				it++)
		{
			cout << *it << ' ';
		}
		cout << endl;
	}
	else if (test == "DataProcessor")
	{
		cout << "value" << TAB << "expected" << endl;
		cout << HLINE << HLINE << endl;

		string experimentName = "exAbacate";
		DataProcessor dp;
		DatabaseInterface dbif;
		long int nflows = 0;

		dbif.getNumberOfFlows(experimentName, &nflows);
		printTestResult("Number of flows", isEqual(int(nflows), 58));
		cout << "DatabaseInterface.nflows" << endl;
		cout << nflows << TAB << 58 << endl;

		cout << HLINE << HLINE << endl << "Mathematical methods" << HLINE
				<< HLINE << endl;

		printTestResult("QuickSort", dp.test_QuickSort());
		printTestResult("List Mode", dp.test_Mode());
		printTestResult("ListToVector", dp.test_list_tocvector());
		printTestResult("Empirical CDF", dp.test_empiricalCdf());
		printTestResult("Cost Function", dp.test_computeCost());

		printTestResult("Weibull PDF", dp.test_pdf_weibull());
		printTestResult("Weibull CDF", dp.test_cdf_weibull());
		printTestResult("Gradient Descendent", dp.test_gradientDescendent());

		printTestResult("Information Criterion",
				dp.test_informationCriterion());
		printTestResult("Exponential PDF", dp.test_pdf_exponential());
		printTestResult("Exponential CDF", dp.test_cdf_exponential());
		printTestResult("PDF Pareto", dp.test_pdf_pareto());
		printTestResult("Pareto CDF", dp.test_cdf_pareto());
		printTestResult("PDF Cauchy", dp.test_pdf_cauchy());
		printTestResult("CDF Cauchy", dp.test_cdf_cauchy());
		printTestResult("All fitting", dp.test_fitModels());
		printTestResult("Model selection", dp.test_modelSelection());

		//Create Network Trace
		//NetworkTrace trace = NetworkTrace(nflows);
		/*
		 NetworkTrace trace(nflows);
		 dp.calculate(experimentName, &dbif, &trace);

		 cout << "flow0: " << endl;
		 cout << "src IP: " << trace.netFlow[0].getNetworkSrcAddr() <<endl;
		 cout << "dst IP: " << trace.netFlow[0].getNetworkDstAddr() <<endl;
		 cout << "L4 pro: " << trace.netFlow[0].getTransportProtocol() << endl;
		 cout << "src port: " << trace.netFlow[10].getTransportSrcPort() << endl;
		 cout << "dst port: " << trace.netFlow[10].getTransportDstPort() << endl;

		 cout << "flow1: " << endl;
		 cout << "src IP: " << trace.netFlow[1].getNetworkSrcAddr() << endl;
		 cout << "dst IP: " << trace.netFlow[1].getNetworkDstAddr() << endl;
		 cout << "L4 pro: " << trace.netFlow[1].getTransportProtocol() << endl;
		 cout << "src port: " << trace.netFlow[10].getTransportSrcPort() << endl;
		 cout << "dst port: " << trace.netFlow[10].getTransportDstPort() << endl;

		 cout << "flow10: " << endl;
		 cout << "src IP: " << trace.netFlow[10].getNetworkSrcAddr() <<endl;
		 cout << "dst IP: " << trace.netFlow[10].getNetworkDstAddr() <<endl;
		 cout << "L4 pro: " << trace.netFlow[10].getTransportProtocol() << endl;
		 cout << "src port: " << trace.netFlow[10].getTransportSrcPort() << endl;
		 cout << "dst port: " << trace.netFlow[10].getTransportDstPort() << endl;

		 */

		//NetworkTrace trace;
	}
	else
	{
		cout << "Invalid Option" << endl;
	}

}

TestClass::~TestClass()
{
	cout << HLINE << endl << "end test.";
}

void TestClass::printTestResult(string testName, bool result)
{
	string outRes;
	if (result == true)
		outRes = "ok";
	else
		outRes = "failed";

	cout << testName << ":\t\t" << outRes << endl;
}

bool TestClass::compareDouble(double val1, double val2)
{
	double error = 0;

	error = fabs(double(val1) - double(val2));
	if (error > double(1e-5))
		return (false);
	else
		return (true);
}

bool TestClass::compareDouble(double val1, double val2, double acErr)
{
	double error = 0;

	error = fabs(double(val1) - double(val2));
	if (error > double(acErr))
		return (false);
	else
		return (true);
}

template<typename T>
bool TestClass::isEqual(const T* vet1, const T* vet2, const int size)
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
bool std::TestClass::isEqual(const T val1, const T val2)
{
	if (val1 == val2)
		return (true);
	else
		return (false);
}

} /* namespace std */
