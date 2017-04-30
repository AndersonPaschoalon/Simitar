/*
 * StochasticModelFit.cpp
 *
 *  Created on: 6 de nov de 2016
 *      Author: apaschoalon
 */

#include "StochasticModelFit.h"

int compareBic(const void* a, const void* b)
{

	if ((*(StochasticModelFit*) a).bic < (*(StochasticModelFit*) b).bic)
		return -1;
	if ((*(StochasticModelFit*) a).bic == (*(StochasticModelFit*) b).bic)
		return 0;
	if ((*(StochasticModelFit*) a).bic > (*(StochasticModelFit*) b).bic)
		return 1;

	return (0);
}

int compareAic(const void* a, const void* b)
{

	if ((*(StochasticModelFit*) a).aic < (*(StochasticModelFit*) b).aic)
		return -1;
	if ((*(StochasticModelFit*) a).aic == (*(StochasticModelFit*) b).aic)
		return 0;
	if ((*(StochasticModelFit*) a).aic > (*(StochasticModelFit*) b).aic)
		return 1;

	return (0);
}
