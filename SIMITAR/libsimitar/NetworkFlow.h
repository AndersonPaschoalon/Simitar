/*
 * NetworkFlow.h
 *
 *  Created on: 15 de set de 2016
 *      Author: apaschoalon
 */

#ifndef NETWORKFLOW_H_
#define NETWORKFLOW_H_

//#define _GNU_SOURCE
//external libraries
// default
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <thread>
#include <unistd.h>
#include <pthread.h>
#include <mutex>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

//local includes
#include "Defines.h"
#include "Protocol.h"
#include "StochasticModelFit.h"
#include "RegressionTests.h"
#include "cfunctions.h"
#include "SimitarWorkspace.h"

//namespaces
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::list;
using std::vector;
using std::thread;

class NetworkFlow
{
public:

	NetworkFlow();

	virtual ~NetworkFlow();

	virtual std::thread flowThread(const std::string& netInterface) = 0;

	virtual int server(const std::string& netInterface) = 0;

	void setTimeScale(time_scale theTimeScale);

	double timeScaleFactor();

	virtual void flowGenerate(const counter& flowId, const time_sec& onTime,
			const uint& npackets, const uint& nbytes,
			const string& netInterface) = 0;

	inline int getLocalIfIp(char* interface, char* ipaddr);

	inline int getLocalIp(const char* interface, char* ipaddr);

	string print();

	string toString();

	void resetCounters();

	///
	///Return the next IP address form the destination-hosts file
	///@return
	///
	//string getHostIP();

	///
	///returns a random transport port number
	///@return
	///
	int randTranportPort();
	protocol getApplicationProtocol() const;
	void setApplicationProtocol(protocol applicationProtocol);
	uint getFlowDsByte() const;
	void setFlowDsByte(uint flowDsByte);
	double getFlowDuration() const;
	void setFlowDuration(time_sec flowDuration);
	double getFlowStartDelay() const;
	void setFlowStartDelay(time_sec flowStartDelay);

	protocol getLinkProtocol() const;
	void setLinkProtocol(protocol linkProtocol);
	void setMacAddr(const string& macSrc, const string& macDst);
	void setMacSrcAddr(const string& macSrc);
	void setMacDstAddr(const string& macDst);
	const string& getMacSrcAddr();
	const string& getMacDstAddr();

	const string& getNetworkDstAddr() const;
	void setNetworkDstAddr(const string& networkDstAddr);
	int getNetworkHostListConter() const;
	void setNetworkHostListConter(int networkHostListConter);
	protocol getNetworkProtocol() const;
	void setNetworkProtocol(protocol networkProtocol);
	const string& getNetworkSrcAddr() const;
	void setNetworkSrcAddr(const string& networkSrcAddr);
	uint getNetworkTtl() const;
	void setNetworkTtl(uint networkTtl);
	unsigned long int getNumberOfKbytes() const;
	void setNumberOfKbytes(unsigned long int numberOfKbytes);
	unsigned long int getNumberOfPackets() const;
	void setNumberOfPackets(unsigned long int numberOfPackets);

	uint getTransportDstPort() const;
	void setTransportDstPort(uint transportDstPort);
	uint getTransportSctpAssociationId() const;
	void setTransportSctpAssociationId(uint transportSctpAssociationId);
	uint getTransportSctpMaxStreams() const;
	void setTransportSctpMaxStreams(uint transportSctpMaxStreams);
	uint getTransportSrcPort() const;
	void setTransportSrcPort(uint transportSrcPort);
	protocol getTransportProtocol() const;
	void setTransportProtocol(protocol transportProtocol);

	void setInterDepertureTimeModels(list<StochasticModelFit>* modelList);
//	StochasticModelFit getInterDepertureTimeModel_next();
	StochasticModelFit getInterDepertureTimeModel(uint position);
	uint getNumberOfInterdepertureTimeModels();

	//void setInterFileTimeModel(list<StochasticModelFit>* modelList);
	//StochasticModelFit getInterFileTimeModel_next();
	//time_sec getInterFileTime();
	//uint getNumberOfInterfileTimeModels();

//	void setSessionTimesOnOff(vector<time_sec>* onTimesVec,
//			vector<time_sec>* offTimesVec);
	void setSessionTimesOnOff(vector<time_sec>* onTimesVec,
			vector<time_sec>* offTimesVec, vector<uint>* pktCounter,
			vector<uint>* fileSize);

	/**
	 * @brief Returns ON times of the traffic bursts sessions.
	 * Returns ON times of the traffic bursts sessions in a sequential order.
	 * When the available session ON values are over, it reset its counters,
	 * and starts to return the first value.
	 *
	 * @return ON times of the traffic bursts sessions
	 */
	time_sec getSessionOnTime_next();

	/**
	 * @brief Returns OFF times of the traffic bursts sessions.
	 * Returns OFF times of the traffic bursts sessions in a sequential order.
	 * When the available session ON values are over, since the size of this
	 * vector is (n-1), where n is the size of the Session On times vector,
	 * it returns 0. Then, it starts sending the first values again. It is
	 * implemented in that way, to be possible in a loop  to easely know when
	 * the Session values are.
	 * Example of usage: prints all on off times:
	 * time_sec off_time;
	 * for(;;){
	 *     std::cout << "on: " << getSessionOnTime_next()  << std::endl;
	 *     off_time = getSessionOffTime_next;
	 *     if(off_time == 0)
	 *         break;
	 *     else
	 *   	   std::cout << "off: " << off_time << endl;
	 * }
	 *
	 * @return OFF times of the traffic bursts sessions
	 */
	time_sec getSessionOffTime_next();

	/**
	 * @brief Returns number of packets of the current session refereed by the
	 * last call of getSessionOnTime_next.
	 * Example of usage: prints all on off times, and number of packets:
	 * time_sec off_time;
	 * for(;;){
	 *     std::cout << "on: " << getSessionOnTime_next() ;
	 *     std::cout << ", npkts:" << getSessionOnTime_nPackets << std::endl;
	 *     off_time = getSessionOffTime_next;
	 *     if(off_time == 0)
	 *         break;
	 *     else
	 *   	   std::cout << "off: " << off_time << endl;
	 * }
	 *
	 * @return Number of packets of the current session
	 */
	uint getSessionOnTime_nPackets() const;

	/**
	 * @brief Returns number of bytes of the current session refereed by the
	 * last call of getSessionOnTime_next.
	 * Example of usage: prints all on off times, and number of packets:
	 * time_sec off_time;
	 * for(;;){
	 *     std::cout << "on: " << getSessionOnTime_next() ;
	 *     std::cout << ", nbytes:" << getSessionOnTime_nBytes << std::endl;
	 *     off_time = getSessionOffTime_next;
	 *     if(off_time == 0)
	 *         break;
	 *     else
	 *   	   std::cout << "off: " << off_time << endl;
	 * }
	 *
	 * @return Number of bytes of the current session
	 */
	uint getSessionOnTime_nBytes() const;

	vector<time_sec>* getSessionOnVector();
	vector<time_sec>* getSessionOffVector();
	vector<uint>* getSessionOnPacketsVector();
	vector<uint>* getSessionOnBytesVector();

//	StochasticModelFit getPacketSizeModelMode1_next();
//	StochasticModelFit getPacketSizeModelMode2_next();
	StochasticModelFit getPacketSizeModelMode1(uint i);
	StochasticModelFit getPacketSizeModelMode2(uint i);

	void setPacketSizeModel(list<StochasticModelFit>* modelList1,
			list<StochasticModelFit>* modelList2, long int nkbytesMode1,
			long int nkbytesMode2, long int nPacketsMode1,
			long int nPacketsMode2);
	long int getNkbytesMode1() const;
	long int getNkbytesMode2() const;
	long int getNpacketsMode1() const;
	long int getNpacketsMode2() const;

	uint getNumberOfPsMode2Models() const;
	uint getNumberOfPsMode1Models() const;

	//DEBUG
	void printModels();

	uint getFlowId() const
	{
		return flowId;
	}

	void setFlowId(uint flowId)
	{
		this->flowId = flowId;
	}

private:

	////////////////////////////////////////////////////////////////////////////
	/// Flow-level settings
	////////////////////////////////////////////////////////////////////////////
	time_scale flow_time_scale;

	////////////////////////////////////////////////////////////////////////////
	/// Flow-level options
	////////////////////////////////////////////////////////////////////////////

	time_sec flow_duration;
	time_sec flow_start_delay;
	uint flow_ds_byte;
	unsigned long int number_of_packets;
	unsigned long int number_of_kbytes;
	uint flowId;

	////////////////////////////////////////////////////////////////////////////
	/// Protocol stack options
	////////////////////////////////////////////////////////////////////////////

	/// L2: Link Layer
	protocol link_protocol;
	string mac_src;
	string mac_dst;

	/// L3: Network Layer
	uint network_ttl;
	protocol network_protocol;
	string network_dst_addr;
	string network_src_addr;
	int network_hostList_conter;

	///L4: Transport Layer
	uint transport_dst_port;
	uint transport_src_port;
	protocol transport_protocol;
	uint transport_sctp_association_id;
	uint transport_sctp_max_streams;

	/// L5: Application Layer
	protocol application_protocol;

	////////////////////////////////////////////////////////////////////////////
	/// Interperture time
	////////////////////////////////////////////////////////////////////////////

	/// Interarrival
	list<StochasticModelFit>* ptr_interArrivalModelList; //file interdeperture time
	//counter interDepertureTimeModel_counter = 0; //counter of for model get method
	/// Session on/off

	////////////////////////////////////////////////////////////////////////////
	/// Session model
	////////////////////////////////////////////////////////////////////////////
	vector<time_sec>* ptr_session_onTimes;
	vector<time_sec>* ptr_session_offTimes;
	vector<uint>* ptr_session_nPackets;
	vector<uint>* ptr_session_nBytes;
	counter sessionOnTimes_counter = -1;
	counter sessionOffTimes_counter = 0;

	////////////////////////////////////////////////////////////////////////////
	///Packet Size Model
	////////////////////////////////////////////////////////////////////////////

	list<StochasticModelFit>* ptr_psMode1;
	list<StochasticModelFit>* ptr_psMode2;
	long int nkbytes_mode1;
	long int nkbytes_mode2;
	long int npacket_mode1;
	long int npackets_mode2;
	//counter packetSizeModel1_counter;
	//counter packetSizeModel2_counter;

};

#endif /* NETWORKFLOW_H_ */
