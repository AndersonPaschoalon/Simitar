/*
 * DitgFlow.h
 *
 *  Created on: 15 de set de 2017
 *      Author: anderson
 */

#ifndef DITGFLOW_H_
#define DITGFLOW_H_

#include "DummyFlow.h"

/**
 *
 */
class DitgFlow: public DummyFlow
{
public:

	/**
	 *
	 */
	DitgFlow();

	/**
	 *
	 */
	virtual ~DitgFlow();

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
	std::string ditg_command(const time_sec& onTime, const uint& npackets,
			const uint& nbytes, const string& netInterface);
};

#endif /* DITGFLOW_H_ */
