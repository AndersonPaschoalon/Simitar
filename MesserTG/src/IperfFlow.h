/*
 * IperfFlow.h
 *
 *  Created on: 30 de abr de 2017
 *      Author: anderson
 */

#ifndef IPERFFLOW_H_
#define IPERFFLOW_H_

#include "DummyFlow.h"

class IperfFlow: public DummyFlow
{
public:

	IperfFlow()
	{
	}

	virtual ~IperfFlow()
	{
	}

	inline void flowGenerate(const counter& flowId, const time_sec& onTime,
			const unsigned int& npackets, const uint& nbytes,
			const string& netInterface)
	{
	}
};

#endif /* IPERFFLOW_H_ */
