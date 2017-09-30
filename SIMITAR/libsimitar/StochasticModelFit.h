/*
 * StochasticModelFit.h
 *
 *  Created on: 6 de nov de 2016
 *      Author: apaschoalon
 */

#ifndef STOCHASTICMODELFIT_H_
#define STOCHASTICMODELFIT_H_

#include <cmath>
#include <cfloat>
#include <armadillo>
#include <string>
#include <string.h>
#include <math.h>
#include <random>
#include <chrono>

#include "Defines.h"
#include "RegressionTests.h"

using namespace arma;

/**
 *
 */
typedef enum stochastic_functions_enum
{
	WEIBULL,                      //!< WEIBULL
	NORMAL,                       //!< NORMAL
	EXPONENTIAL,                  //!< EXPONENTIAL
	EXPONENTIAL_MEAN,             //!< EXPONENTIAL_MEAN
	EXPONENTIAL_LINEAR_REGRESSION,            //!< EXPONENTIAL_LINEAR_REGRESSION
	PARETO,                       //!< PARETO
	PARETO_LINEAR_REGRESSION,     //!< PARETO_LINEAR_REGRESSION
	PARETO_MAXIMUM_LIKEHOOD,      //!< PARETO_MAXIMUM_LIKEHOOD
	CAUCHY,                       //!< CAUCHY
	CONSTANT,                     //!< CONSTANT
	SINGLE_PACKET,                //!< SINGLE_PACKET
	NO_MODEL                      //!< NO_MODEL
} stochastic_functions;

/**
 *
 */
typedef enum information_criterion_enum
{
	AIC, BIC
} information_criterion;

/**
 *
 */
class StochasticModelFit
{
public:
	/**
	 * @brief Creates a not void stochastic model
	 */
	StochasticModelFit()
	{
		m_modelName = NO_MODEL;
		m_param1 = 0;
		m_param2 = 0;
		m_aic = datum::nan;
		m_bic = datum::nan;
	}

	/**
	 * @brief Create a stochastic model.
	 * Creates a stochastic model, with its name (enum stochastic_functions
	 * type, std::string or C string format), first and second parameters,
	 * and AIC and BIC criterion. If there is no second parameter, it should
	 * be filled with zero. Currently it supports the follow distributions:
	 *	- Weibull distribution
	 *		\f[
	 *		f(t) = \begin{cases}
	 *				\frac{\alpha}{\beta^\alpha}t^{\alpha - 1}e^{(t/\beta)^{\alpha}}; & t \geq 0 \\
		 *				0; & t < 0
	 *			\end{cases}
	 *		\f]
	 *	- Normal distribution
	 *		\f[
	 *		f(t) =  \frac{1}{\sqrt[]{2\sigma^2}\pi}e^{\frac{(t - \mu)^2}{2\sigma^2}}
	 *		\f]
	 *	- Exponential distribution
	 *		\f[
	 *		f(t) = 	\begin{cases}
	 *					\lambda e^{-\lambda t} ; & t \geq 0  \\
		 *					0; & t < 0
	 *				\end{cases}
	 *		\f]
	 *	- Pareto distibution
	 *		\f[ f(t) =	\begin{cases}
	 *				\frac{
	 *					\alpha t_{m}^\alpha}{t^{\alpha + 1}} ;& t \geq t_{m} \\
		 *					0;& t < t_{m}
	 *				\end{cases}
	 *		\f]
	 *	- Cauchy distribution
	 *		\f[ f(t) = \frac{1}{\pi \gamma}[\frac{\gamma^2}{(t - t_{0})^{2} + \gamma^{2}}] \f]
	 *	On each case, the parameter order follow its alphabetical order.
	 *	The current relationship between parameters are:
	 *
	 *	- Weibull: \f$ (\alpha, \beta ) = (shape, scale) = (param1, param2)\f$;
	 *
	 *	- Normal: \f$ (\mu, \sigma = (mean, standard deviation) = (param1, param2)\f$;
	 *
	 *	- Exponential \f$ (\lambda ) = (rate) = (param1)\f$;
	 *
	 *	- Pareto: \f$( \alpha, x_m) = (shape, scale) = (param1, param2) \f$;
	 *
	 *	- Cauchy: \f$(\gamma, x_0) =  (scale, location) = (param1, param2)\f$.
	 *
	 *  Notice that on Cauchy distribution the first parameter is the scale!
	 *
	 * @param sf stochastic function
	 * @param param1 first parameter (alphabetical order)
	 * @param param2 second parameter (alphabetical order)
	 * @param aic <a href="https://en.wikipedia.org/wiki/Akaike_information_criterion">
	 * 			Akaike information criterion</a>
	 * @param bic <a href="https://en.wikipedia.org/wiki/Bayesian_information_criterion">
	 * 			Bayesian information criterion</a>
	 */
	StochasticModelFit(stochastic_functions sf, double param1, double param2,
			double aic, double bic)
	{
		set(sf, param1, param2, aic, bic);
	}

	StochasticModelFit(char* modelStr, double param1, double param2, double aic,
			double bic)
	{
		set(modelStr, param1, param2, aic, bic);
	}

	StochasticModelFit(const std::string& modelStr, double param1, double param2,
			double aic, double bic)
	{
		set(modelStr, param1, param2, aic, bic);
	}

	/**
	 *
	 * @return
	 */
	double aic() const
	{
		return (m_aic);
	}
	double bic() const
	{
		return (m_bic);
	}
	std::string strModelName() const
	{
		std::string strRet;

		if (m_modelName == WEIBULL)
		{
			strRet = "weibull";
		}
		else if (m_modelName == NORMAL)
		{
			strRet = "normal";
		}
		else if (m_modelName == EXPONENTIAL)
		{
			strRet = "exponential";
		}
		else if (m_modelName == EXPONENTIAL_LINEAR_REGRESSION)
		{
			strRet = "exponential-lr";
		}
		else if (m_modelName == EXPONENTIAL_MEAN)
		{
			strRet = "exponential-me";
		}
		else if (m_modelName == PARETO)
		{
			strRet = "pareto";
		}
		else if (m_modelName == PARETO_LINEAR_REGRESSION)
		{
			strRet = "pareto-lt";
		}
		else if (m_modelName == PARETO_MAXIMUM_LIKEHOOD)
		{
			strRet = "pareto-ml";
		}
		else if (m_modelName == CAUCHY)
		{
			strRet = "cauchy";
		}
		else if (m_modelName == CONSTANT)
		{
			strRet = "constant";
		}
		else if (m_modelName == SINGLE_PACKET)
		{
			strRet = "single-packet";
		}
		else if (m_modelName == NO_MODEL)
		{
			strRet = "no-model-selected";
		}
		else
		{
			//TODO
		}

		return (strRet);
	}

	// <TESTED>
	void strModelName(char* cStr) const
	{
		//MESSER_LOG_INIT(LOG_LEVEL_SF);

		if (m_modelName == WEIBULL)
		{
			strcpy(cStr, LABEL_WEIBULL);
		}
		else if (m_modelName == NORMAL)
		{
			strcpy(cStr, LABEL_NORMAL);
		}
		else if (m_modelName == EXPONENTIAL)
		{
			strcpy(cStr, LABEL_EXPONENTIAL);
		}
		else if (m_modelName == EXPONENTIAL_LINEAR_REGRESSION)
		{
			strcpy(cStr, LABEL_EXPONENTIAL_LINEAR_REGRESSION);
		}
		else if (m_modelName == EXPONENTIAL_MEAN)
		{
			strcpy(cStr, LABEL_EXPONENTIAL_MEAN);
		}
		else if (m_modelName == PARETO)
		{
			strcpy(cStr, LABEL_PARETO);
		}
		else if (m_modelName == PARETO_LINEAR_REGRESSION)
		{
			strcpy(cStr, LABEL_PARETO_LINEAR_REGRESSION);
		}
		else if (m_modelName == PARETO_MAXIMUM_LIKEHOOD)
		{
			strcpy(cStr, LABEL_PARETO_MAXIMUM_LIKEHOOD);
		}
		else if (m_modelName == CAUCHY)
		{
			strcpy(cStr, LABEL_CAUCHY);
		}
		else if (m_modelName == CONSTANT)
		{
			strcpy(cStr, LABEL_CONSTANT);
		}
		else if (m_modelName == SINGLE_PACKET)
		{
			strcpy(cStr, LABEL_SINGLE_PACKET);
		}
		else if (m_modelName == NO_MODEL)
		{
			strcpy(cStr, LABEL_NO_MODEL);
		}
		else
		{
			fprintf(stderr,
					"Error: No valid stochastic model. m_modelName=`%d`. Returning default value: `%s`\n",
					m_modelName, LABEL_NO_MODEL);
			//MESSER_CRIT(
			//		"Error: No valid stochastic model. m_modelName=`%d`. Returning default value: `%s`  @<%s, %s>",
			//		m_modelName, LABEL_NO_MODEL);
		}

		//MESSER_LOG_END();
	}
	stochastic_functions modelName() const
	{
		return (m_modelName);
	}

	double param1() const
	{
		return (m_param1);
	}

	double param2() const
	{
		return (m_param2);
	}

	/**
	 * @brief Set and stochastic model.
	 * Set a stochastic model, with its name (enum stochastic_functions
	 * type, std::string or C string format), first and second parameters,
	 * and AIC and BIC criterion. If there is no second parameter, it should
	 * be filled with zero. Currently it supports the follow distributions:
	 *	- Weibull distribution
	 *		\f[
	 *		f(t) = \begin{cases}
	 *				\frac{\alpha}{\beta^\alpha}t^{\alpha - 1}e^{(t/\beta)^{\alpha}}; & t \geq 0 \\
		 *				0; & t < 0
	 *			\end{cases}
	 *		\f]
	 *	- Normal distribution
	 *		\f[
	 *		f(t) =  \frac{1}{\sqrt[]{2\sigma^2}\pi}e^{\frac{(t - \mu)^2}{2\sigma^2}}
	 *		\f]
	 *	- Exponential distribution
	 *		\f[
	 *		f(t) = 	\begin{cases}
	 *					\lambda e^{-\lambda t} ; & t \geq 0  \\
		 *					0; & t < 0
	 *				\end{cases}
	 *		\f]
	 *	- Pareto distibution
	 *		\f[ f(t) =	\begin{cases}
	 *				\frac{
	 *					\alpha t_{m}^\alpha}{t^{\alpha + 1}} ;& t \geq t_{m} \\
		 *					0;& t < t_{m}
	 *				\end{cases}
	 *		\f]
	 *	- Cauchy distribution
	 *		\f[ f(t) = \frac{1}{\pi \gamma}[\frac{\gamma^2}{(t - t_{0})^{2} + \gamma^{2}}] \f]
	 *	On each case, the parameter order follow its alphabetical order.
	 *	The current relationship between parameters are:
	 *
	 *	- Weibull: \f$ (\alpha, \beta ) = (shape, scale) = (param1, param2)\f$;
	 *
	 *	- Normal: \f$ (\mu, \sigma = (mean, standard deviation) = (param1, param2)\f$;
	 *
	 *	- Exponential \f$ (\lambda ) = (rate) = (param1)\f$;
	 *
	 *	- Pareto: \f$( \alpha, x_m) = (shape, scale) = (param1, param2) \f$;
	 *
	 *	- Cauchy: \f$(\gamma, x_0) =  (scale, location) = (param1, param2)\f$.
	 *
	 *  Notice that on Cauchy distribution the first parameter is the scale!
	 *
	 * @param sf stochastic function
	 * @param param1 first parameter (alphabetical order)
	 * @param param2 second parameter (alphabetical order)
	 * @param aic <a href="https://en.wikipedia.org/wiki/Akaike_information_criterion">
	 * 			Akaike information criterion</a>
	 * @param bic <a href="https://en.wikipedia.org/wiki/Bayesian_information_criterion">
	 * 			Bayesian information criterion</a>
	 */
	void set(stochastic_functions sf, double param1, double param2, double aic,
			double bic)
	{
		m_modelName = sf;
		m_param1 = param1;
		m_param2 = param2;
		m_aic = aic;
		m_bic = bic;
	}

	/**
	 * @brief Set and stochastic model
	 * Set a stochastic model, with its name (enum stochastic_functions
	 * type, std::string or C string format), first and second parameters,
	 * and AIC and BIC criterion. If there is no second parameter, it should
	 * be filled with zero. Currently it supports the follow distributions:
	 *	- Weibull distribution
	 *		\f[
	 *		f(t) = \begin{cases}
	 *					\frac{\alpha}{\beta^\alpha}t^{\alpha - 1}e^{(t/\beta)^{\alpha}}; & t \geq 0 \\
	 *					0; & t < 0
	 *				\end{cases}
	 *		\f]
	 *	- Normal distribution
	 *		\f[
	 *		f(t) =  \frac{1}{\sqrt[]{2\sigma^2}\pi}e^{\frac{(t - \mu)^2}{2\sigma^2}}
	 *		\f]
	 *	- Exponential distribution
	 *		\f[
	 *		f(t) = 	\begin{cases}
	 *					\lambda e^{-\lambda t} ; & t \geq 0  \\
	 *					 0; & t < 0
	 *				\end{cases}
	 *		\f]
	 *	- Pareto distibution
	 *		\f[
	 *		f(t) =	\begin{cases}
	 *					\frac{\alpha t_{m}^\alpha}{t^{\alpha + 1}} ;& t \geq t_{m}
	 *					\\ 0;& t < t_{m}
	 *				\end{cases}
	 *		\f]
	 *	- Cauchy distribution
	 *		\f[
	 *		f(t) = \frac{1}{\pi \gamma}[\frac{\gamma^2}{(t - t_{0})^{2} + \gamma^{2}}]
	 *		\f]
	 *	On each case, the parameter order follow its alphabetical order.
	 *	The current relationship between parameters are:
	 *	- Weibull: \f$ (\alpha, \beta ) = (shape, scale) = (param1, param2)\f$
	 *	- Normal: \f$ (\mu, \sigma = (mean, standard deviation) = (param1, param2)\f$
	 *	- Exponential \f$ (\lambda ) = (rate) = (param1)\f$
	 *	- Pareto: (\f$ \alpha, x_m) = (shape, scale) = (param1, param2)\f$
	 *	- Cauchy: \f$(\gamma, x_0) =  (scale, location) = (param1, param2)\f$
	 *  Notice that on Cauchy distribution the first parameter is the scale!
	 *
	 * @param modelStr
	 * @param param1
	 * @param param2
	 * @param aic
	 * @param bic
	 * @return 	returns 0 in success, and -1 if the model's name string
	 * 			(modelStr) has a invalid name. In this case, the parameters are
	 * 			setted, and the model name is set to NO_MODEL.
	 */
	int set(char* modelStr, double param1, double param2, double aic,
			double bic)
	{
		int setRet = set(std::string(modelStr), param1, param2, aic, bic);
		return (setRet);
	}

	/**
	 * @brief Set and stochastic model
	 * Set a stochastic model, with its name (enum stochastic_functions
	 * type, std::string or C string format), first and second parameters,
	 * and AIC and BIC criterion. If there is no second parameter, it should
	 * be filled with zero. Currently it supports the follow distributions:
	 *	- Weibull distribution
	 *		\f[
	 *		f(t) = \begin{cases}
	 *					\frac{\alpha}{\beta^\alpha}t^{\alpha - 1}e^{(t/\beta)^{\alpha}}; & t \geq 0 \\
	 *					0; & t < 0
	 *				\end{cases}
	 *		\f]
	 *	- Normal distribution
	 *		\f[
	 *		f(t) =  \frac{1}{\sqrt[]{2\sigma^2}\pi}e^{\frac{(t - \mu)^2}{2\sigma^2}}
	 *		\f]
	 *	- Exponential distribution
	 *		\f[
	 *		f(t) = 	\begin{cases}
	 *					\lambda e^{-\lambda t} ; & t \geq 0  \\
	 *					 0; & t < 0
	 *				\end{cases}
	 *		\f]
	 *	- Pareto distibution
	 *		\f[
	 *		f(t) =	\begin{cases}
	 *					\frac{\alpha t_{m}^\alpha}{t^{\alpha + 1}} ;& t \geq t_{m}
	 *					\\ 0;& t < t_{m}
	 *				\end{cases}
	 *		\f]
	 *	- Cauchy distribution
	 *		\f[
	 *		f(t) = \frac{1}{\pi \gamma}[\frac{\gamma^2}{(t - t_{0})^{2} + \gamma^{2}}]
	 *		\f]
	 *	On each case, the parameter order follow its alphabetical order.
	 *	The current relationship between parameters are:
	 *	- Weibull: \f$ (\alpha, \beta ) = (shape, scale) = (param1, param2)\f$
	 *	- Normal: \f$ (\mu, \sigma = (mean, standard deviation) = (param1, param2)\f$
	 *	- Exponential \f$ (\lambda ) = (rate) = (param1)\f$
	 *	- Pareto: (\f$ \alpha, x_m) = (shape, scale) = (param1, param2)\f$
	 *	- Cauchy: \f$(\gamma, x_0) =  (scale, location) = (param1, param2)\f$
	 *  Notice that on Cauchy distribution the first parameter is the scale!
	 *
	 * @param modelStr
	 * @param param1
	 * @param param2
	 * @param aic
	 * @param bic
	 * @return 	returns 0 in success, and -1 if the model's name string
	 * 			(modelStr) has a invalid name. In this case, the parameters are
	 * 			setted, and the model name is set to NO_MODEL.
	 */
	int set(const std::string& modelStr, double param1, double param2, double aic,
			double bic)
	{
		stochastic_functions sf;
		int setRet = 0;

		if (modelStr == std::string(LABEL_WEIBULL))
		{
			sf = WEIBULL;
		}
		else if (modelStr == std::string(LABEL_NORMAL))
		{
			sf = NORMAL;
		}
		else if (modelStr == std::string(LABEL_EXPONENTIAL))
		{
			sf = EXPONENTIAL;
		}
		else if (modelStr == std::string(LABEL_EXPONENTIAL_LINEAR_REGRESSION))
		{
			sf = EXPONENTIAL_LINEAR_REGRESSION;
		}
		else if (modelStr == std::string(LABEL_EXPONENTIAL_MEAN))
		{
			sf = EXPONENTIAL_MEAN;
		}
		else if (modelStr == std::string(LABEL_PARETO))
		{
			sf = PARETO;
		}
		else if (modelStr == std::string(LABEL_PARETO_LINEAR_REGRESSION))
		{
			sf = PARETO_LINEAR_REGRESSION;
		}
		else if (modelStr == std::string(LABEL_PARETO_MAXIMUM_LIKEHOOD))
		{
			sf = PARETO_MAXIMUM_LIKEHOOD;
		}
		else if (modelStr == std::string(LABEL_CAUCHY))
		{
			sf = CAUCHY;
		}
		else if (modelStr == std::string(LABEL_CONSTANT))
		{
			sf = CONSTANT;
		}
		else if (modelStr == std::string(LABEL_SINGLE_PACKET))
		{
			sf = SINGLE_PACKET;
		}
		else if (modelStr == std::string(LABEL_NO_MODEL))
		{
			sf = NO_MODEL;
		}
		else
		{
			fprintf(stderr,
					"Error: No valid stochastic model name `%s`. Setting default value: `%s`\n",
					modelStr.c_str(), LABEL_NO_MODEL);
			setRet = -1;
			sf = NO_MODEL;
		}
		set(sf, param1, param2, aic, bic);

		return (setRet);
	}

	/**
	 * Define the information criterion to be uses as comparator ">" and "<"
	 * between models. So, the stochastic models are ordered according this
	 * value.
	 *
	 * @param infoCrit
	 */
	void setInforCriterion(information_criterion infoCrit)
	{
		m_infoCrit = infoCrit;
	}

	bool operator <(const StochasticModelFit& smf) const
	{
		if (m_infoCrit == AIC)
		{
			return (m_aic < smf.aic());
		}
		else
		{
			return (m_bic < smf.bic());
		}
	}

	bool operator >(const StochasticModelFit& smf) const
	{
		if (m_infoCrit == AIC)
		{
			return (m_aic > smf.aic());
		}
		else
		{
			return (m_bic > smf.bic());
		}
	}

	/**
	 * @brief
	 *
	 * @param other
	 */
	StochasticModelFit(const StochasticModelFit& other)
	{
		m_modelName = other.modelName();
		m_param1 = other.param1();
		m_param2 = other.param2();
		m_aic = other.aic();
		m_bic = other.bic();
	}

	/**
	 * @brief
	 *
	 * @param other
	 * @return
	 */
	StochasticModelFit& operator=(const StochasticModelFit& other) noexcept
	{
		if (this != &other)
		{
			//m_modelName = other.m_modelName;
			m_modelName = other.modelName();
			m_param1 = other.param1();
			m_param2 = other.param2();
			m_aic = other.aic();
			m_bic = other.bic();
			m_infoCrit = other.m_infoCrit;
		}
		else
		{
			cerr
					<< "Attempted assignment of a StochasticModelFit object to itself"
					<< endl;
		}

		return (*this);
	}

	/**
	 * @brief
	 */
	void print() const
	{
		cout << strModelName() << "(" << m_param1 << ", " << m_param1 << ") "
				<< "aic=" << m_aic << ", bic=" << m_bic << endl;
	}

	/**
	 * @brief
	 *
	 * @return
	 */
	double getRandom()
	{
		unsigned seed =
				std::chrono::system_clock::now().time_since_epoch().count();
		return (getRandom(seed));
	}

	/**
	 * @brief
	 *
	 * @param seed
	 * @return
	 */
	double getRandom(unsigned seed)
	{

		//MESSER_LOG_INIT(LOG_LEVEL_SF);
		double retVal = .0;

		std::ranlux48 generator(seed);
		if (m_modelName == WEIBULL)
		{
			// (alpha, beta) = (shape, scale) = (a, b)
			std::weibull_distribution<double> distribution(m_param1, m_param2);
			retVal = distribution(generator);
		}
		else if (m_modelName == NORMAL)
		{
			// (mu, std) = (mean, standar_deviation)
			std::normal_distribution<double> distribution(m_param1, m_param2);
			retVal = distribution(generator);
		}
		else if ((m_modelName == EXPONENTIAL)
				|| (m_modelName == EXPONENTIAL_LINEAR_REGRESSION)
				|| (m_modelName == EXPONENTIAL_MEAN))
		{
			std::exponential_distribution<double> distribution(m_param1);
			retVal = distribution(generator);
		}
		else if ((m_modelName == PARETO)
				|| (m_modelName == PARETO_LINEAR_REGRESSION)
				|| (m_modelName == PARETO_MAXIMUM_LIKEHOOD))
		{
			// No std function offered in C++ standar library, so we use
			// Exponential to Pareto transformation
			// https://en.wikipedia.org/wiki/Pareto_distribution#Relation_to_the_exponential_distribution
			// It says that if X is a Pareto random variable and Y is
			// a exponential ramdom variable, with rate parameter alpha:
			// X = x_m * exp(Y)
			// therefore, after the transformation, we have:
			// alpha === lambda,
			std::exponential_distribution<double> distribution(m_param1);
			retVal = m_param2 * exp(distribution(generator));
		}
		else if (m_modelName == CAUCHY)
		{
			//http://www.cplusplus.com/reference/random/cauchy_distribution/cauchy_distribution/
			//https://en.wikipedia.org/wiki/Cauchy_distribution
			// a === location(x0), b === scale(gamma)
			std::cauchy_distribution<double> distribution(m_param2, m_param1);
			retVal = distribution(generator);
		}
		else if ((m_modelName == CONSTANT) || (m_modelName == SINGLE_PACKET))
		{
			retVal = m_param1;
		}
		else if (m_modelName == NO_MODEL)
		{
			retVal = 0;
		}
		else
		{
			fprintf(stderr,
					"Error: No valid stochastic model (It is `%s)`. Returning default value: `%f`\n",
					this->strModelName().c_str(), .0);
			//MESSER_CRIT(
			//		"Error: No valid stochastic model (It is `%s)`. Returning default value: `%f`  @<%s, %s>",
			//		this->strModelName().c_str(), .0);
		}

		//MESSER_LOG_END();
		return (retVal);
	}

	void unity_tests()
	{
		RegressionTests rt;

		rt.printHeader("class StochasticModelFit");
		rt.printTestResult("set method", test_set());
		rt.printTestResult("getRandom method", test_ramdom());
	}

private:

	////////////////////////////////////////////////////////////////////////////
	/// Members
	////////////////////////////////////////////////////////////////////////////
	stochastic_functions m_modelName;
	double m_aic;
	double m_bic;
	double m_param1;
	double m_param2;
	information_criterion m_infoCrit = AIC;

	////////////////////////////////////////////////////////////////////////////
	/// Constants
	////////////////////////////////////////////////////////////////////////////
	static const char * LABEL_WEIBULL;
	static const char * LABEL_NORMAL;
	static const char * LABEL_EXPONENTIAL;
	static const char * LABEL_EXPONENTIAL_MEAN;
	static const char * LABEL_EXPONENTIAL_LINEAR_REGRESSION;
	static const char * LABEL_PARETO;
	static const char * LABEL_PARETO_LINEAR_REGRESSION;
	static const char * LABEL_PARETO_MAXIMUM_LIKEHOOD;
	static const char * LABEL_CAUCHY;
	static const char * LABEL_CONSTANT;
	static const char * LABEL_SINGLE_PACKET;
	static const char * LABEL_NO_MODEL;

	////////////////////////////////////////////////////////////////////////////
	/// Unity tests
	////////////////////////////////////////////////////////////////////////////
	bool test_set()
	{
		//MESSER_LOG_INIT(LOG_LEVEL_SF);

		cout << "*4 Error messages should appear now*" << endl;

		int rr = 0;
		double alpha = 1.2;
		double beta = 0.314;
		double aa = -15;
		double bb = -7;
		char charM1[100];
		char charM2[100];
		strcpy(charM1, LABEL_CAUCHY);
		strcpy(charM2, LABEL_NO_MODEL);
		char charM3[] = "Blind Guardian";
		char charM4[] = "NO_MODEL";
		std::string strM1 = LABEL_CAUCHY;
		std::string strM2 = LABEL_NO_MODEL;
		std::string strM3 = "Blind Guardian";
		std::string strM4 = "NO_MODEL";
		char charM5[100];
		char charM6[100];
		char charM7[100];
		char charM8[100];
		char charM9[100];
		char charM10[100];
		char charM11[100];
		char charM12[100];
		char charM13[100];
		char charM14[100];
		char charM15[100];
		char charM16[100];
		strcpy(charM5, LABEL_EXPONENTIAL);
		strcpy(charM6, LABEL_EXPONENTIAL_LINEAR_REGRESSION);
		strcpy(charM7, LABEL_EXPONENTIAL_MEAN);
		strcpy(charM8, LABEL_NORMAL);
		strcpy(charM9, LABEL_NO_MODEL);
		strcpy(charM10, LABEL_PARETO);
		strcpy(charM11, LABEL_PARETO_LINEAR_REGRESSION);
		strcpy(charM12, LABEL_PARETO_MAXIMUM_LIKEHOOD);
		strcpy(charM13, LABEL_SINGLE_PACKET);
		strcpy(charM14, LABEL_WEIBULL);
		strcpy(charM15, LABEL_CAUCHY);
		strcpy(charM16, LABEL_CONSTANT);

		//MESSER_DEBUG("charM1=%s  @<%s, %s>", charM1);

		/// char
		rr = set(charM1, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM1);
			return (false);
		}
		rr = set(charM2, alpha, beta, aa, bb);
		if (rr < 0)
		{
			return (false);
		}
		rr = set(charM3, alpha, beta, aa, bb);
		if (rr == 0)
		{
			return (false);
		}
		rr = set(charM4, alpha, beta, aa, bb);
		if (rr == 0)
		{
			return (false);
		}
		/// string
		rr = set(strM1, alpha, beta, aa, bb);
		if (rr < 0)
		{
			return (false);
		}
		rr = set(strM2, alpha, beta, aa, bb);
		if (rr < 0)
		{
			return (false);
		}
		rr = set(strM3, alpha, beta, aa, bb);
		if (rr == 0)
		{
			return (false);
		}
		rr = set(strM4, alpha, beta, aa, bb);
		if (rr == 0)
		{
			return (false);
		}
		rr = set(charM5, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM5);
			return (false);
		}
		rr = set(charM6, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM6);
			return (false);
		}
		rr = set(charM6, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM6);
			return (false);
		}
		rr = set(charM6, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM6);
			return (false);
		}
		rr = set(charM7, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM7);
			return (false);
		}
		rr = set(charM8, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM8);
			return (false);
		}
		rr = set(charM9, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM9);
			return (false);
		}
		rr = set(charM10, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM10);
			return (false);
		}
		rr = set(charM11, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM11);
			return (false);
		}
		rr = set(charM12, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM12);
			return (false);
		}
		rr = set(charM13, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM13);
			return (false);
		}
		rr = set(charM14, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM14);
			return (false);
		}
		rr = set(charM15, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM15);
			return (false);
		}
		rr = set(charM16, alpha, beta, aa, bb);
		if (rr < 0)
		{
			//MESSER_CRIT("Test error at %s  @<%s, %s>", charM16);
			return (false);
		}

		//MESSER_LOG_END();
		return (true);
	}

	bool test_ramdom()
	{
		cout << "getRandom: This is a just a visual test\n";

		const int nrolls = 1000; // number of experiments
		const int nstars = 500; // maximum number of stars to distribute

		this->set(WEIBULL, 2.0, 4.0, 0, 0);
		unsigned seed = 77;
		int pw[10] =
		{ };

		for (int i = 0; i < nrolls; ++i)
		{
			double number = this->getRandom(seed);
			seed++;
			if (number < 10)
				++pw[int(number)];
		}

		std::cout << "weibull_distribution (2.0,4.0):" << std::endl;

		for (int i = 0; i < 10; ++i)
		{
			std::cout << i << "-" << (i + 1) << ": ";
			std::cout << std::string(pw[i] * nstars / nrolls, '*') << std::endl;
		}

		this->set(EXPONENTIAL, 3.5, 0, 0, 0);

		const int nintervals = 20; // number of intervals

		int pe[nintervals] =
		{ };

		for (int i = 0; i < nrolls; ++i)
		{
			double number = this->getRandom();
			if (number < 1.0)
				++pe[int(nintervals * number)];
		}

		std::cout << "exponential_distribution (3.5):" << std::endl;
		std::cout << std::fixed;
		std::cout.precision(1);

		for (int i = 0; i < nintervals; ++i)
		{
			std::cout << float(i) / nintervals << "-"
					<< float(i + 1) / nintervals << ": ";
			std::cout << std::string(pe[i] * nstars / nrolls, '*') << std::endl;
		}

		this->set(NORMAL, 5.0, 2.0, 0, 0);

		int pn[10] =
		{ };

		for (int i = 0; i < nrolls; ++i)
		{
			double number = this->getRandom();
			if ((number >= 0.0) && (number < 10.0))
				++pn[int(number)];
		}

		std::cout << "normal_distribution (5.0,2.0):" << std::endl;

		for (int i = 0; i < 10; ++i)
		{
			std::cout << i << "-" << (i + 1) << ": ";
			std::cout << std::string(pn[i] * nstars / nrolls, '*') << std::endl;
		}

		this->set(CAUCHY, 5.0, 1.0, 0, 0);

		int pc[10] =
		{ };

		for (int i = 0; i < nrolls; ++i)
		{
			double number = this->getRandom();
			if ((number >= 0.0) && (number < 10.0))
				++pc[int(number)];
		}

		std::cout << "cauchy_distribution (5.0,1.0):" << std::endl;

		for (int i = 0; i < 10; ++i)
		{
			std::cout << i << "-" << (i + 1) << ": ";
			std::cout << std::string(pc[i] * nstars / nrolls, '*') << std::endl;
		}

		this->set(PARETO, 0.1, 0.5, 0, 0);

		int pp[10] =
		{ };

		for (int i = 0; i < nrolls; ++i)
		{
			double number = this->getRandom();
			if ((number >= 0.0) && (number < 10.0))
				++pp[int(number)];
		}

		std::cout << "pareto_distribution (0.1, 0.5):" << std::endl;

		for (int i = 0; i < 10; ++i)
		{
			std::cout << i << "-" << (i + 1) << ": ";
			std::cout << std::string(pp[i] * nstars / nrolls, '*') << std::endl;
		}

		return (true);
	}
};

//int compareBic(const void* a, const void* b);
//int compareAic(const void* a, const void* b);

#endif /* STOCHASTICMODELFIT_H_ */
