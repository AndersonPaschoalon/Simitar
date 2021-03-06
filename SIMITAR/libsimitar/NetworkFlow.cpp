/*
 * NetworkFlow.cpp
 *
 *  Created on: 15 de set de 2016
 *      Author: apaschoalon
 */

#include "NetworkFlow.h"
#include "DummyFlow.h"

NetworkFlow::NetworkFlow()
{
	/// flow settings
	flow_time_scale = seconds;
//	flow_sleep_method = method_usleep;

	///flow-level parameters initialization
	flowId = 0;
	flow_ds_byte = 0;
	flow_duration = 0;
	flow_start_delay = 0;
	number_of_kbytes = 0;
	number_of_packets = 0;

	///protocols parameters  initialization
	link_protocol = PROTOCOL__ETHERNET; //default
	mac_src = "";
	mac_dst = "";
	network_dst_addr = "";
	network_src_addr = "";
	network_protocol = PROTOCOL__IPV4; //default
	network_ttl = 64; //default
	network_hostList_conter = 0;
	transport_protocol = PROTOCOL__UDP; //default
	transport_dst_port = 0;
	transport_sctp_association_id = 0;
	transport_sctp_max_streams = 0;
	transport_src_port = 0;
	application_protocol = PROTOCOL__NULL;

	/// Interarrival
	ptr_interArrivalModelList = NULL;
	//interDepertureTimeModel_counter = 0;
	ptr_session_onTimes = NULL;
	ptr_session_offTimes = NULL;
	ptr_session_nBytes = NULL;
	ptr_session_nPackets = NULL;
	//sessionOnTimes_counter = 0;
	sessionOnTimes_counter = -1;
	sessionOffTimes_counter = -1;

	/// Packet size parameters
	ptr_psMode1 = NULL;
	ptr_psMode2 = NULL;
	nkbytes_mode1 = 0;
	nkbytes_mode2 = 0;
	npacket_mode1 = 0;
	npackets_mode2 = 0;

}

/**
 * Time scale defined for the network Flow. This settings must be changed in the
 * flow generator class constructor. The default scale is seconds.
 * If the flow time scale is seconds, it returns 1.0. If it is milliseconds,
 * returns 1000.0.
 * @return
 */
double NetworkFlow::timeScaleFactor()
{
	if (flow_time_scale == seconds)
		return (1.0);
	else if (flow_time_scale == milliseconds)
		return (1000.0);

	PLOG_ERROR << ERRORMSG_BAD_VALUE
						<< " value `flow_time_scale` invalid definition:"
						<< flow_time_scale;
	exit(ERROR_BAD_VALUE);
}

void NetworkFlow::setTimeScale(time_scale theTimeScale)
{
	flow_time_scale = theTimeScale;
}

NetworkFlow::~NetworkFlow()
{

	ptr_interArrivalModelList->clear();

	ptr_session_onTimes->clear();
	ptr_session_offTimes->clear();
	ptr_session_nBytes->clear();
	ptr_session_nPackets->clear();

	ptr_psMode1->clear();
	ptr_psMode2->clear();

	/// interarrival data structs
	delete ptr_interArrivalModelList;

	delete ptr_session_onTimes;
	delete ptr_session_offTimes;
	delete ptr_session_nBytes;
	delete ptr_session_nPackets;

	/// packet-size data structures
	delete ptr_psMode1;
	delete ptr_psMode2;
}

std::string NetworkFlow::print()
{
	string flow_str_print = "";
	StochasticModelFit themodel;

	/***************************************************************************
	 * Dummy-parser
	 **************************************************************************/

	/**
	 * Flow-level
	 */
	flow_str_print += "Flow" + std::to_string(flowId) + "> Duration:"
			+ std::to_string(getFlowDuration()) + ", Start-delay:"
			+ std::to_string(getFlowStartDelay()) + "s" + ", N.packets: "
			+ std::to_string(getNumberOfPackets());

	////////////////////////////////////////////////////////////////////////////
	/// Link-layer protocol
	////////////////////////////////////////////////////////////////////////////
	flow_str_print += " Link[" + Protocol(this->getLinkProtocol()).str() + "]";

	////////////////////////////////////////////////////////////////////////////
	/// Network-layer protocol
	////////////////////////////////////////////////////////////////////////////
	flow_str_print += " Network[" + Protocol(this->getNetworkProtocol()).str()
			+ "]";

	////////////////////////////////////////////////////////////////////////////
	/// Transport-layer protocol
	////////////////////////////////////////////////////////////////////////////
	flow_str_print += " Transport["
			+ Protocol(this->getTransportProtocol()).str() + "]";

	// Application protocol
	flow_str_print += " Application["
			+ Protocol(this->getApplicationProtocol()).str() + "]";

	////////////////////////////////////////////////////////////////////////////
	/// Inter-deperture model
	////////////////////////////////////////////////////////////////////////////
	flow_str_print += " Inter-deperture["
			+ this->getInterDepertureTimeModel(0).strModelName() + "]";

	////////////////////////////////////////////////////////////////////////////
	/// Packet-size model
	////////////////////////////////////////////////////////////////////////////
	flow_str_print += " Packet-size-Mode1["
			+ this->getPacketSizeModelMode1(0).strModelName() + "]";
	flow_str_print += " Packet-size-Mode2["
			+ this->getPacketSizeModelMode2(0).strModelName() + "]";

	simitar_iostream_mutex.lock();
	printf("%s\n", flow_str_print.c_str());
	simitar_iostream_mutex.unlock();

	return (flow_str_print);
}

int NetworkFlow::randTranportPort()
{
	return (rand() % (MAX_TRANSPORT_PORT_NUMBER + 1));
}

unsigned int NetworkFlow::getFlowDsByte() const
{
	return flow_ds_byte;
}

void NetworkFlow::setFlowDsByte(unsigned int flowDsByte)
{
	//allowed range [0, 255]
	//Under Linux you need root privileges to set the DS byte to a value
	//larger than 160
	if (flowDsByte < 255)
		flow_ds_byte = flowDsByte;
	else
		flow_ds_byte = 255;
}

protocol NetworkFlow::getApplicationProtocol() const
{
	return application_protocol;
}

void NetworkFlow::setApplicationProtocol(protocol applicationProtocol)
{
	application_protocol = applicationProtocol;
}

double NetworkFlow::getFlowDuration() const
{
	return flow_duration;
}

void NetworkFlow::setFlowDuration(double flowDuration)
{
	flow_duration = flowDuration;
}

double NetworkFlow::getFlowStartDelay() const
{
	return flow_start_delay;
}

void NetworkFlow::setFlowStartDelay(double flowStartDelay)
{
	flow_start_delay = flowStartDelay;
}

protocol NetworkFlow::getLinkProtocol() const
{
	return link_protocol;
}

void NetworkFlow::setLinkProtocol(protocol linkProtocol)
{
	link_protocol = linkProtocol;
}

void NetworkFlow::setMacSrcAddr(const string& macSrc)
{
	mac_src = macSrc;
}

void NetworkFlow::setMacDstAddr(const string& macDst)
{
	mac_dst = macDst;
}

const string& NetworkFlow::getNetworkDstAddr() const
{
	return network_dst_addr;
}

void NetworkFlow::setNetworkDstAddr(const string& networkDstAddr)
{
	network_dst_addr = networkDstAddr;
}

int NetworkFlow::getNetworkHostListConter() const
{
	return network_hostList_conter;
}

void NetworkFlow::setNetworkHostListConter(int networkHostListConter)
{
	network_hostList_conter = networkHostListConter;
}

protocol NetworkFlow::getNetworkProtocol() const
{
	return network_protocol;
}

void NetworkFlow::setNetworkProtocol(protocol networkProtocol)
{
	network_protocol = networkProtocol;
}

const string& NetworkFlow::getNetworkSrcAddr() const
{
	return network_src_addr;
}

void NetworkFlow::setNetworkSrcAddr(const string& networkSrcAddr)
{
	network_src_addr = networkSrcAddr;
}

unsigned int NetworkFlow::getNetworkTtl() const
{
	return network_ttl;
}

void NetworkFlow::setNetworkTtl(unsigned int networkTtl)
{
	network_ttl = networkTtl;
}

unsigned long int NetworkFlow::getNumberOfKbytes() const
{
	return number_of_kbytes;
}

void NetworkFlow::setNumberOfKbytes(unsigned long int numberOfKbytes)
{
	number_of_kbytes = numberOfKbytes;
}

unsigned long int NetworkFlow::getNumberOfPackets() const
{
	return number_of_packets;
}

void NetworkFlow::setNumberOfPackets(unsigned long int numberOfPackets)
{
	number_of_packets = numberOfPackets;
}

unsigned int NetworkFlow::getTransportDstPort() const
{
	return transport_dst_port;
}

void NetworkFlow::setTransportDstPort(unsigned int transportDstPort)
{
	transport_dst_port = transportDstPort;
}

unsigned int NetworkFlow::getTransportSctpAssociationId() const
{
	return transport_sctp_association_id;
}

void NetworkFlow::setTransportSctpAssociationId(
		unsigned int transportSctpAssociationId)
{
	transport_sctp_association_id = transportSctpAssociationId;
}

unsigned int NetworkFlow::getTransportSctpMaxStreams() const
{
	return transport_sctp_max_streams;
}

void NetworkFlow::setTransportSctpMaxStreams(
		unsigned int transportSctpMaxStreams)
{
	transport_sctp_max_streams = transportSctpMaxStreams;
}

unsigned int NetworkFlow::getTransportSrcPort() const
{
	return transport_src_port;
}

void NetworkFlow::setTransportSrcPort(unsigned int transportSrcPort)
{
	transport_src_port = transportSrcPort;
}

protocol NetworkFlow::getTransportProtocol() const
{
	return transport_protocol;
}

void NetworkFlow::setTransportProtocol(protocol transportProtocol)
{
	transport_protocol = transportProtocol;
}

StochasticModelFit NetworkFlow::getInterDepertureTimeModel(
		unsigned int position)
{
	StochasticModelFit themodel;
	unsigned int i = 0;

	if (ptr_interArrivalModelList == NULL)
	{
		themodel.set(NO_MODEL, 0, 0, datum::inf, datum::inf);
		//ptr_interArrivalModelList->push_back(themodel);

		PLOG_ERROR << ERRORMSG_BAD_VALUE
							<< "Trying to get a StochasticModelFit,"
							<< "but no model was set."
							<< "NO_MODEL set as default";
	}
	else
	{
		list<StochasticModelFit>::iterator it;

		for (it = ptr_interArrivalModelList->begin();
				it != ptr_interArrivalModelList->end(); it++)
		{
			if (i == position)
			{

				themodel = *it;
				break;
			}
			i++;
		}
		if (position > i)
		{
			themodel = *it;
		}
	}

	return (themodel);

}

void NetworkFlow::setInterDepertureTimeModels(
		list<StochasticModelFit>* modelList)
{
	ptr_interArrivalModelList = modelList;
	//interDepertureTimeModel_counter = 0;
}

void NetworkFlow::setSessionTimesOnOff(vector<time_sec>* onTimesVec,
		vector<time_sec>* offTimesVec, vector<unsigned int>* pktCounter,
		vector<unsigned int>* fileSize)
{
	ptr_session_onTimes = onTimesVec;
	ptr_session_offTimes = offTimesVec;
	ptr_session_nPackets = pktCounter;
	ptr_session_nBytes = fileSize;
}

time_sec NetworkFlow::getSessionOnTime_next()
{
	sessionOnTimes_counter++;
	if (sessionOnTimes_counter >= ptr_session_onTimes->size())
	{
		sessionOnTimes_counter = 0;
	}
	return (ptr_session_onTimes->at(sessionOnTimes_counter));
}

time_sec NetworkFlow::getSessionOffTime_next()
{
	sessionOffTimes_counter++;
	if (sessionOffTimes_counter >= ptr_session_offTimes->size())
	{
		sessionOffTimes_counter = -1;
		return (.0);
	}
	return (ptr_session_offTimes->at(sessionOffTimes_counter));
}

uint NetworkFlow::getSessionOnTime_nPackets() const
{
	return (ptr_session_nPackets->at(sessionOnTimes_counter));
}

uint NetworkFlow::getSessionOnTime_nBytes() const
{
	return (ptr_session_nBytes->at(sessionOnTimes_counter));
}

StochasticModelFit NetworkFlow::getPacketSizeModelMode1(unsigned int position)
{
	StochasticModelFit themodel;
	unsigned int i = 0;

	if (ptr_psMode1 == NULL)
	{
		themodel.set(NO_MODEL, 0, 0, datum::inf, datum::inf);
		//ptr_psMode1->push_back(themodel);

		PLOG_ERROR << ERRORMSG_BAD_VALUE
							<< " Trying to get a StochasticModelFit, but no model was set. NO_MODEL set as default";
	}
	else
	{
		std::list<StochasticModelFit>::iterator it;

		for (it = ptr_psMode1->begin(); it != ptr_psMode1->end(); it++)
		{
			if (i == position)
			{

				themodel = *it;
				break;
			}
			i++;
		}
		if (position > i)
		{
			themodel = *it;
		}

	}

	return (themodel);
}

StochasticModelFit NetworkFlow::getPacketSizeModelMode2(unsigned int position)
{
	StochasticModelFit themodel;
	unsigned int i = 0;

	if (ptr_psMode2 == NULL)
	{
		themodel.set(NO_MODEL, 0, 0, datum::inf, datum::inf);
		//ptr_psMode2->push_back(themodel);

		PLOG_ERROR << ERRORMSG_BAD_VALUE
							<< " Trying to get a StochasticModelFit, but no model was set. NO_MODEL set as default";
	}
	else
	{
		std::list<StochasticModelFit>::iterator it;

		for (it = ptr_psMode2->begin(); it != ptr_psMode2->end(); it++)
		{
			if (i == position)
			{

				themodel = *it;
				break;
			}
			i++;
		}
		if (position > i)
		{
			themodel = *it;
		}

	}

	return (themodel);
}


void NetworkFlow::setPacketSizeModel(std::list<StochasticModelFit>* modelVet1,
		std::list<StochasticModelFit>* modelVet2, long int nkbytesMode1,
		long int nkbytesMode2, long int nPacketsMode1, long int nPacketsMode2)
{
	ptr_psMode1 = modelVet1;
	ptr_psMode2 = modelVet2;
	nkbytes_mode1 = nkbytesMode1;
	nkbytes_mode2 = nkbytesMode2;
	npacket_mode1 = nPacketsMode1;
	npackets_mode2 = nPacketsMode2;

}

long int NetworkFlow::getNkbytesMode1() const
{
	return nkbytes_mode1;
}

long int NetworkFlow::getNkbytesMode2() const
{
	return nkbytes_mode2;
}

long int NetworkFlow::getNpacketsMode1() const
{
	return npacket_mode1;
}

unsigned int NetworkFlow::getNumberOfInterdepertureTimeModels()
{
	if (ptr_interArrivalModelList != NULL)
	{
		return (ptr_interArrivalModelList->size());
	}
	else
	{
		return (0);
	}
}

//TODO test -> not tested
unsigned int NetworkFlow::getNumberOfPsMode1Models() const
{
	if (ptr_psMode1 != NULL)
	{
		return (ptr_psMode1->size());
	}
	else
	{
		return (0);
	}
}

//TODO test -> not tested
unsigned int NetworkFlow::getNumberOfPsMode2Models() const
{
	if (ptr_psMode2 != NULL)
	{
		return (ptr_psMode2->size());
	}
	else
	{
		return (0);
	}
}

long int NetworkFlow::getNpacketsMode2() const
{
	return npackets_mode2;
}

void NetworkFlow::setMacAddr(const string& macSrc, const string& macDst)
{
	mac_src = macSrc;
	mac_dst = macDst;
}

const string& NetworkFlow::getMacSrcAddr()
{
	return (mac_src);
}

const string& NetworkFlow::getMacDstAddr()
{
	return (mac_dst);
}

void NetworkFlow::resetCounters()
{
	sessionOnTimes_counter = 0;
	sessionOffTimes_counter = 0;
}

inline int NetworkFlow::getLocalIfIp(char* interface, char* ipaddr)
{
	struct ifaddrs *ifaddr, *ifa;
	int s;
	//int family, s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1)
	{
		//perror("getifaddrs");
		//return (-1);
		PLOG_FATAL << ERRORMSG_GENERAL_IO_ERROR << "getifaddrs";
		exit(ERROR_GENERAL_IO_ERROR);
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
	{

		if (ifa->ifa_addr == NULL)
			continue;

		s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host,
		NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, "lo") != 0)
				&& (ifa->ifa_addr->sa_family == AF_INET))
		{
			if (s != 0)
			{
				//printf("getnameinfo() failed: %s\n", gai_strerror(s));
				//return (-2);
				PLOG_FATAL << ERRORMSG_GENERAL_IO_ERROR
									<< "getnameinfo() failed: "
									<< gai_strerror(s);
				exit(ERROR_GENERAL_IO_ERROR);
			}
			strcpy(interface, ifa->ifa_name);
			strcpy(ipaddr, host);
			break;
		}
	}

	freeifaddrs(ifaddr);
	return (0);
}

inline int NetworkFlow::getLocalIp(const char* interface, char* ipaddr)
{
	struct ifaddrs *ifaddr, *ifa;
	int s;
	//int family, s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1)
	{
		PLOG_FATAL << ERRORMSG_GENERAL_IO_ERROR << "getifaddrs"
							<< "Check the ehternet interface:" << interface;
		exit(ERROR_GENERAL_IO_ERROR);
		//perror("getifaddrs");
		//return (-1);
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
	{

		if (ifa->ifa_addr == NULL)
			continue;

		s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host,
		NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, interface) == 0)
				&& (ifa->ifa_addr->sa_family == AF_INET))
		{
			if (s != 0)
			{
				//printf("getnameinfo() failed: %s\n", gai_strerror(s));
				//return (-2);
				PLOG_FATAL << ERRORMSG_GENERAL_IO_ERROR
									<< "getnameinfo() failed: "
									<< gai_strerror(s)
									<< "Check the ehternet interface:"
									<< interface;
				exit(ERROR_GENERAL_IO_ERROR);
			}

			strcpy(ipaddr, host);
			break;
		}
	}

	freeifaddrs(ifaddr);
	return (0);
}

// DEBUG
void NetworkFlow::printModels()
{
	for (list<StochasticModelFit>::iterator it =
			ptr_interArrivalModelList->begin();
			it != ptr_interArrivalModelList->end(); it++)
	{
		it->print();
	}
}

vector<time_sec> *NetworkFlow::getSessionOnVector()
{
	return (ptr_session_onTimes);
}

vector<time_sec> *NetworkFlow::getSessionOffVector()
{
	return (ptr_session_offTimes);
}

vector<uint>* NetworkFlow::getSessionOnPacketsVector()
{
	return (ptr_session_nPackets);
}

vector<uint>* NetworkFlow::getSessionOnBytesVector()
{
	return (ptr_session_nBytes);
}

