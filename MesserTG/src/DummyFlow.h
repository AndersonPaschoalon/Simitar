/*
 * DummyFlow.h
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#ifndef DUMMYFLOW_H_
#define DUMMYFLOW_H_

#include "NetworkFlow.h"
/*
 TODO Implementation of L2 data structures
 typedef struct mac_dst_n {
 string mac_dst;
 unsigned float frequency; //0-1
 struct mac_dst_n* next;
 }mac_dst_node;

 typedef struct l2_addr_list{
 string mac_src;
 unsigned long int mac_dst_count;
 mac_dst_node nodes;
 struct l2_addr_list* next;
 } l2_addr;
 */

class DummyFlow: public NetworkFlow
{
public:
	/**
	 *
	 */
	DummyFlow();

	/**
	 *
	 */
	virtual ~DummyFlow();

	/**
	 *
	 */
	void print();

	/**
	 *
	 * @return
	 */
	void flowGenerate(counter flowId, time_sec onTime, unsigned int npackets,
			string netInterface);

	std::thread flowThread()
	{
		MESSER_LOG_INIT(INFO);
		MESSER_DEBUG("std::thread flowThread() ok! @<%s, %s>");

		counter flowId = 0;
		time_sec onTime = 0;
		unsigned int npackets = 0;
		string netInterface = "";

		return std::thread([=]
		{	flowGenerate(flowId, onTime, npackets, netInterface);});
	}

};

#endif /* DUMMYFLOW_H_ */
