/*
 * DummyFlow.cpp
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#include "Defines.h"
#include "DummyFlow.h"

DummyFlow::DummyFlow()
{

	//
	//flow-level parameters initialization
	//
	flow_ds_byte = 0;
	flow_duration = 0;
	flow_start_delay = 0;
	number_of_kbytes = 0;
	number_of_packets = 0;

	//
	//protocols parameters  initialization
	//
	link_protocol = PROTOCOL__ETHERNET; //default
	link_src_addr_count = 0;
	network_dst_addr = "";
	network_protocol = PROTOCOL__IPV4; //default
	network_src_addr = "";
	network_ttl = 64; //default
	network_hostList_conter = 0;
	transport_protocol = PROTOCOL__UDP; //default
	transport_dst_port = 0;
	transport_sctp_association_id = 0;
	transport_sctp_max_streams = 0;
	transport_src_port = 0;
	application_protocol = PROTOCOL__NULL;

	//
	//Interarrival
	//
	interArrivalvet = 0;
	interDepertureTimeModel_counter = 0;
	interFileModel = 0;
	interFileModel_counter = 0;
	interSessionModel = 0;
	interSessionModel_counter = 0;

	//
	//Interarrival time parameters
	//
	psMode1 = NULL;
	psMode2 = NULL;
	nkbytes_mode1 = 0;
	nkbytes_mode2 = 0;
	npacket_mode1 = 0;
	npackets_mode2 = 0;
	packetSizeModel1_counter = 0;
	packetSizeModel2_counter = 0;

}

DummyFlow::~DummyFlow()
{
	//interarrival data structs
	delete[] interArrivalvet;
	delete[] interFileModel;
	delete[] interSessionModel;

	//packet-size data structures
	delete[] psMode1;
	delete[] psMode2;
}

void DummyFlow::flowGenerate()
{
	int rc = 0;

	//start delay
	unsigned int usecs = (unsigned int) (this->getFlowStartDelay() * MEGA_POWER);
	string flow_str_print = "";
	protocol prt;
	//stochastic_model themodel;
	StochasticModelFit themodel;

	/***************************************************************************
	 * Dummy-parser
	 **************************************************************************/

	/**
	 * Flow-level
	 */
	flow_str_print += "Flow> Duration:" + std::to_string(flow_duration)
			+ ", Start-delay:" + std::to_string(flow_start_delay) + "s"
			+ ", N.packets: " + std::to_string(number_of_packets);

	/**
	 * Link-layer protocol
	 */
	flow_str_print += " Link[";
	prt = this->getLinkProtocol();
	if (prt == PROTOCOL__ETHERNET)
	{
		flow_str_print += "Ethernet";
	}
	else
	{
		flow_str_print += "Ethernet";
	}
	flow_str_print += "]";

	/**
	 * Network-layer protocol
	 */
	flow_str_print += " Network[";
	prt = this->getNetworkProtocol();
	if (prt == PROTOCOL__IPV4)
	{
		flow_str_print += "IPv4: ";
	}
	else if (prt == PROTOCOL__IPV6)
	{
		flow_str_print += "IPv6: ";
	}
	else
	{
		flow_str_print += std::to_string(prt) + ": ";
	}
	flow_str_print += this->getNetworkSrcAddr() + " > "
			+ this->getNetworkDstAddr() + "]";

	/**
	 * Transport-layer protocol
	 */
	flow_str_print += " Transport[";
	prt = this->getTransportProtocol();
	if (prt == PROTOCOL__TCP)
	{
		flow_str_print += "TCP";
	}
	else if (prt == PROTOCOL__UDP)
	{
		flow_str_print += "UDP";
	}
	else if (prt == PROTOCOL__ICMP)
	{
		flow_str_print += "ICMP";
	}
	else if (prt == PROTOCOL__ICMPV6)
	{
		flow_str_print += "ICMPv6";
	}

	else if (prt == PROTOCOL__SCTP)
	{
		flow_str_print += "SCTP";
	}

	else if (prt == PROTOCOL__DCCP)
	{
		flow_str_print += "";
	}

	else if (prt == PROTOCOL__GRE)
	{
		flow_str_print += "GRE";
	}
	else
	{
		flow_str_print += std::to_string(prt);
	}
	flow_str_print += ": " + std::to_string(this->getTransportSrcPort()) + " > "
			+ std::to_string(this->getTransportDstPort()) + "]";

	/**
	 * Application protocol
	 */
	flow_str_print += " Application[no-protocol] ";

	/**
	 * Inter-deperture model
	 */
	flow_str_print += " Inter-deperture[";
	themodel = this->getInterDepertureTimeModel_next();
	flow_str_print += themodel.modelName;

	if (themodel.modelName == WEIBULL)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1)
				+ ", betha=" + std::to_string(themodel.param2);
	}
	else if (themodel.modelName == NORMAL)
	{
		flow_str_print += ": mu=" + std::to_string(themodel.param1) + ", sigma="
				+ std::to_string(themodel.param2);
	}
	else if ((themodel.modelName == EXPONENTIAL_LINEAR_REGRESSION)
			|| (themodel.modelName == EXPONENTIAL_MEAN))
	{
		flow_str_print += ": lambda=" + std::to_string(themodel.param1);
	}
	else if ((themodel.modelName == PARETO_LINEAR_REGRESSION)
			|| (themodel.modelName == PARETO_MAXIMUM_LIKEHOOD))
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", xm="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CAUCHY)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", x0="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CONSTANT)
	{
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else if (themodel.modelName == NO_MODEL)
	{
		//flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else
	{
		perror(
				"Error @ DummyFlow::flowGenerate(). No model selected for Inter-deperture model\n");
		cerr << "Hint: " << " this->getInterDepertureTimeModel_next() = "
				<< themodel.modelName << endl;
		errno = EINVAL;
	}
	flow_str_print += "] ";

	/**
	 * Inter-File time model
	 */
	flow_str_print += " Inter-File[";
	themodel = this->getInterFileTimeModel_next();
	flow_str_print += themodel.modelName;

	if (themodel.modelName == WEIBULL)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1)
				+ ", betha=" + std::to_string(themodel.param2);
	}
	else if (themodel.modelName == NORMAL)
	{
		flow_str_print += ": mu=" + std::to_string(themodel.param1) + ", sigma="
				+ std::to_string(themodel.param2);
	}
	else if ((themodel.modelName == EXPONENTIAL_LINEAR_REGRESSION)
			|| (themodel.modelName == EXPONENTIAL_MEAN))
	{
		flow_str_print += ": lambda=" + std::to_string(themodel.param1);
	}
	else if ((themodel.modelName == PARETO_LINEAR_REGRESSION)
			|| (themodel.modelName == PARETO_MAXIMUM_LIKEHOOD))
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", xm="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CAUCHY)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", x0="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CONSTANT)
	{
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else if (themodel.modelName == NO_MODEL)
	{
		//flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else
	{
		perror(
				"Error @ DummyFlow::flowGenerate(). No model selected for Inter-File time model\n");
		cerr << "Hint: " << " this->getInterFileTimeModel_next() = "
				<< themodel.modelName << endl;
		errno = EINVAL;
	}
	flow_str_print += "] ";

	/**
	 * Inter-session time model
	 */
	flow_str_print += " Inter-session[";
	themodel = this->getInterSessionTimeModel_next();
	flow_str_print += themodel.modelName;

	if (themodel.modelName == WEIBULL)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1)
				+ ", betha=" + std::to_string(themodel.param2);
	}
	else if (themodel.modelName == NORMAL)
	{
		flow_str_print += ": mu=" + std::to_string(themodel.param1) + ", sigma="
				+ std::to_string(themodel.param2);
	}
	else if ((themodel.modelName == EXPONENTIAL_LINEAR_REGRESSION)
			|| (themodel.modelName == EXPONENTIAL_MEAN))
	{
		flow_str_print += ": lambda=" + std::to_string(themodel.param1);
	}
	else if ((themodel.modelName == PARETO_LINEAR_REGRESSION)
			|| (themodel.modelName == PARETO_MAXIMUM_LIKEHOOD))
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", xm="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CAUCHY)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", x0="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CONSTANT)
	{
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else if (themodel.modelName == NO_MODEL)
	{
		//flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else
	{
		perror(
				"Error @ DummyFlow::flowGenerate(). No model selected for Inter-session time model\n");
		cerr << "Hint: " << " this->getInterSessionTimeModel_next() = "
				<< themodel.modelName << endl;
		errno = EINVAL;
	}
	flow_str_print += "] ";

	/**
	 * Packet-size model
	 */
	flow_str_print += " Packet-size-Mode1[";

	themodel = this->getPacketSizeModelMode1_next();
	flow_str_print += themodel.modelName;

	if (themodel.modelName == WEIBULL)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1)
				+ ", betha=" + std::to_string(themodel.param2);
	}
	else if (themodel.modelName == NORMAL)
	{
		flow_str_print += ": mu=" + std::to_string(themodel.param1) + ", sigma="
				+ std::to_string(themodel.param2);
	}
	else if ((themodel.modelName == EXPONENTIAL_LINEAR_REGRESSION)
			|| (themodel.modelName == EXPONENTIAL_MEAN))
	{
		flow_str_print += ": lambda=" + std::to_string(themodel.param1);
	}
	else if ((themodel.modelName == PARETO_LINEAR_REGRESSION)
			|| (themodel.modelName == PARETO_MAXIMUM_LIKEHOOD))
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", xm="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CAUCHY)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", x0="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CONSTANT)
	{
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else if (themodel.modelName == NO_MODEL)
	{
		//flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else
	{
		perror(
				"Error @ DummyFlow::flowGenerate(). No model selected for Packet-size Mode1 model\n");
		cerr << "Hint: " << " getPacketSizeModelMode1_next = "
				<< themodel.modelName << endl;
		errno = EINVAL;
	}
	flow_str_print += "] ";

	flow_str_print += " Packet-size-Mode2[";

	themodel = this->getPacketSizeModelMode2_next();
	flow_str_print += themodel.modelName;

	if (themodel.modelName == WEIBULL)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1)
				+ ", betha=" + std::to_string(themodel.param2);
	}
	else if (themodel.modelName == NORMAL)
	{
		flow_str_print += ": mu=" + std::to_string(themodel.param1) + ", sigma="
				+ std::to_string(themodel.param2);
	}
	else if ((themodel.modelName == EXPONENTIAL_LINEAR_REGRESSION)
			|| (themodel.modelName == EXPONENTIAL_MEAN))
	{
		flow_str_print += ": lambda=" + std::to_string(themodel.param1);
	}
	else if ((themodel.modelName == PARETO_LINEAR_REGRESSION)
			|| (themodel.modelName == PARETO_MAXIMUM_LIKEHOOD))
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", xm="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CAUCHY)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1) + ", x0="
				+ std::to_string(themodel.param2);
	}
	else if (themodel.modelName == CONSTANT)
	{
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else if (themodel.modelName == NO_MODEL)
	{
		//flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else
	{
		perror(
				"Error @ DummyFlow::flowGenerate(). No model selected for Packet-size Mode2 model\n");
		cerr << "Hint: " << " getPacketSizeModelMode2_next = "
				<< themodel.modelName << endl;
		errno = EINVAL;
	}
	flow_str_print += "] ";

	//convert the cpp flow-string to a c flow string, in order to atomize the printing
	const char* flow_print = flow_str_print.c_str();

	//rc = usleep(usecs);
	if (rc != 0)
	{
		perror(
				"Impossible to execute usleep() sleep at void DummyFlow::printFlow()\n");
		errno = EAGAIN;
		exit(EXIT_FAILURE);
	}

	pthread_mutex_t lock;
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	printf("%s\n", flow_print);
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);

}

int DummyFlow::randTranportPort()
{
	return (rand() % (MAX_TRANSPORT_PORT_NUMBER + 1));
}

//TODO implementar a lista de hosts -> catch these values from a list
string DummyFlow::getHostIP()
{
	string dstIP;
	pthread_mutex_t lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	if (network_hostList_conter == 0)
	{
		dstIP = "172.16.0.1";
		network_hostList_conter++;
	}
	else
	{
		dstIP = "172.16.0.2";
		network_hostList_conter = 0;
	}
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);

	return (dstIP);
}

unsigned int DummyFlow::getFlowDsByte() const
{
	return flow_ds_byte;
}

void DummyFlow::setFlowDsByte(unsigned int flowDsByte)
{
	//allowed range [0, 255]
	//Under Linux you need root privileges to set the DS byte to a value
	//larger than 160
	if (flowDsByte < 255)
		flow_ds_byte = flowDsByte;
	else
		flow_ds_byte = 255;
}

protocol DummyFlow::getApplicationProtocol() const
{
	return application_protocol;
}

void DummyFlow::setApplicationProtocol(protocol applicationProtocol)
{
	application_protocol = applicationProtocol;
}

double DummyFlow::getFlowDuration() const
{
	return flow_duration;
}

void DummyFlow::setFlowDuration(double flowDuration)
{
	flow_duration = flowDuration;
}

double DummyFlow::getFlowStartDelay() const
{
	return flow_start_delay;
}

void DummyFlow::setFlowStartDelay(double flowStartDelay)
{
	flow_start_delay = flowStartDelay;
}

protocol DummyFlow::getLinkProtocol() const
{
	return link_protocol;
}

void DummyFlow::setLinkProtocol(protocol linkProtocol)
{
	link_protocol = linkProtocol;
}

long int DummyFlow::getLinkSrcAddrCount() const
{
	return link_src_addr_count;
}

void DummyFlow::setLinkSrcAddrCount(long int linkSrcAddrCount)
{
	link_src_addr_count = linkSrcAddrCount;
}

const string& DummyFlow::getNetworkDstAddr() const
{
	return network_dst_addr;
}

void DummyFlow::setNetworkDstAddr(const string& networkDstAddr)
{
	network_dst_addr = networkDstAddr;
}

int DummyFlow::getNetworkHostListConter() const
{
	return network_hostList_conter;
}

void DummyFlow::setNetworkHostListConter(int networkHostListConter)
{
	network_hostList_conter = networkHostListConter;
}

protocol DummyFlow::getNetworkProtocol() const
{
	return network_protocol;
}

void DummyFlow::setNetworkProtocol(protocol networkProtocol)
{
	network_protocol = networkProtocol;
}

const string& DummyFlow::getNetworkSrcAddr() const
{
	return network_src_addr;
}

void DummyFlow::setNetworkSrcAddr(const string& networkSrcAddr)
{
	network_src_addr = networkSrcAddr;
}

unsigned int DummyFlow::getNetworkTtl() const
{
	return network_ttl;
}

void DummyFlow::setNetworkTtl(unsigned int networkTtl)
{
	network_ttl = networkTtl;
}

unsigned long int DummyFlow::getNumberOfKbytes() const
{
	return number_of_kbytes;
}

void DummyFlow::setNumberOfKbytes(unsigned long int numberOfKbytes)
{
	number_of_kbytes = numberOfKbytes;
}

unsigned long int DummyFlow::getNumberOfPackets() const
{
	return number_of_packets;
}

void DummyFlow::setNumberOfPackets(unsigned long int numberOfPackets)
{
	number_of_packets = numberOfPackets;
}

unsigned int DummyFlow::getTransportDstPort() const
{
	return transport_dst_port;
}

void DummyFlow::setTransportDstPort(unsigned int transportDstPort)
{
	transport_dst_port = transportDstPort;
}

unsigned int DummyFlow::getTransportSctpAssociationId() const
{
	return transport_sctp_association_id;
}

void DummyFlow::setTransportSctpAssociationId(
		unsigned int transportSctpAssociationId)
{
	transport_sctp_association_id = transportSctpAssociationId;
}

unsigned int DummyFlow::getTransportSctpMaxStreams() const
{
	return transport_sctp_max_streams;
}

void DummyFlow::setTransportSctpMaxStreams(unsigned int transportSctpMaxStreams)
{
	transport_sctp_max_streams = transportSctpMaxStreams;
}

unsigned int DummyFlow::getTransportSrcPort() const
{
	return transport_src_port;
}

void DummyFlow::setTransportSrcPort(unsigned int transportSrcPort)
{
	transport_src_port = transportSrcPort;
}

protocol DummyFlow::getTransportProtocol() const
{
	return transport_protocol;
}

void DummyFlow::setTransportProtocol(protocol transportProtocol)
{
	transport_protocol = transportProtocol;
}

StochasticModelFit DummyFlow::getInterDepertureTimeModel_next()
{
	StochasticModelFit themodel;
	if (interArrivalvet == NULL)
	{
		themodel.modelName = NO_MODEL;
		themodel.param1 = 0;
		themodel.param2 = 0;
	}
	else
	{
		themodel = this->interArrivalvet[interDepertureTimeModel_counter];
	}

	if (counter(themodel.size) > interDepertureTimeModel_counter)
	{
		interDepertureTimeModel_counter++;
	}

	return (themodel);
}

void DummyFlow::setInterDepertureTimeModels(StochasticModelFit* modelVet)
{
	interArrivalvet = modelVet;
	interDepertureTimeModel_counter = 0;
}

void DummyFlow::setInterFileTimeModel(StochasticModelFit* modelStruct)
{
	interFileModel = modelStruct;
}

StochasticModelFit DummyFlow::getInterFileTimeModel_next()
{
	StochasticModelFit themodel;
	if (interFileModel == NULL)
	{
		themodel.modelName = NO_MODEL;
		themodel.param1 = 0;
		themodel.param2 = 0;
	}
	else
	{
		themodel = this->interFileModel[interFileModel_counter];
	}

	if (themodel.size > interFileModel_counter)
	{
		interDepertureTimeModel_counter++;
	}

	return (themodel);
}

time_sec DummyFlow::getInterFileTime()
{
	time_sec interFileTimeRngEstimation = 0;

	//TODO: weibull-constant estimator rng generator

	return (interFileTimeRngEstimation);
}

void DummyFlow::setInterSessionTimeModel(StochasticModelFit* modelStruct)
{
	interSessionModel = modelStruct;
}

StochasticModelFit DummyFlow::getInterSessionTimeModel_next()
{
	StochasticModelFit themodel;
	if (interSessionModel == NULL)
	{
		themodel.modelName = NO_MODEL;
		themodel.param1 = 0;
		themodel.param2 = 0;
	}
	else
	{
		themodel = this->interSessionModel[interSessionModel_counter];
	}

	if (themodel.size > interSessionModel_counter)
	{
		interSessionModel_counter++;
	}

	return (themodel);
}

time_sec DummyFlow::getInterSessionTime()
{
	time_sec interSessionTimeRngEstimation = 0;

	//TODO: weibull-constant estimator rng generator

	return (interSessionTimeRngEstimation);
}

StochasticModelFit DummyFlow::getPacketSizeModelMode1_next()
{
	StochasticModelFit themodel;
	if (interFileModel == NULL)
	{
		themodel.modelName = NO_MODEL;
		themodel.param1 = 0;
		themodel.param2 = 0;
	}
	else
	{
		themodel = this->psMode1[packetSizeModel1_counter];
	}

	if (themodel.size > interFileModel_counter)
	{
		packetSizeModel1_counter++;
	}

	return (themodel);
}

StochasticModelFit DummyFlow::getPacketSizeModelMode2_next()
{
	StochasticModelFit themodel;
	if (interFileModel == NULL)
	{
		themodel.modelName = NO_MODEL;
		themodel.param1 = 0;
		themodel.param2 = 0;
	}
	else
	{
		themodel = this->psMode2[packetSizeModel2_counter];
	}

	if (themodel.size > interFileModel_counter)
	{
		packetSizeModel2_counter++;
	}

	return (themodel);
}

void DummyFlow::setPacketSizeModel(StochasticModelFit* modelVet1,
		StochasticModelFit* modelVet2, long int nkbytesMode1,
		long int nkbytesMode2, long int nPacketsMode1, long int nPacketsMode2)
{
	psMode1 = modelVet1;
	psMode2 = modelVet2;
	packetSizeModel1_counter = 0;
	packetSizeModel2_counter = 0;
	nkbytes_mode1 = nkbytesMode1;
	nkbytes_mode2 = nkbytesMode2;
	npacket_mode1 = nPacketsMode1;
	npackets_mode2 = nPacketsMode2;

}

long int DummyFlow::getNkbytesMode1() const
{
	return nkbytes_mode1;
}

long int DummyFlow::getNkbytesMode2() const
{
	return nkbytes_mode2;
}

long int DummyFlow::getNpacketMode1() const
{
	return npacket_mode1;
}

long int DummyFlow::getNpacketsMode2() const
{
	return npackets_mode2;
}

