/*
 * DummyFlow.h
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#ifndef DUMMYFLOW_H_
#define DUMMYFLOW_H_

#include "NetworkFlow.h"

class DummyFlow: public NetworkFlow
{
public:
	/**
	 * Sleep method used between packet trains and for inter-pacekt times, provided
	 * by the fsleep() method (flow sleep).
	 * method_usleep:
	 */
	typedef enum
	{
		method_usleep, method_pooling, method_select
	} sleep_method;

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
	 * @return
	 */
	int server(const std::string& netInterface);

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
			const std::string& netInterface);

	void flowStart(const std::string& netInterface);

	std::thread flowThread(const std::string& netInterface)
	{
		return std::thread([=]
		{	flowStart(netInterface);});
	}

private:

	/**
	 *
	 * @param sleep_time
	 */
	void fsleep(time_sec sleep_time, sleep_method sleepMethod);

};

#endif /* DUMMYFLOW_H_ */
