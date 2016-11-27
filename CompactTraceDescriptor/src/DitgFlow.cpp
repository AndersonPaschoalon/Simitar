/*
 * DitgFlow.cpp
 *
 *  Created on: 16 de set de 2016
 *      Author: apaschoalon
 */

#include "DitgFlow.h"

DitgFlow::DitgFlow()
{
	// TODO Auto-generated constructor stub

}

DitgFlow::~DitgFlow()
{
	// TODO Auto-generated destructor stub
}

void DitgFlow::flowGenerate()
{
	//TODO Criar um metodo que retorna o IP de eth0 (default) da maquina atual
	char host[] = "10.1.1.48";
	string strCommand = "";
	char* command = NULL;
	int rc = 0;
	int flowDuration = 0;
	unsigned int usecs = (unsigned int) (this->getFlowStartDelay() * MEGA_POWER);

	/***************************************************************************
	 * D-ITG settings parser
	 **************************************************************************/

	/**
	 * Flow-level settings
	 */
	//duration
	flowDuration = int(this->getFlowDuration() * 1000);
	if (flowDuration == 0)
		flowDuration = 1;
	strCommand += " -t " + std::to_string(flowDuration);
	//flow start-delay
	//strCommand += " -d " + std::to_string(this->getFlowStartDelay()*1000);
	//TODO DS-byte configuration
	//DS-byte
	//strCommand += " -b " + std::to_string(this->getFlowDsByte());
	//Guarantee the mean packet rate
	strCommand += " -j 1";

	/**
	 * Network-layer settings
	 */
	//tty byte
	strCommand += " -f " + std::to_string(this->getNetworkTtl());
	//destination IPv4 address
	strCommand += " -a " + this->getHostIP();
	//strCommand += " -a " + this->getL3DstAddr();
	//TODO setar diferentes destinos IP, se possivel
	//source IPv4 address
	//strCommand += " -sa " + this->getL3SrcAddr();

	/**
	 * Transport-layer settings
	 */
	if (this->getTransportProtocol() == PROTOCOL__TCP)
	{
		strCommand += " -T TCP -D ";
		strCommand += " -rp " + std::to_string(this->getTransportDstPort());
		//strCommand += " -sp " + std::to_string(this->getL4SrcPort());
	}
	else if (this->getTransportProtocol() == PROTOCOL__UDP)
	{
		strCommand += " -T UDP ";
		strCommand += " -rp " + std::to_string(this->getTransportDstPort());
		//strCommand += " -sp " + std::to_string(this->getL4SrcPort());
	}
	else if (this->getTransportProtocol() == PROTOCOL__ICMP)
	{
		//TODO set ICMP type
		strCommand += " -T ICMP ";
	}
	else if (this->getTransportProtocol() == PROTOCOL__SCTP)
	{
		//TODO Set D-ITG compile file to support SCTP
		// To enable this option D-ITG has to be compiled with"sctp" option enabled (i.e.  make sctp=on).
		strCommand += " -T SCTP "
				+ std::to_string(this->getTransportSctpAssociationId()) + " "
				+ std::to_string(this->getTransportSctpMaxStreams()) + " ";
	}
	else if (this->getTransportProtocol() == PROTOCOL__DCCP)
	{
		//TODO Set D-ITG compile file to support DCCP
		//To enable this option D-ITG has to be compiled with "dccp" option enabled (i.e.  make dccp=on).
		strCommand += " -T DCCP ";
	}
	else
	{
		strCommand += " -T UDP -rp " + std::to_string(this->randTranportPort());
	}

	/**
	 * Inter-departure time options
	 */

	//-C  <rate>              Constant (default: 1000 pkts/s).
	//TODO select the best model
	//strCommand += " -C " + std::to_string(this->getIdtConstant());

	/**
	 * Packet size options
	 */
	//TODO choose the best model
	// now, just use the constant model
	//strCommand += " -c " + std::to_string(this->getPsConstant());

	/***************************************************************************
	 * D-ITG: generatte flow
	 **************************************************************************/
	command = new char[strCommand.length() + 1];
	strcpy(command, strCommand.c_str());

	//start-delay using usleep()
	rc = usleep(usecs);
	if (rc != 0)
	{
		perror("Error on usleep() @ DummyFlow::flowGenerate()");
		printf("\n usleep() return value was %d\n", rc);
		errno = EAGAIN;
		exit(EXIT_FAILURE);
	}

	rc = DITGsend(host, command);
	if (rc != 0)
	{
		perror("Error on  DITGsend() @ DummyFlow::flowGenerate()");
		printf("\nDITGsend() return value was %d\n", rc);
		errno = EAGAIN;
		exit(EXIT_FAILURE);
	}

	delete[] command;

#ifdef DEBUG
	cout << "D-ITG command: " << command << endl;
#endif

	return;
}
