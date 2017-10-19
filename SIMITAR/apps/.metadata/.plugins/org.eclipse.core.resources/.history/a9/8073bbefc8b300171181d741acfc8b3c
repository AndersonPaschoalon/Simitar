/*
 * NetworkFlowFactory.h
 *
 *  Created on: 14 de set de 2017
 *      Author: anderson
 */

#ifndef NETWORKFLOWFACTORY_H_
#define NETWORKFLOWFACTORY_H_

// Dependencies
#include <algorithm>
#include <iostream>
#include <string>
// Simitar classes
#include "PlogMacros.h"
#include "NetworkFlow.h"
// TrafficGen tools
#include "DummyFlow.h"
#include "IperfFlow.h"
#include "DitgFlow.h"

/**
 *
 */
class NetworkFlowFactory
{
public:
	/**
	 *
	 * @param choise
	 * @return
	 */
	static NetworkFlow*  make_flow(const string& choise);


	std::string support_tools();

	/**
	 *
	 */
	NetworkFlowFactory();

	/**
	 *
	 */
	virtual ~NetworkFlowFactory();

private:

};

#endif /* NETWORKFLOWFACTORY_H_ */
