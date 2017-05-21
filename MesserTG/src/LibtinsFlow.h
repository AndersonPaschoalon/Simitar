/*
 * LibtinsFlow.h
 *
 *  Created on: 11 de mai de 2017
 *      Author: anderson
 */

#ifndef LIBTINSFLOW_H_
#define LIBTINSFLOW_H_

#include "DummyFlow.h"

class LibtinsFlow: public DummyFlow
{
public:
	LibtinsFlow();
	virtual ~LibtinsFlow();
	inline void flowGenerate(const counter& flowId, const time_sec& onTime,
			const unsigned int& npackets, const uint& nbytes,
			const string& netInterface)
	{
	}

};

#endif /* LIBTINSFLOW_H_ */
