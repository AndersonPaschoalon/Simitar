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

	/*
	 //
	 // Packet-size model
	 //
	 //TODO Normal model for bimodal
	 //TODO more statistical models
	 flow_str_print += " PacketSize[";

	 themodel = this->getPsModel1();
	 if (themodel == MODEL__NULL)
	 {
	 flow_str_print += "no-model";
	 }
	 else if (themodel == MODEL__BIMODAL_CONSTANT_CONSTANT)
	 {
	 flow_str_print += "bimodal-constant-constant: mean1="
	 + std::to_string(this->getPsBimodalMode1Constant()) + ", mean2="
	 + std::to_string(this->getPsBimodalMode2Constant());
	 }
	 else if (themodel == MODEL__BIMODAL_CONSTANT_WEIBULL)
	 {
	 flow_str_print += "bimodal-constant-weibull: mean1="
	 + std::to_string(this->getPsBimodalMode1Constant())
	 + ", shape2="
	 + std::to_string(this->getPsBimodalMode2WeibullShape())
	 + ", scale2="
	 + std::to_string(this->getPsBimodalMode2WeibullScale());
	 }
	 else if (themodel == MODEL__BIMODAL_WEIBULL_CONSTANT)
	 {
	 flow_str_print += "bimodal-weibull-constant: scale1="
	 + std::to_string(this->getPsBimodalMode1WeibullScale())
	 + ", shape1="
	 + std::to_string(this->getPsBimodalMode1WeibullShape())
	 + +", mean2="
	 + std::to_string(this->getPsBimodalMode2Constant());
	 }
	 else if (themodel == MODEL__BIMODAL_WEIBULL_WEIBULL)
	 {
	 flow_str_print += "bimodal-weibull-weibull: scale1="
	 + std::to_string(this->getPsBimodalMode1WeibullScale())
	 + ", shape1="
	 + std::to_string(this->getPsBimodalMode1WeibullShape())
	 + +", scale2="
	 + std::to_string(this->getPsBimodalMode2WeibullScale())
	 + ", shape2="
	 + std::to_string(this->getPsBimodalMode2WeibullShape());
	 }
	 else if (themodel == MODEL__CONSTANT)
	 {
	 flow_str_print += "constant: mean="
	 + std::to_string(this->getPsConstant()) + ", ="
	 + std::to_string(this->getPsConstant());
	 }
	 else if (themodel == MODEL__WEIBULL)
	 {
	 flow_str_print += "weibull: shape="
	 + std::to_string(this->getPsWeibullShape()) + ", scale="
	 + std::to_string(this->getPsWeibullScale());

	 }
	 else if (themodel == MODEL__UNIFORM)
	 {
	 flow_str_print += "uniform: max="
	 + std::to_string(this->getPsUniformMaxpktsize()) + ", min="
	 + std::to_string(this->getPsUniformMinpktsize());
	 }
	 else
	 {
	 perror("Error @ DummyFlow::flowGenerate(). No model selected for Packet Size\n");
	 cout << "Hint: " << "this->getPsModel1() = "<< this->getPsModel1();
	 cout << " && themodel = " << themodel << endl;
	 errno = EINVAL;
	 }
	 flow_str_print += "] ";
	 */

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
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
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
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
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
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
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
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
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
		flow_str_print += ": mean=" + std::to_string(themodel.param1);
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

	/// ///////////////////////////////////////////////////

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

/*
 double DummyFlow::getIdtCauchyScale() const
 {
 return idt_cauchy_scale;
 }

 void DummyFlow::setIdtCauchyScale(double idtCauchyScale)
 {
 idt_cauchy_scale = idtCauchyScale;
 }

 double DummyFlow::getIdtCauchyShape() const
 {
 return idt_cauchy_shape;
 }

 void DummyFlow::setIdtCauchyShape(double idtCauchyShape)
 {
 idt_cauchy_shape = idtCauchyShape;
 }

 double DummyFlow::getIdtConstant() const
 {
 return idt_constant;
 }

 void DummyFlow::setIdtConstant(double idtConstant)
 {
 idt_constant = idtConstant;
 }

 double DummyFlow::getIdtExponential() const
 {
 return idt_exponential;
 }

 void DummyFlow::setIdtExponential(double idtExponential)
 {
 idt_exponential = idtExponential;
 }

 double DummyFlow::getIdtGammaScale() const
 {
 return idt_gamma_scale;
 }

 void DummyFlow::setIdtGammaScale(double idtGammaScale)
 {
 idt_gamma_scale = idtGammaScale;
 }

 double DummyFlow::getIdtGammaShape() const
 {
 return idt_gamma_shape;
 }

 void DummyFlow::setIdtGammaShape(double idtGammaShape)
 {
 idt_gamma_shape = idtGammaShape;
 }

 stochastic_model DummyFlow::getIdtModel1() const
 {
 return idt_model1;
 }

 void DummyFlow::setIdtModel1(stochastic_model idtModel1)
 {
 idt_model1 = idtModel1;
 }

 stochastic_model DummyFlow::getIdtModel2() const
 {
 return idt_model2;
 }

 void DummyFlow::setIdtModel2(stochastic_model idtModel2)
 {
 idt_model2 = idtModel2;
 }

 stochastic_model DummyFlow::getIdtModel3() const
 {
 return idt_model3;
 }

 void DummyFlow::setIdtModel3(stochastic_model idtModel3)
 {
 idt_model3 = idtModel3;
 }

 stochastic_model DummyFlow::getIdtModel4() const
 {
 return idt_model4;
 }

 void DummyFlow::setIdtModel4(stochastic_model idtModel4)
 {
 idt_model4 = idtModel4;
 }

 stochastic_model DummyFlow::getIdtModel5() const
 {
 return idt_model5;
 }

 void DummyFlow::setIdtModel5(stochastic_model idtModel5)
 {
 idt_model5 = idtModel5;
 }

 stochastic_model DummyFlow::getIdtModel6() const
 {
 return idt_model6;
 }

 void DummyFlow::setIdtModel6(stochastic_model idtModel6)
 {
 idt_model6 = idtModel6;
 }

 stochastic_model DummyFlow::getIdtModel7() const
 {
 return idt_model7;
 }

 void DummyFlow::setIdtModel7(stochastic_model idtModel7)
 {
 idt_model7 = idtModel7;
 }

 stochastic_model DummyFlow::getIdtModel8() const
 {
 return idt_model8;
 }

 void DummyFlow::setIdtModel8(stochastic_model idtModel8)
 {
 idt_model8 = idtModel8;
 }

 stochastic_model DummyFlow::getIdtModel9() const
 {
 return idt_model9;
 }

 void DummyFlow::setIdtModel9(stochastic_model idtModel9)
 {
 idt_model9 = idtModel9;
 }

 double DummyFlow::getIdtNormalStdDev() const
 {
 return idt_normal_stdDev;
 }

 void DummyFlow::setIdtNormalStdDev(double idtNormalStdDev)
 {
 idt_normal_stdDev = idtNormalStdDev;
 }

 double DummyFlow::getIdtNormalMean() const
 {
 return idt_normal_mean;
 }

 void DummyFlow::setIdtNormalMean(double idtNormalMean)
 {
 idt_normal_mean = idtNormalMean;
 }

 double DummyFlow::getIdtParetoScale() const
 {
 return idt_pareto_scale;
 }

 void DummyFlow::setIdtParetoScale(double idtParetoScale)
 {
 idt_pareto_scale = idtParetoScale;
 }

 double DummyFlow::getIdtParetoShape() const
 {
 return idt_pareto_shape;
 }

 void DummyFlow::setIdtParetoShape(double idtParetoShape)
 {
 idt_pareto_shape = idtParetoShape;
 }

 double DummyFlow::getIdtPoissonMean() const
 {
 return idt_poisson_mean;
 }

 void DummyFlow::setIdtPoissonMean(double idtPoissonMean)
 {
 idt_poisson_mean = idtPoissonMean;
 }

 double DummyFlow::getIdtUniformMaxpktsize() const
 {
 return idt_uniform_maxpktsize;
 }

 void DummyFlow::setIdtUniformMaxpktsize(double idtUniformMaxpktsize)
 {
 idt_uniform_maxpktsize = idtUniformMaxpktsize;
 }

 double DummyFlow::getIdtUniformMinpktsize() const
 {
 return idt_uniform_minpktsize;
 }

 void DummyFlow::setIdtUniformMinpktsize(double idtUniformMinpktsize)
 {
 idt_uniform_minpktsize = idtUniformMinpktsize;
 }

 double DummyFlow::getIdtWeibullScale() const
 {
 return idt_weibull_scale;
 }

 void DummyFlow::setIdtWeibullScale(double idtWeibullScale)
 {
 idt_weibull_scale = idtWeibullScale;
 }

 double DummyFlow::getIdtWeibullShape() const
 {
 return idt_weibull_shape;
 }

 void DummyFlow::setIdtWeibullShape(double idtWeibullShape)
 {
 idt_weibull_shape = idtWeibullShape;
 }
 */

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

/*
 const protocolSupport& DummyFlow::getProtocols() const
 {
 return protocols;
 }

 void DummyFlow::setProtocols(const protocolSupport& protocols)
 {
 this->protocols = protocols;
 }
 */

/*
 double DummyFlow::getPsBimodalMode1Constant() const
 {
 return ps_bimodal_mode1_constant;
 }

 void DummyFlow::setPsBimodalMode1Constant(double psBimodalMode1Constant)
 {
 ps_bimodal_mode1_constant = psBimodalMode1Constant;
 }

 double DummyFlow::getPsBimodalMode1NormalDevstd() const
 {
 return ps_bimodal_mode1_normal_devstd;
 }

 void DummyFlow::setPsBimodalMode1NormalDevstd(
 double psBimodalMode1NormalDevstd)
 {
 ps_bimodal_mode1_normal_devstd = psBimodalMode1NormalDevstd;
 }

 double DummyFlow::getPsBimodalMode1NormalMean() const
 {
 return ps_bimodal_mode1_normal_mean;
 }

 void DummyFlow::setPsBimodalMode1NormalMean(double psBimodalMode1NormalMean)
 {
 ps_bimodal_mode1_normal_mean = psBimodalMode1NormalMean;
 }

 double DummyFlow::getPsBimodalMode1WeibullScale() const
 {
 return ps_bimodal_mode1_weibull_scale;
 }

 void DummyFlow::setPsBimodalMode1WeibullScale(
 double psBimodalMode1WeibullScale)
 {
 ps_bimodal_mode1_weibull_scale = psBimodalMode1WeibullScale;
 }

 double DummyFlow::getPsBimodalMode1WeibullShape() const
 {
 return ps_bimodal_mode1_weibull_shape;
 }

 void DummyFlow::setPsBimodalMode1WeibullShape(
 double psBimodalMode1WeibullShape)
 {
 ps_bimodal_mode1_weibull_shape = psBimodalMode1WeibullShape;
 }

 double DummyFlow::getPsBimodalMode2Constant() const
 {
 return ps_bimodal_mode2_constant;
 }

 void DummyFlow::setPsBimodalMode2Constant(double psBimodalMode2Constant)
 {
 ps_bimodal_mode2_constant = psBimodalMode2Constant;
 }

 double DummyFlow::getPsBimodalMode2NormalDevstd() const
 {
 return ps_bimodal_mode2_normal_devstd;
 }

 void DummyFlow::setPsBimodalMode2NormalDevstd(
 double psBimodalMode2NormalDevstd)
 {
 ps_bimodal_mode2_normal_devstd = psBimodalMode2NormalDevstd;
 }

 double DummyFlow::getPsBimodalMode2NormalMean() const
 {
 return ps_bimodal_mode2_normal_mean;
 }

 void DummyFlow::setPsBimodalMode2NormalMean(double psBimodalMode2NormalMean)
 {
 ps_bimodal_mode2_normal_mean = psBimodalMode2NormalMean;
 }

 double DummyFlow::getPsBimodalMode2WeibullScale() const
 {
 return ps_bimodal_mode2_weibull_scale;
 }

 void DummyFlow::setPsBimodalMode2WeibullScale(
 double psBimodalMode2WeibullScale)
 {
 ps_bimodal_mode2_weibull_scale = psBimodalMode2WeibullScale;
 }

 double DummyFlow::getPsBimodalMode2WeibullShape() const
 {
 return ps_bimodal_mode2_weibull_shape;
 }

 void DummyFlow::setPsBimodalMode2WeibullShape(
 double psBimodalMode2WeibullShape)
 {
 ps_bimodal_mode2_weibull_shape = psBimodalMode2WeibullShape;
 }

 stochastic_model DummyFlow::getPsBimodalTypeMode1() const
 {
 return ps_bimodal_type_mode1;
 }

 void DummyFlow::setPsBimodalTypeMode1(stochastic_model psBimodalTypeMode1)
 {
 ps_bimodal_type_mode1 = psBimodalTypeMode1;
 }

 stochastic_model DummyFlow::getPsBimodalTypeMode2() const
 {
 return ps_bimodal_type_mode2;
 }

 void DummyFlow::setPsBimodalTypeMode2(stochastic_model psBimodalTypeMode2)
 {
 ps_bimodal_type_mode2 = psBimodalTypeMode2;
 }

 int DummyFlow::getPsConstant() const
 {
 return ps_constant;
 }

 void DummyFlow::setPsConstant(int psConstant)
 {
 ps_constant = psConstant;
 }

 double DummyFlow::getPsExponential() const
 {
 return ps_exponential;
 }

 void DummyFlow::setPsExponential(double psExponential)
 {
 ps_exponential = psExponential;
 }

 stochastic_model DummyFlow::getPsModel1() const
 {
 return ps_model1;
 }

 void DummyFlow::setPsModel1(stochastic_model psModel1)
 {
 ps_model1 = psModel1;
 }

 stochastic_model DummyFlow::getPsModel2() const
 {
 return ps_model2;
 }

 void DummyFlow::setPsModel2(stochastic_model psModel2)
 {
 ps_model2 = psModel2;
 }

 stochastic_model DummyFlow::getPsModel3() const
 {
 return ps_model3;
 }

 void DummyFlow::setPsModel3(stochastic_model psModel3)
 {
 ps_model3 = psModel3;
 }

 stochastic_model DummyFlow::getPsModel4() const
 {
 return ps_model4;
 }

 void DummyFlow::setPsModel4(stochastic_model psModel4)
 {
 ps_model4 = psModel4;
 }

 stochastic_model DummyFlow::getPsModel5() const
 {
 return ps_model5;
 }

 void DummyFlow::setPsModel5(stochastic_model psModel5)
 {
 ps_model5 = psModel5;
 }

 stochastic_model DummyFlow::getPsModel6() const
 {
 return ps_model6;
 }

 void DummyFlow::setPsModel6(stochastic_model psModel6)
 {
 ps_model6 = psModel6;
 }

 stochastic_model DummyFlow::getPsModel7() const
 {
 return ps_model7;
 }

 void DummyFlow::setPsModel7(stochastic_model psModel7)
 {
 ps_model7 = psModel7;
 }

 stochastic_model DummyFlow::getPsModel8() const
 {
 return ps_model8;
 }

 void DummyFlow::setPsModel8(stochastic_model psModel8)
 {
 ps_model8 = psModel8;
 }

 double DummyFlow::getPsNormalMean() const
 {
 return ps_normal_mean;
 }

 void DummyFlow::setPsNormalMean(double psNormalMean)
 {
 ps_normal_mean = psNormalMean;
 }

 double DummyFlow::getPsNormalStdDev() const
 {
 return ps_normal_stdDev;
 }

 void DummyFlow::setPsNormalStdDev(double psNormalStdDev)
 {
 ps_normal_stdDev = psNormalStdDev;
 }

 double DummyFlow::getPsParetoScale() const
 {
 return ps_pareto_scale;
 }

 void DummyFlow::setPsParetoScale(double psParetoScale)
 {
 ps_pareto_scale = psParetoScale;
 }

 double DummyFlow::getPsParetoShape() const
 {
 return ps_pareto_shape;
 }

 void DummyFlow::setPsParetoShape(double psParetoShape)
 {
 ps_pareto_shape = psParetoShape;
 }

 double DummyFlow::getPsPoissonMean() const
 {
 return ps_poisson_mean;
 }

 void DummyFlow::setPsPoissonMean(double psPoissonMean)
 {
 ps_poisson_mean = psPoissonMean;
 }

 double DummyFlow::getPsUniformMaxpktsize() const
 {
 return ps_uniform_maxpktsize;
 }

 void DummyFlow::setPsUniformMaxpktsize(double psUniformMaxpktsize)
 {
 ps_uniform_maxpktsize = psUniformMaxpktsize;
 }

 double DummyFlow::getPsUniformMinpktsize() const
 {
 return ps_uniform_minpktsize;
 }

 void DummyFlow::setPsUniformMinpktsize(double psUniformMinpktsize)
 {
 ps_uniform_minpktsize = psUniformMinpktsize;
 }

 double DummyFlow::getPsWeibullScale() const
 {
 return ps_weibull_scale;
 }

 void DummyFlow::setPsWeibullScale(double psWeibullScale)
 {
 ps_weibull_scale = psWeibullScale;
 }

 double DummyFlow::getPsWeibullShape() const
 {
 return ps_weibull_shape;
 }

 void DummyFlow::setPsWeibullShape(double psWeibullShape)
 {
 ps_weibull_shape = psWeibullShape;
 }
 */

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

//TODO
//StochasticModelFit DummyFlow::getPacketSizeModel_next() const
//{
//}
//TODO
//void DummyFlow::setPacketSizeModel_next(StochasticModelFit* modelVet) const
//{
//}

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

