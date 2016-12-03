/*
 * NetworkFlow.h
 *
 *  Created on: 15 de set de 2016
 *      Author: apaschoalon
 */

#ifndef NETWORKFLOW_H_
#define NETWORKFLOW_H_

//external libraries
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <pthread.h>
#include <string>

//local includes
#include "ITGapi.h"
#include "Defines.h"
#include "StochasticModelFit.h"

//namespaces
using std::string;
using std::cout;
using std::cin;
using std::endl;

class NetworkFlow
{
public:
	NetworkFlow();
	virtual ~NetworkFlow();
	static NetworkFlow *make_flow(string choise);

	virtual void flowGenerate() = 0;
	virtual std::thread flowThread() = 0;

	virtual int randTranportPort() = 0;
	virtual protocol getApplicationProtocol() const = 0;
	virtual void setApplicationProtocol(protocol applicationProtocol) = 0;
	virtual unsigned int getFlowDsByte() const = 0;
	virtual void setFlowDsByte(unsigned int flowDsByte) = 0;
	virtual time_sec getFlowDuration() const = 0;
	virtual void setFlowDuration(time_sec flowDuration) = 0;
	virtual time_sec getFlowStartDelay() const = 0;
	virtual void setFlowStartDelay(time_sec flowStartDelay) = 0;

	virtual protocol getLinkProtocol() const = 0;
	virtual void setLinkProtocol(protocol linkProtocol) = 0;
	virtual long int getLinkSrcAddrCount() const = 0;
	virtual void setLinkSrcAddrCount(long int linkSrcAddrCount) = 0;
	virtual const string& getNetworkDstAddr() const = 0;
	virtual void setNetworkDstAddr(const string& networkDstAddr) = 0;
	virtual int getNetworkHostListConter() const = 0;
	virtual void setNetworkHostListConter(int networkHostListConter) = 0;
	virtual protocol getNetworkProtocol() const = 0;
	virtual void setNetworkProtocol(protocol networkProtocol) = 0;
	virtual const string& getNetworkSrcAddr() const = 0;
	virtual void setNetworkSrcAddr(const string& networkSrcAddr) = 0;
	virtual unsigned int getNetworkTtl() const = 0;
	virtual void setNetworkTtl(unsigned int networkTtl) = 0;
	virtual unsigned long long int getNumberOfKbytes() const = 0;
	virtual void setNumberOfKbytes(unsigned long long int numberOfKbytes) = 0;
	virtual unsigned long long int getNumberOfPackets() const = 0;
	virtual void setNumberOfPackets(unsigned long long int numberOfPackets) = 0;

//TODO
//	virtual StochasticModelFit getPacketSizeModel_next() const = 0;
//	virtual void setPacketSizeModel_next(
//			StochasticModelFit* modelVet) const = 0;

	virtual void setInterDepertureTimeModels(StochasticModelFit* modelVet) = 0;
	virtual StochasticModelFit getInterDepertureTimeModel_next()= 0;

	virtual void setInterFileTimeModel(StochasticModelFit* modelVet) = 0;
	virtual StochasticModelFit getInterFileTimeModel_next() = 0;
	virtual time_sec getInterFileTime() = 0;

	virtual void setInterSessionTimeModel(StochasticModelFit* modelVet) = 0;
	virtual StochasticModelFit getInterSessionTimeModel_next() = 0;
	virtual time_sec getInterSessionTime() = 0;

	virtual unsigned int getTransportDstPort() const = 0;
	virtual void setTransportDstPort(unsigned int transportDstPort) = 0;
	virtual unsigned int getTransportSctpAssociationId() const = 0;
	virtual void setTransportSctpAssociationId(
			unsigned int transportSctpAssociationId) = 0;
	virtual unsigned int getTransportSctpMaxStreams() const = 0;
	virtual void setTransportSctpMaxStreams(
			unsigned int transportSctpMaxStreams) = 0;
	virtual port_number getTransportSrcPort() const = 0;
	virtual void setTransportSrcPort(port_number transportSrcPort) = 0;
	virtual protocol getTransportProtocol() const = 0;
	virtual void setTransportProtocol(protocol transportProtocol) = 0;

};

#endif /* NETWORKFLOW_H_ */
