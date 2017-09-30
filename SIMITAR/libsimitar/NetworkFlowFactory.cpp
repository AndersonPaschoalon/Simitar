/*
 * NetworkFlowFactory.cpp
 *
 *  Created on: 14 de set de 2017
 *      Author: anderson
 */

#include "NetworkFlowFactory.h"

NetworkFlowFactory::NetworkFlowFactory()
{

}

NetworkFlowFactory::~NetworkFlowFactory()
{
}


NetworkFlow* NetworkFlowFactory::make_flow(const string& choise)
{
	std::string choise_lc;

	// Allocate the destination space
	choise_lc.resize(choise.size());
	// Convert the source string to lower case storing the result in destination string
	std::transform(choise.begin(), choise.end(), choise_lc.begin(), ::tolower);

	if (choise_lc == "dummy")
	{
		//PLOG_DEBUG << "Creating DummyFlow";
		return new DummyFlow;
	}
	else if(choise_lc == "ditg")
	{
		//PLOG_DEBUG << "Creating DitgFlow";
		return new DitgFlow;
	}
	else if(choise_lc == "iperf")
	{
		//PLOG_DEBUG << "Creating IperfFlow";
		return new IperfFlow;
	}
	else if((choise_lc == "tins") || (choise_lc == "libtins"))
	{
		//PLOG_DEBUG << "Creating TinsFLow";
		printf("TODO\n");
	}
	else if (choise_lc == "ostinato"){
		//PLOG_DEBUG << "Creating OstinatoFLow";
		printf("TODO\n");
	}

	PLOG_WARN << ERRORMSG_BAD_VALUE << choise ;
	PLOG_INFO << "Instantiating DummyFlow as default";
	return new DummyFlow;
}

std::string NetworkFlowFactory::support_tools()
{
	return("dummy, ditg, iperf, tins");
}
