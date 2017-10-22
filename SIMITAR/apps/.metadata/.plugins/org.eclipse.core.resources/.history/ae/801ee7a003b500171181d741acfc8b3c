/*
 * TinsFlow.h
 *
 *  Created on: 3 de out de 2017
 *      Author: anderson
 */

#ifndef TINSFLOW_H_
#define TINSFLOW_H_

#include "DummyFlow.h"
#include <tins/tins.h>

using namespace Tins;

class TinsFlow: public DummyFlow
{
public:
	TinsFlow();
	virtual ~TinsFlow();

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
	void sendPackets(uint flowID, protocol etherProtocol, protocol netProtocol,
			protocol transportProtocol, protocol application, std::string etherDst,
			std::string etherSrc, std::string netSrc, std::string netDst,
			uint ttlNumber, uint portStc, uint portDst, uint npackets, uint pktSize,
			std::string networkInterface);
};

#endif /* TINSFLOW_H_ */
