/*
 * IperfFlow.h
 *
 *  Created on: 13 de set de 2017
 *      Author: anderson
 */

#ifndef IPERFFLOW_H_
#define IPERFFLOW_H_

#include "DummyFlow.h"

typedef enum
{
	bits, on_time, packets
} enum_transmission_type;

class IperfFlow: public DummyFlow
{
public:
	/**
	 *
	 */
	IperfFlow();

	/**
	 *
	 */
	virtual ~IperfFlow();

	/**
	 *
	 * @return
	 */
	int server();

	/**
	 *
	 * @param flowId
	 * @param onTime
	 * @param npackets
	 * @param nbytes
	 * @param netInterface
	 */
	void flowGenerate(const counter& flowId, const time_sec& onTime,
			const uint& npackets, const uint& nbytes,
			const string& netInterface);

private:
	std::string iperf_command(const time_sec& onTime, const uint& npackets,
			const uint& nbytes, const string& netInterface);

	static int iperf_server_tcp();
	static int iperf_server_udp();

};

#endif /* IPERFFLOW_H_ */
