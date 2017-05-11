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
}

DummyFlow::~DummyFlow()
{
}

void DummyFlow::print()
{
}

void DummyFlow::flowGenerate(counter flowId, time_sec onTime,
		unsigned int npackets, string netInterface)
{
	int rc = 0;

	unsigned int usecs = (unsigned int) (this->getFlowStartDelay() * MEGA_POWER);
	string flow_str_print = "";
	protocol prt;
	StochasticModelFit themodel;

	/***************************************************************************
	 * Dummy-parser
	 **************************************************************************/

	/**
	 * Flow-level
	 */
	flow_str_print += "Flow> Duration:" + std::to_string(getFlowDuration())
			+ ", Start-delay:" + std::to_string(getFlowStartDelay()) + "s"
			+ ", N.packets: " + std::to_string(getNumberOfPackets());

	////////////////////////////////////////////////////////////////////////////
	/// Link-layer protocol
	////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////
	/// Network-layer protocol
	////////////////////////////////////////////////////////////////////////////

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

	////////////////////////////////////////////////////////////////////////////
	/// Transport-layer protocol
	////////////////////////////////////////////////////////////////////////////

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

	// Application protocol
	flow_str_print += " Application[no-protocol] ";

	////////////////////////////////////////////////////////////////////////////
	/// Inter-deperture model
	////////////////////////////////////////////////////////////////////////////

	flow_str_print += " Inter-deperture[";
	themodel = this->getInterDepertureTimeModel_next();
	flow_str_print += themodel.strModelName();

	if (themodel.modelName() == WEIBULL)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", betha=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == NORMAL)
	{
		flow_str_print += ": mu=" + std::to_string(themodel.param1())
				+ ", sigma=" + std::to_string(themodel.param2());
	}
	else if ((themodel.modelName() == EXPONENTIAL_LINEAR_REGRESSION)
			|| (themodel.modelName() == EXPONENTIAL_MEAN))
	{
		flow_str_print += ": lambda=" + std::to_string(themodel.param1());
	}
	else if ((themodel.modelName() == PARETO_LINEAR_REGRESSION)
			|| (themodel.modelName() == PARETO_MAXIMUM_LIKEHOOD))
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", xm=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == CAUCHY)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", x0=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == CONSTANT)
	{
		flow_str_print += ": mean=" + std::to_string(themodel.param1());
	}
	else if ((themodel.modelName() == SINGLE_PACKET)
			|| (themodel.modelName() == NO_MODEL))
	{
		//do nothing
	}
	else
	{

		cerr << "Error @" << __PRETTY_FUNCTION__
				<< "No model selected for Inter-deperture model\n" << "Hint: "
				<< " this->getInterDepertureTimeModel_next() = "
				<< themodel.strModelName() << endl;
	}

	flow_str_print += "] ";

	flow_str_print += " ("
			+ std::to_string(getNumberOfInterdepertureTimeModels()) + ")";

	////////////////////////////////////////////////////////////////////////////
	/// Packet-size model
	////////////////////////////////////////////////////////////////////////////

	flow_str_print += " Packet-size-Mode1[";

	themodel = this->getPacketSizeModelMode1_next();
	flow_str_print += themodel.strModelName();

	if (themodel.modelName() == WEIBULL)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", betha=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == NORMAL)
	{
		flow_str_print += ": mu=" + std::to_string(themodel.param1())
				+ ", sigma=" + std::to_string(themodel.param2());
	}
	else if ((themodel.modelName() == EXPONENTIAL_LINEAR_REGRESSION)
			|| (themodel.modelName() == EXPONENTIAL_MEAN))
	{
		flow_str_print += ": lambda=" + std::to_string(themodel.param1());
	}
	else if ((themodel.modelName() == PARETO_LINEAR_REGRESSION)
			|| (themodel.modelName() == PARETO_MAXIMUM_LIKEHOOD))
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", xm=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == CAUCHY)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", x0=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == CONSTANT)
	{
		flow_str_print += ": mean=" + std::to_string(themodel.param1());
	}
	else if (themodel.modelName() == NO_MODEL)
	{
		//flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else
	{
		cerr << "Error @ " << __PRETTY_FUNCTION__
				<< "No model selected for Packet-size Mode1 model\n" << endl;
		cerr << "Hint: " << " getPacketSizeModelMode1_next = "
				<< themodel.strModelName() << endl;
		errno = EINVAL;
	}
	flow_str_print += "] ";

	flow_str_print += " Packet-size-Mode2[";

	themodel = this->getPacketSizeModelMode2_next();
	flow_str_print += themodel.strModelName();

	if (themodel.modelName() == WEIBULL)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", betha=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == NORMAL)
	{
		flow_str_print += ": mu=" + std::to_string(themodel.param1())
				+ ", sigma=" + std::to_string(themodel.param2());
	}
	else if ((themodel.modelName() == EXPONENTIAL_LINEAR_REGRESSION)
			|| (themodel.modelName() == EXPONENTIAL_MEAN))
	{
		flow_str_print += ": lambda=" + std::to_string(themodel.param1());
	}
	else if ((themodel.modelName() == PARETO_LINEAR_REGRESSION)
			|| (themodel.modelName() == PARETO_MAXIMUM_LIKEHOOD))
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", xm=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == CAUCHY)
	{
		flow_str_print += ": alpha=" + std::to_string(themodel.param1())
				+ ", x0=" + std::to_string(themodel.param2());
	}
	else if (themodel.modelName() == CONSTANT)
	{
		flow_str_print += ": mean=" + std::to_string(themodel.param1());
	}
	else if (themodel.modelName() == NO_MODEL)
	{
		//flow_str_print += ": mean=" + std::to_string(themodel.param1);
	}
	else
	{
		perror(
				"Error @ DummyFlow::flowGenerate(). No model selected for Packet-size Mode2 model\n");
		cerr << "Hint: " << " getPacketSizeModelMode2_next = "
				<< themodel.strModelName() << endl;
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

