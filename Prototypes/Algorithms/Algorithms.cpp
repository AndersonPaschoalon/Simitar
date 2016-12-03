//============================================================================
// Name        : CppAlgorithms.cpp
// Author      : Anderson Paschoalon
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Algorithms.h"

int main()
{
	DataProcessor dp;
	dp.printTestResult("QuickSort", dp.testQuickSort());
	dp.printTestResult("List Mode", dp.testMode());
	dp.printTestResult("ListToVector", dp.test_list_tocvector());
	dp.printTestResult("Empirical CDF", dp.test_empiricalCdf());
	dp.printTestResult("Cost Function", dp.test_computeCost());

	dp.printTestResult("Weibull PDF", dp.test_pdf_weibull());
	dp.printTestResult("Weibull CDF", dp.test_cdf_weibull());
	dp.printTestResult("Gradient Descendent", dp.test_gradientDescendent());

	dp.printTestResult("Information Criterion", dp.test_informationCriterion());
	dp.printTestResult("Exponential PDF", dp.test_pdf_exponential());
	dp.printTestResult("Exponential CDF", dp.test_cdf_exponential());
	dp.printTestResult("PDF Pareto", dp.test_pdf_pareto());
	dp.printTestResult("Pareto CDF", dp.test_cdf_pareto());
	dp.printTestResult("PDF Cauchy", dp.test_pdf_cauchy());
	dp.printTestResult("CDF Cauchy", dp.test_cdf_cauchy());
	dp.printTestResult("All fitting", dp.test_fitModels());
	dp.printTestResult("Model selection", dp.test_modelSelection());

	return 0;
}

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

/*******************************************************************************
 * ACTUAL FUNCTIONS
 ******************************************************************************/

StochasticModelFit* DataProcessor::fitModels(list<double>& empiricalData,
		const string& criterion)
{
	//constants
	const int numberOfModels = 8;
	const int m = empiricalData.size(); //empirical data-size
	//vars
	int counter = 0;
	StochasticModelFit* modelVet = NULL;
	vec paramVec = zeros<vec>(2);
	vec infoCriterion = zeros<vec>(2);

	modelVet = new StochasticModelFit[numberOfModels];

	//Inter-arrival vec
	vec interArrival = zeros<vec>(m);
	counter = 0;
	for (list<double>::iterator it = empiricalData.begin();
			it != empiricalData.end(); it++)
	{
		interArrival(counter) = *it + min_time;
		counter++;
	}
	//Empirical CDF of interArrival
	vec* interArrivalCdf = empiricalCdf(empiricalData);

	//Weibull
	weibullFitting(interArrival, *interArrivalCdf, paramVec, infoCriterion);
	modelVet[0].aic = infoCriterion(0);
	modelVet[0].bic = infoCriterion(1);
	modelVet[0].modelName = "weibull";
	modelVet[0].param1 = paramVec(0);
	modelVet[0].param2 = paramVec(1);
	modelVet[0].size = numberOfModels;

	//normal
	normalFitting(interArrival, paramVec, infoCriterion);
	modelVet[1].aic = infoCriterion(0);
	modelVet[1].bic = infoCriterion(1);
	modelVet[1].modelName = "normal";
	modelVet[1].param1 = paramVec(0);
	modelVet[1].param2 = paramVec(1);
	modelVet[1].size = numberOfModels;

	//exponential mean
	exponentialMeFitting(interArrival, paramVec, infoCriterion);
	modelVet[2].aic = infoCriterion(0);
	modelVet[2].bic = infoCriterion(1);
	modelVet[2].modelName = "exponential-mean";
	modelVet[2].param1 = paramVec(0);
	modelVet[2].param2 = paramVec(1);
	modelVet[2].size = numberOfModels;

	//exponential Linear Regression (LR)
	exponentialLrFitting(interArrival, *interArrivalCdf, paramVec,
			infoCriterion);
	modelVet[3].aic = infoCriterion(0);
	modelVet[3].bic = infoCriterion(1);
	modelVet[3].modelName = "exponential-linear-regression";
	modelVet[3].param1 = paramVec(0);
	modelVet[3].param2 = paramVec(1);
	modelVet[3].size = numberOfModels;

	//pareto linear regression
	paretoLrFitting(interArrival, *interArrivalCdf, paramVec, infoCriterion);
	modelVet[4].aic = infoCriterion(0);
	modelVet[4].bic = infoCriterion(1);
	modelVet[4].modelName = "pareto-linear-regression";
	modelVet[4].param1 = paramVec(0);
	modelVet[4].param2 = paramVec(1);
	modelVet[4].size = numberOfModels;

	//pareto maximum likehood
	paretoMlhFitting(interArrival, *interArrivalCdf, paramVec, infoCriterion);
	modelVet[5].aic = infoCriterion(0);
	modelVet[5].bic = infoCriterion(1);
	modelVet[5].modelName = "pareto-maximum-likehood";
	modelVet[5].param1 = paramVec(0);
	modelVet[5].param2 = paramVec(1);
	modelVet[5].size = numberOfModels;

	//Cauchy
	cauchyFitting(interArrival, *interArrivalCdf, paramVec, infoCriterion);
	modelVet[6].aic = infoCriterion(0);
	modelVet[6].bic = infoCriterion(1);
	modelVet[6].modelName = "cauchy";
	modelVet[6].param1 = paramVec(0);
	modelVet[6].param2 = paramVec(1);
	modelVet[6].size = numberOfModels;

	//Constant
	constantFitting(interArrival, paramVec, infoCriterion);
	modelVet[7].aic = infoCriterion(0);
	modelVet[7].bic = infoCriterion(1);
	modelVet[7].modelName = "constant";
	modelVet[7].param1 = paramVec(0);
	modelVet[7].param2 = paramVec(1);
	modelVet[7].size = numberOfModels;

	if (criterion == "bic")
	{
		qsort(modelVet, numberOfModels, sizeof(StochasticModelFit), compareBic);
	}
	else if (criterion == "aic")
	{
		qsort(modelVet, numberOfModels, sizeof(StochasticModelFit), compareAic);
	}
	else
	{
		cout
				<< "Error @ DataProcessor::fitModels -> Invalid criterion argument: "
				<< criterion << endl;
		cout << "AIC set as default" << endl;
		qsort(modelVet, numberOfModels, sizeof(StochasticModelFit), compareAic);

	}

	delete interArrivalCdf;

	return (modelVet);
}

inline void DataProcessor::weibullFitting(const vec& interArrival,
		const vec& interArrivalCdf, vec& paramVec, vec& infoCriterion)
{
	//init
	int iterations = 1500;
	double learning_rate = 0.01;
	vec theta = zeros(2);
	vec J_history = zeros(iterations);

	//linearization
	vec y = log(-log(1.0 + diferential - interArrivalCdf));
	vec x = log(interArrival);
	mat* X = featureMatrix(x);

	//gradient descendent
	gradientDescendent(*X, y, learning_rate, iterations, theta, J_history);

	//parameter evaluation
	double weibull_alpha = theta(1);
	double weibull_betha = exp(-theta(0) / theta(1));
	paramVec(0) = weibull_alpha;
	paramVec(1) = weibull_betha;

	delete X;

	//information criterion
	double aic = informationCriterion(interArrival, "weibull", paramVec, "aic");
	double bic = informationCriterion(interArrival, "weibull", paramVec, "bic");
	infoCriterion(0) = aic;
	infoCriterion(1) = bic;

}

inline void DataProcessor::normalFitting(const vec& interArrival, vec& paramVec,
		vec& infoCriterion)
{
	double sigma = stddev(interArrival);
	double mu = mean(interArrival);
	paramVec(0) = mu;
	paramVec(1) = sigma;

	//information criterion
	double aic = informationCriterion(interArrival, "normal", paramVec, "aic");
	double bic = informationCriterion(interArrival, "normal", paramVec, "bic");
	infoCriterion(0) = aic;
	infoCriterion(1) = bic;
}

inline void DataProcessor::exponentialLrFitting(const vec& interArrival,
		const vec& interArrivalCdf, vec& paramVec, vec& infoCriterion)
{
	//init
	int iterations = 1500;
	double learning_rate = 0.01;
	vec theta = zeros<vec>(2);
	vec J_history = zeros<vec>(iterations);

	//linearization
	vec y = log(1.00 + diferential - interArrivalCdf);
	//vec y = log(1.00 - interArrivalCdf);
	vec x = interArrival;
	mat* X = featureMatrix(x);

	//gradient descendent
	gradientDescendent(*X, y, learning_rate, iterations, theta, J_history);

	//parameter evaluation
	double exp_lambda = -theta(1);
	paramVec(0) = exp_lambda;
	paramVec(1) = 0;

	delete X;

	//information criterion
	double aic = informationCriterion(interArrival, "exponential", paramVec,
			"aic");
	double bic = informationCriterion(interArrival, "exponential", paramVec,
			"bic");
	infoCriterion(0) = aic;
	infoCriterion(1) = bic;
}

inline void DataProcessor::exponentialMeFitting(const vec& interArrival,
		vec& paramVec, vec& infoCriterion)
{
	paramVec(0) = 1.0 / mean(interArrival);
	paramVec(1) = 0;

	//information criterion
	double aic = informationCriterion(interArrival, "exponential", paramVec,
			"aic");
	double bic = informationCriterion(interArrival, "exponential", paramVec,
			"bic");
	infoCriterion(0) = aic;
	infoCriterion(1) = bic;
}

inline void DataProcessor::paretoLrFitting(const vec& interArrival,
		const vec& interArrivalCdf, vec& paramVec, vec& infoCriterion)
{
	//init
	int iterations = 1500;
	double learning_rate = 0.01;
	vec theta = zeros(2);
	vec J_history = zeros(iterations);

	//linearization
	vec y = log(1.00 + diferential - interArrivalCdf);
	//vec y = log(1.00 - interArrivalCdf);
	vec x = log(interArrival);
	mat* X = featureMatrix(x);

	//gradient descendent
	gradientDescendent(*X, y, learning_rate, iterations, theta, J_history);

	//parameter evaluation
	double pareto_alpha = -theta(1);
	double pareto_xm = interArrival.min();
	paramVec(0) = pareto_alpha;
	paramVec(1) = pareto_xm;

	delete X;

	//information criterion
	double aic = informationCriterion(interArrival, "pareto", paramVec, "aic");
	double bic = informationCriterion(interArrival, "pareto", paramVec, "bic");
	infoCriterion(0) = aic;
	infoCriterion(1) = bic;
}

inline void DataProcessor::paretoMlhFitting(const vec& interArrival,
		const vec& interArrivalCdf, vec& paramVec, vec& infoCriterion)
{
	double pareto_xm = interArrival.min();
	int m = interArrival.size();
	//vec logDiff = log(interArrival) - log(ones<vec>(m) * pareto_xm);
	vec logDiff = log(interArrival) - log(pareto_xm);
	double pareto_alpha = double(m) / (sum(logDiff));
	paramVec(0) = pareto_alpha;
	paramVec(1) = pareto_xm;

	//information criterion
	double aic = informationCriterion(interArrival, "pareto", paramVec, "aic");
	double bic = informationCriterion(interArrival, "pareto", paramVec, "bic");
	infoCriterion(0) = aic;
	infoCriterion(1) = bic;
}

inline void DataProcessor::cauchyFitting(const vec& interArrival,
		const vec& interArrivalCdf, vec& paramVec, vec& infoCriterion)
{
	//initialization
	int iterations = 1500;
	double learning_rate = 0.01;
	int m = interArrival.size();
	double minInterArrival = interArrival.min();
	double y_max = 1.0 / minInterArrival;
	vec y = tan(datum::pi * (interArrivalCdf - 0.5));
	for (int i = 0; i < m; i++)
	{
		//avoid too high numbers when tan() tends to infinity
		if (y(i) > y_max)
			y(i) = y_max;
	}

	//linearization
	vec J_history = zeros<vec>(iterations);
	vec theta = zeros(2);
	mat* X = featureMatrix(interArrival);

	//gradient descendent
	gradientDescendent(*X, y, learning_rate, iterations, theta, J_history);

	//parameter evaluation
	double cauchy_gamma = double(1.0) / theta(1);
	double cauchy_x0 = -theta(0) / theta(1);
	paramVec(0) = cauchy_gamma;
	paramVec(1) = cauchy_x0;

	delete X;

	//information criterion
	double aic = informationCriterion(interArrival, "cauchy", paramVec, "aic");
	double bic = informationCriterion(interArrival, "cauchy", paramVec, "bic");
	infoCriterion(0) = aic;
	infoCriterion(1) = bic;

}

void DataProcessor::constantFitting(const vec& interArrival, vec& paramVec,
		vec& informationCriterion)
{
	paramVec(0) = mean(interArrival);
	paramVec(1) = 0;
	informationCriterion(0) = datum::inf;
	informationCriterion(1) = datum::inf;
}

template<typename T> bool DataProcessor::isEqual(const T* vet1, const T* vet2,
		const int size)
{
	for (int i = 0; i < size; i++)
	{
		if (vet1[i] != vet2[i])
		{
			return (false);
		}
	}

	return (true);
}

template<typename T> void DataProcessor::vectorC_to_list(list<T>* theList,
		T* vet, int size)
{
	for (int i = 0; i < size; i++)
	{
		theList->push_back(vet[i]);
	}
}

template<typename T>
void DataProcessor::quickSort(T* vet, int left, int right)
{
	int p = left;
	int i = 0;
	T ch = 0;
	int j = 0;

	for (i = left + 1; i <= right; i++)
	{
		j = i;
		if (vet[j] < vet[p])
		{
			ch = vet[j];
			while (j > p)
			{
				vet[j] = vet[j - 1];
				j--;
			}
			vet[j] = ch;
			p++;
		}
	}
	if (p - 1 >= left)
		quickSort(vet, left, p - 1);
	if (p + 1 <= right)
		quickSort(vet, p + 1, right);
}

template<typename T>
T DataProcessor::mode(list<T>* theList)
{
	T* vet;
	int listSize = theList->size();
	int i = 0;
	T candidate = 0;
	T prev = 0;
	int counter = 0;
	int largerCounter = 0;
	T mode = 0;
	vet = new T[listSize];

	if (listSize == 0)
	{
		return (0);
	}

	i = 0;

	for (typename list<T>::iterator it = theList->begin(); it != theList->end();
			it++)
	{
		vet[i] = *it;
		i++;
	}

	quickSort(vet, 0, listSize - 1);

	prev = vet[0];
	largerCounter = 0;
	for (i = 0; i < listSize; i++)
	{
		candidate = vet[i];
		if (candidate == prev)
		{
			counter++;
			if (counter > largerCounter)
			{
				largerCounter = counter;
				mode = vet[i];
			}
		}
		else
			counter = 1;

		prev = vet[i];
	}

	delete[] vet;

	return (mode);
}

template<typename T>
inline T* DataProcessor::list_to_cvector(list<T>* theList)
{
	int listSize = theList->size();
	T* vet;
	int i = 0;

	vet = new T[listSize];
	if (listSize == 0)
	{
		return (0);
	}

	i = 0;
	for (typename list<T>::iterator it = theList->begin(); it != theList->end();
			it++)
	{
		vet[i] = *it;
		i++;
	}

	return (vet);
}
template<typename T>
inline void DataProcessor::delete_cvector(T* c_vet)
{
	delete[] c_vet;
}

inline vec* DataProcessor::empiricalCdf(list<double>& empiricalData)
{
	double* cvet_empiricalData = list_to_cvector(&empiricalData);
	int data_size = empiricalData.size();
	quickSort(cvet_empiricalData, 0, data_size - 1);
	double x = cvet_empiricalData[0]; // anchor - fist element;
	int i1 = 0; // fist index
	int i2 = 0;
	double prob = 0;
	vec* interArrivalCdf = new vec(zeros<vec>(data_size));

	for (int i = 0; i < data_size; i++)
	{
		if (cvet_empiricalData[i] > x)
		{
			i2 = i - 1;
			prob = double(i) / data_size;
			for (int j = i1; j <= i2; j++)
			{
				(*interArrivalCdf)(j) = prob;
			}
			i1 = i;
			x = cvet_empiricalData[i];
		}
	}
	//last position == 1
	(*interArrivalCdf)(data_size - 1) = 1;

	delete_cvector(cvet_empiricalData);
	return (interArrivalCdf);
}

inline mat* DataProcessor::featureMatrix(list<double>& empiricalData)
{
	int data_size = empiricalData.size();
	mat* featureMatrix = new mat(ones<mat>(data_size, 2));

	int i = 0;
	for (list<double>::iterator it = empiricalData.begin();
			it != empiricalData.end(); it++)
	{
		(*featureMatrix)(i, 1) = *it;
		i++;
	}

	return (featureMatrix);

}

inline mat* DataProcessor::featureMatrix(const vec& empiricalData)
{
	int data_size = empiricalData.size();
	mat* featureMatrix = new mat(ones<mat>(data_size, 2));
	for (int i = 0; i < data_size; i++)
	{
		(*featureMatrix)(i, 1) = empiricalData(i);
	}

	return (featureMatrix);
}

inline double DataProcessor::computeCost(const mat& X, const vec& y,
		const vec& theta)
{
	double J = .0;
	double jtemp = .0;
	int m = y.size();

	for (int i = 0; i < m; i++)
	{
		jtemp = jtemp + pow(double(theta(0) + theta(1) * X(i, 1) - y(i)), 2);

	}
	J = (1.0 / double(2 * m)) * jtemp;

	return (J);
}

inline void DataProcessor::gradientDescendent(const mat& X, const vec& y,
		const double learning_rate, const int num_iters, vec& theta,
		vec& J_history)
{

	int m = y.n_rows; //number of training examples
	double temp1 = .0;
	double temp2 = .0;
	double delta1 = .0;
	double delta2 = .0;
	vec x = X.col(1);

	for (int i = 0; i < num_iters; i++)
	{
		temp1 = .0;
		temp2 = .0;
		delta1 = .0;
		delta2 = .0;

		//slope
		delta1 = sum(theta(0) + theta(1) * x - y) / double(m);
		delta2 = sum((theta(0) + theta(1) * x - y) % x) / double(m);

		//linear regression
		temp1 = theta(0) - learning_rate * delta1;
		temp2 = theta(1) - learning_rate * delta2;

		theta(0) = temp1;
		theta(1) = temp2;

		//Save the cost J in every iteration
		J_history(i) = computeCost(X, y, theta);

	}

}

inline double DataProcessor::informationCriterion(const vec& data,
		const string& functionName, const vec& paramVet,
		const string& criterion)
{
	double criterionVal = .0;
	double nEstimatedParameters = double(paramVet.size());
	double likehoodLogVal = logLikehood(data, functionName, paramVet);
	double logDataLen = log(double(data.size()));

	if (criterion == "aic")
	{
		criterionVal = 2 * nEstimatedParameters - 2 * likehoodLogVal;
	}
	else if (criterion == "bic")
	{
		criterionVal = nEstimatedParameters * logDataLen - 2 * likehoodLogVal;
	}
	else
	{
		cout << "\nInvalid functionName or no functionName selected: "
				<< functionName << endl;
		printf("Selecting default criterion: AIC\n");
		criterionVal = 2 * nEstimatedParameters - 2 * likehoodLogVal;
	}

	return (criterionVal);

}

inline double DataProcessor::logLikehood(const vec& data,
		const string& functionName, const vec& paramVet)
{
	double param1 = paramVet(0);
	double param2 = paramVet(1);
	double m = data.size();
	double L = .0;
	int i = 0;
	vec data_prob = zeros<vec>(size(data));

	if (functionName == "weibull")
	{
		for (i = 0; i < m; i++)
			data_prob(i) = pdf_weibull(data(i), param1, param2);
	}
	else if (functionName == "normal")
	{
		for (i = 0; i < m; i++)
			data_prob(i) = pdf_normal(data(i), param1, param2);
	}
	else if (functionName == "uniform")
	{
		data_prob = ones<vec>(size(data)) * pdf_uniform(param1, param2);
	}
	else if (functionName == "exponential")
	{
		for (i = 0; i < m; i++)
			data_prob(i) = pdf_exponential(data(i), param1);
	}
	else if (functionName == "pareto")
	{
		for (i = 0; i < m; i++)
			data_prob(i) = pdf_pareto(data(i), param1, param2);
	}
	else if (functionName == "cauchy")
	{
		for (i = 0; i < m; i++)
			data_prob(i) = pdf_cauchy(data(i), param1, param2);
	}
	else
	{
		cout << "Warning, no valid stochastic function selected: "
				<< functionName << endl;
		printf("Likehood logarithm seted to -Inf (worst as possible)\n");
		return (datum::inf);
	}

	L = sum(log(data_prob));
	return (L);

}

inline double DataProcessor::pdf_weibull(double x, double alpha, double betha)
{
	if (x >= 0)
		return ((alpha / pow(betha, alpha)) * pow(x, alpha - 1.0)
				* exp(-(pow(x / betha, alpha))));
	else
		return (.0);
}

inline double DataProcessor::cdf_weibull(double x, double alpha, double betha)
{
	if (x >= 0)
		return (1.0 - exp(-pow(x / betha, alpha)));
	else
		return (.0);
}

inline double DataProcessor::pdf_exponential(double x, double lambda)
{
	if (x >= 0)
		return (lambda * exp(-lambda * x));
	else
		return (.0);

}

inline double DataProcessor::cdf_exponential(double x, double lambda)
{
	if (x >= 0)
		return (1.0 - exp(-lambda * x));
	else
		return (.0);
}

inline double DataProcessor::pdf_pareto(double x, double alpha, double xm)
{
	if (x >= xm)
		return (alpha * pow(xm, alpha) / (pow(x, alpha + 1.0)));
	else
		return (.0);
}

inline double DataProcessor::cdf_pareto(double x, double alpha, double xm)
{
	if (x >= xm)
		return (1.0 - pow(xm / x, alpha));
	else
		return (.0);
}

inline double DataProcessor::pdf_cauchy(double x, double gamma, double x0)
{
	return (1 / (datum::pi * gamma)
			* (pow(gamma, 2) / (pow(x - x0, 2) + pow(gamma, 2))));
}

inline double DataProcessor::cdf_cauchy(double x, double gamma, double x0)
{
	return ((1 / datum::pi) * atan((x - x0) / (gamma)) + 0.5);
}

inline double DataProcessor::pdf_normal(double x, double mu, double sigma)
{
	return (1 / (sqrt(2 * datum::pi) * sigma)
			* exp(-0.5 * pow((x - mu) / sigma, 2)));
}

inline double DataProcessor::cdf_normal(double x, double mu, double sigma)
{
	return (0.5 * (1 + erf((x - mu) / (sigma * sqrt(2)))));
}

inline double DataProcessor::pdf_uniform(double x_min, double x_max)
{
	return (1.0 / (x_max - x_min));
}

inline double DataProcessor::cdf_uniform(double x, double x_min, double x_max)
{
	if (x < x_min)
		return (0);
	else if (x > x_max)
		return (1);
	else
		return ((x - x_min) / (x_max - x_min));
}

#ifdef TEST_FUNCTIONS

void DataProcessor::printTestResult(string testName, bool result)
{
	string outRes;
	if (result == true)
		outRes = "ok";
	else
		outRes = "failed";

	cout << testName << ":\t\t" << outRes << endl;
}

inline bool DataProcessor::compareDouble(double val1, double val2)
{
	double error = 0;

	error = fabs(double(val1) - double(val2));
	if (error > double(1e-5))
		return (false);
	else
		return (true);

}

inline bool DataProcessor::compareDouble(double val1, double val2, double acErr)
{
	double error = 0;

	error = fabs(double(val1) - double(val2));
	if (error > double(acErr))
		return (false);
	else
		return (true);

}

bool DataProcessor::compareMat(mat& mat1, mat& mat2)
{
	int mat1_nc = mat1.n_cols;
	int mat1_nr = mat1.n_rows;
	int mat2_nc = mat2.n_cols;
	int mat2_nr = mat2.n_rows;

	if ((mat1_nc != mat2_nc) || (mat1_nr != mat2_nr))
	{
		cout << "mat1.n_cols and mat2.n_cols dont match. " << mat1_nc << ":"
				<< mat2_nc << " " << mat1_nr << ":" << mat2_nr << endl;
		return (false);
	}
	for (int i = 0; i < mat1_nr; i++)
	{
		for (int j = 0; j < mat1_nc; j++)
		{
			if (compareDouble(mat1(i, j), mat2(i, j), 1e-5))
			{
				//cout << " mat1(" << i << ", " << j << " ) = " << mat1(i,j);
				//cout << " mat2(" << i << ", " << j << " ) = " << mat2(i,j);
				return (false);
			}
		}
	}

	return (true);
}

inline void DataProcessor::save_data_on_file(const string& fileName,
		const mat& vet1, const mat& vet2)
{
	string file_out = fileName + ".txt";
	int m = vet1.size();

	ofstream writeOnFile(file_out, ios::out);
	if (!writeOnFile)
	{
		cerr << "file could not be oppeded" << endl;
		exit(1);
	}

	for (int i = 0; i < m; i++)
	{
		writeOnFile << vet1(i) << " " << vet2(i) << endl;
	}

}

bool DataProcessor::testMode()
{

	int randint1[] =
	{ 1, 8, 1, 13, 9, 2, 1, 15, 4, 3, 10, 4, 13, 2, 14, 7, 7 };
	int randint1_mode = 1;
	list<int> l_randint1;
	vectorC_to_list(&l_randint1, randint1, 17);

	int randint2[] =
	{ 5, 3, 6, 8, 14, 9, 11, 9, 11, 15, 8, 7, 12, 13, 14 };
	int randint2_mode = 8;
	list<int> l_randint2;
	vectorC_to_list(&l_randint2, randint2, 15);

	int randint3[] =
	{ 9, 10, 6, 3, 13, 13, 14, 7, 7, 1, 5, 1, 8, 5, 9, 2, 3, 4, 5, 6, 6, 6 };
	int randint3_mode = 6;
	list<int> l_randint3;
	vectorC_to_list(&l_randint3, randint3, 22);

	int randint4[] =
	{ 2, 1 };
	int randint4_mode = 1;
	list<int> l_randint4;
	vectorC_to_list(&l_randint4, randint4, 2);

	int randint5[] =
	{ 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 };
	int randint5_mode = 1;
	list<int> l_randint5;
	vectorC_to_list(&l_randint5, randint5, 10);

	if (mode(&l_randint1) != randint1_mode)
		return (false);
	if (mode(&l_randint2) != randint2_mode)
		return (false);
	if (mode(&l_randint3) != randint3_mode)
		return (false);
	if (mode(&l_randint4) != randint4_mode)
		return (false);
	if (mode(&l_randint5) != randint5_mode)
		return (false);

	return (true);
}

bool DataProcessor::testQuickSort()
{
	int randIntA[] =
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int randIntA_size = 18;
	int randIntA_sorted[] =
	{ 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9 };
	int randIntB[] =
	{ 9, 2, 3, 3, 12, 15, 8, 14, 2, 7, 4, 6, 10, 2, 12 };
	int randIntB_size = 15;
	int randIntB_sorted[] =
	{ 2, 2, 2, 3, 3, 4, 6, 7, 8, 9, 10, 12, 12, 14, 15 };
	double randDoubleA[] =
	{ 0.20872, 12.25501, 5.88210, 2.77962, 8.74916, 2.97454, 4.39641, 12.19733,
			4.66014, 4.52477, 5.19375, 12.11314, 13.35458, 11.56941, 6.59435 };
	int randDoubleA_size = 15;
	double randDoubleA_sorted[] =
	{ 0.20872, 2.77962, 2.97454, 4.39641, 4.52477, 4.66014, 5.19375, 5.88210,
			6.59435, 8.74916, 11.56941, 12.11314, 12.19733, 12.25501, 13.35458 };

	quickSort(randIntA, 0, randIntA_size - 1);

	if (isEqual(randIntA, randIntA_sorted, randIntA_size) == false)
	{
		return (false);
	}

	quickSort(randIntB, 0, randIntB_size - 1);
	if (isEqual(randIntB, randIntB_sorted, randIntB_size) == false)
	{
		return (false);
	}

	quickSort(randDoubleA, 0, randDoubleA_size - 1);
	if (isEqual(randDoubleA, randDoubleA_sorted, randDoubleA_size) == false)
	{
		return (false);
	}

	return (true);

}

inline bool DataProcessor::test_list_tocvector()
{
	list<int> randInt_list1 =
	{ 9, 2, 3, 3, 12, 15, 8, 14, 2, 7, 4, 6, 10, 2, 12 };
	list<double> randInt_list2 =
	{ 2.2, 2.111, 3.16, 6.66, 13, 2.61 };
	list<int> randInt_list3 =
	{ 1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1 };

	int* cvet1 = NULL;
	double* cvet2 = NULL;
	int* cvet3 = NULL;

	cvet1 = list_to_cvector(&randInt_list1);
	cvet2 = list_to_cvector(&randInt_list2);
	cvet3 = list_to_cvector(&randInt_list3);

	int i = 0;
	for (list<int>::iterator it = randInt_list1.begin();
			it != randInt_list1.end(); it++)
	{
		if (cvet1[i] != *it)
		{
			return (false);
		}
		//cout << *it << " ";
		i++;
	}
	i = 0;
	for (list<double>::iterator it = randInt_list2.begin();
			it != randInt_list2.end(); it++)
	{
		if (cvet2[i] != *it)
		{
			return (false);
		}
		//cout << *it << " ";
		i++;
	}
	i = 0;
	for (list<int>::iterator it = randInt_list3.begin();
			it != randInt_list3.end(); it++)
	{
		if (cvet3[i] != *it)
		{
			return (false);
		}
		//cout << *it << " ";
		i++;
	}

	delete_cvector(cvet1);
	delete_cvector(cvet2);
	delete_cvector(cvet3);

	return (true);
}

inline bool DataProcessor::test_empiricalCdf()
{
	list<double> interArrival_sample =
	{ 5.0000e-07, 1.5000e-06, 1.5000e-06, 2.5000e-06, 2.5000e-06, 3.5000e-06,
			4.5000e-06, 7.5000e-06, 1.2500e-05, 1.9500e-05, 3.1500e-05,
			4.3500e-05, 6.0500e-05, 7.6500e-05, 1.1050e-04, 1.4050e-04,
			1.8150e-04, 2.1150e-04, 2.3350e-04, 2.4350e-04, 2.5650e-04,
			3.0350e-04, 4.1250e-04, 1.3655e-03, 1.1593e-02, 3.2483e-02,
			8.1235e-02, 2.0939e-01, 5.0755e-01, 1.7351e+00 };
	vec emCdf_octave =
	{ 0.033333, 0.100000, 0.100000, 0.166667, 0.166667, 0.200000, 0.233333,
			0.266667, 0.300000, 0.333333, 0.366667, 0.400000, 0.433333,
			0.466667, 0.500000, 0.533333, 0.566667, 0.600000, 0.633333,
			0.666667, 0.700000, 0.733333, 0.766667, 0.800000, 0.833333,
			0.866667, 0.900000, 0.933333, 0.966667, 1.000000 };
	//emCdf_octave = emCdf_octave.t();

	vec* emCdf_cpp = empiricalCdf(interArrival_sample);

	int list_size = interArrival_sample.size();
	for (int i = 0; i < list_size; i++)
	{
		if (!compareDouble(emCdf_octave(i), (*emCdf_cpp)(i), 1e-6))
		{
			cout << "cdf error @ " << "i:" << i << " res:" << (*emCdf_cpp)(i, 0)
					<< " expected:" << emCdf_octave(i, 0) << endl;
			return (false);
		}
	}

	delete emCdf_cpp;
	return (true);
}

inline bool DataProcessor::test_computeCost()
{
	list<double> interArrival_sample =
	{ 5.0000e-07, 1.5000e-06, 1.5000e-06, 2.5000e-06, 2.5000e-06, 3.5000e-06,
			4.5000e-06, 7.5000e-06, 1.2500e-05, 1.9500e-05, 3.1500e-05,
			4.3500e-05, 6.0500e-05, 7.6500e-05, 1.1050e-04, 1.4050e-04,
			1.8150e-04, 2.1150e-04, 2.3350e-04, 2.4350e-04, 2.5650e-04,
			3.0350e-04, 4.1250e-04, 1.3655e-03, 1.1593e-02, 3.2483e-02,
			8.1235e-02, 2.0939e-01, 5.0755e-01, 1.7351e+00 };
	mat* X = featureMatrix(interArrival_sample);
	vec emCdf_octave =
	{ 0.033333, 0.100000, 0.100000, 0.166667, 0.166667, 0.200000, 0.233333,
			0.266667, 0.300000, 0.333333, 0.366667, 0.400000, 0.433333,
			0.466667, 0.500000, 0.533333, 0.566667, 0.600000, 0.633333,
			0.666667, 0.700000, 0.733333, 0.766667, 0.800000, 0.833333,
			0.866667, 0.900000, 0.933333, 0.966667, 1.000000 };
	//emCdf_octave = emCdf_octave.t();
	double J_expected1 = 0.17535;
	double J_expected2 = 1.5341;
	double J_expected3 = 9.0244;

	vec theta = zeros(2);

	double J = computeCost(*X, emCdf_octave, theta);
	if (!compareDouble(J, J_expected1, 0.001))
	{
		//cout << "J1 = " << J << "\nJ_expected1 = "<< J_expected1 << endl;
		return (false);
	}
	theta(0) = 2;
	theta(1) = 2;
	J = computeCost(*X, emCdf_octave, theta);
	if (!compareDouble(J, J_expected2, 0.001))
	{
		//cout << "J2 = " << J << "\nJ_expected2 = "<< J_expected2 << endl;
		return (false);
	}
	theta(0) = 1.5;
	theta(1) = 12;
	J = computeCost(*X, emCdf_octave, theta);
	if (!compareDouble(J, J_expected3, 0.001))
	{
		//cout << "J3 = " << J << "\nJ_expected3 = "<< J_expected3 << endl;
		return (false);
	}

	delete X;
	return (true);
}

inline bool DataProcessor::test_informationCriterion()
{
	//mat M;
	//M.load("CppAlgorithms/data_sample.txt");
	//vec interArrival = sort(M.col(3)) + min_time;
	vec interArrival = sort(interArrivalSample) + min_time;

	int m = interArrival.size();
	list<double> list_interArrival;
	vec* interArrivalCdf;
	for (int i = 0; i < m; i++)
	{
		list_interArrival.push_back(interArrival(i));
	}
	interArrivalCdf = empiricalCdf(list_interArrival);

	//gradient descendent
	int iterations = 1500;
	double learning_rate = 0.01;
	vec theta = zeros(2);
	vec J_history = zeros(iterations);

	vec y = log(-log(1.0 + diferential - *interArrivalCdf));
	vec x = log(interArrival);
	mat* X = featureMatrix(x);

	gradientDescendent(*X, y, learning_rate, iterations, theta, J_history);

	double weibull_alpha = theta(1);
	double weibull_betha = exp(-theta(0) / theta(1));
	vec paramVec =
	{ weibull_alpha, weibull_betha };
	double weibull_bic = informationCriterion(interArrival, "weibull", paramVec,
			"bic");
	double weibull_aic = informationCriterion(interArrival, "weibull", paramVec,
			"aic");

	if (!compareDouble(weibull_bic, -33712.7042, 0.001))
		return (false);
	else if (!compareDouble(weibull_aic, -33724.6567, 0.001))
		return (false);

	return (true);
}

inline bool DataProcessor::test_pdf_weibull()
{
	double alpha = 1.5000;
	double betha = 0.3;
	vec data =
	{ 0.010000, 2.300000, 0.500000 };
	vec dataprob_eval1 =
	{ 9.0733e-01, 8.3571e-09, 7.5066e-01 };
	vec dataprob_test = zeros(3);

	dataprob_test(0) = pdf_weibull(data(0), alpha, betha);
	dataprob_test(1) = pdf_weibull(data(1), alpha, betha);
	dataprob_test(2) = pdf_weibull(data(2), alpha, betha);

	if (compareDouble(dataprob_test(0), dataprob_eval1(0))
			&& compareDouble(dataprob_test(1), dataprob_eval1(1))
			&& compareDouble(dataprob_test(2), dataprob_eval1(2)))
	{
		return (true);
	}

	return (false);
}

inline bool DataProcessor::test_cdf_weibull()
{
	double alpha = 0.5;
	double betha = 1.5;
	vec data =
	{ 0.010000, 2.300000, 0.500000 };
	vec dataprob_eval1 =
	{ 0.078405, 0.710117, 0.438616 };
	vec dataprob_test = zeros(3);

	dataprob_test(0) = cdf_weibull(data(0), alpha, betha);
	dataprob_test(1) = cdf_weibull(data(1), alpha, betha);
	dataprob_test(2) = cdf_weibull(data(2), alpha, betha);
	//cout << dataprob_test(0) << " : " << dataprob_test(1) << " : " << dataprob_test(2) << endl;

	if (compareDouble(dataprob_test(0), dataprob_eval1(0))
			&& compareDouble(dataprob_test(1), dataprob_eval1(1))
			&& compareDouble(dataprob_test(2), dataprob_eval1(2)))
	{
		return (true);
	}

	return (false);
}

inline bool DataProcessor::test_gradientDescendent()
{
	//mat M;
	//M.load("CppAlgorithms/data_sample.txt");
	//vec interArrival = sort(M.col(3)) + min_time;
	vec interArrival = sort(interArrivalSample) + min_time;

	int m = interArrival.size();
	list<double> list_interArrival;
	vec* interArrivalCdf;
	for (int i = 0; i < m; i++)
	{
		list_interArrival.push_back(interArrival(i));
	}
	interArrivalCdf = empiricalCdf(list_interArrival);

	//gradient descendent
	int iterations = 1500;
	double learning_rate = 0.01;
	vec theta = zeros(2);
	vec J_history = zeros(iterations);

	vec y = log(-log(1.0 + diferential - *interArrivalCdf));
	vec x = log(interArrival);
	mat* X = featureMatrix(x);

	gradientDescendent(*X, y, learning_rate, iterations, theta, J_history);

	//expected values
	double Jlast = 0.083359;
	double theta0 = 1.660453;
	double theta1 = 0.248811;

	if (!compareDouble(J_history(iterations - 1), Jlast))

	{
		return (false);
	}
	else if (!compareDouble(theta(0), theta0))
	{
		return (false);
	}
	else if (!compareDouble(theta(1), theta1))
	{
		return (false);
	}

	delete interArrivalCdf;
	delete X;
	return (true);

}

inline bool DataProcessor::test_pdf_exponential()
{
	vec data =
	{ 0.010000, 2.300000, 0.500000 };

	double lambda1 = 0.50000;
	vec val1 =
	{ 0.49751, 0.15832, 0.38940 };
	vec res1 = zeros<vec>(3);

	double lambda2 = 3.0;
	vec val2 =
	{ 2.9113366, 0.0030234, 0.6693905 };
	vec res2 = zeros<vec>(3);

	for (int i = 0; i < 3; i++)
	{
		//exponential
		res1(i) = pdf_exponential(data(i), lambda1);
		res2(i) = pdf_exponential(data(i), lambda2);

		if (!compareDouble(res1(i), val1(i)))
		{
			return (false);
		}
		if (!compareDouble(res2(i), val2(i)))
		{
			return (false);
		}

	}

	return (true);
}

inline bool DataProcessor::test_cdf_exponential()
{
	vec data =
	{ 0.010000, 2.300000, 0.500000 };

	double lambda1 = 0.50000;
	vec val1 =
	{ 0.0049875, 0.6833632, 0.2211992 };
	vec res1 = zeros<vec>(3);

	double lambda2 = 3.0;
	vec val2 =
	{ 0.029554, 0.998992, 0.776870 };
	vec res2 = zeros<vec>(3);

	for (int i = 0; i < 3; i++)
	{
		//exponential
		res1(i) = cdf_exponential(data(i), lambda1);
		res2(i) = cdf_exponential(data(i), lambda2);

		if (!compareDouble(res1(i), val1(i)))
		{
			return (false);
		}
		if (!compareDouble(res2(i), val2(i)))
		{
			return (false);
		}
	}

	return (true);
}

inline bool DataProcessor::test_pdf_pareto()
{

	vec data =
	{ 0.010000, 2.300000, 0.500000 };

	double alpha1 = 0.50000;
	double xm1 = 1.0;
	vec val1 =
	{ 0, 0.14334, 0 };
	vec res1 = zeros<vec>(3);
	double xm2 = 0.00001;
	double alpha2 = 3.0;
	vec val2 =
	{ 3.0000e-07, 1.0720e-16, 4.8000e-14 };
	vec res2 = zeros<vec>(3);

	for (int i = 0; i < 3; i++)
	{
		//exponential
		res1(i) = pdf_pareto(data(i), alpha1, xm1);
		res2(i) = pdf_pareto(data(i), alpha2, xm2);

		//cout << "res1(i) " << res1(i) << ", res2(i) " << res2(i) << endl;
		if (!compareDouble(res1(i), val1(i)))
		{
			return (false);
		}
		if (!compareDouble(res2(i), val2(i)))
		{
			return (false);
		}
	}

	return (true);
}

inline bool DataProcessor::test_cdf_pareto()
{

	vec data =
	{ 0.010000, 2.300000, 0.500000 };

	double alpha1 = 0.50000;
	double xm1 = 0.001;
	vec val1 =
	{ 0.68377, 0.97915, 0.95528 };
	vec res1 = zeros<vec>(3);
	double xm2 = 0.2;
	double alpha2 = 1;
	vec val2 =
	{ 0, 0.91304, 0.60000 };
	vec res2 = zeros<vec>(3);

	for (int i = 0; i < 3; i++)
	{
		//exponential
		res1(i) = cdf_pareto(data(i), alpha1, xm1);
		res2(i) = cdf_pareto(data(i), alpha2, xm2);

		//cout << "res1(i) " << res1(i) << ", res2(i) " << res2(i) << endl;
		if (!compareDouble(res1(i), val1(i)))
		{
			return (false);
		}
		if (!compareDouble(res2(i), val2(i)))
		{
			return (false);
		}
	}
	return (true);
}

inline bool DataProcessor::test_pdf_cauchy()
{

	vec data =
	{ 0.010000, 2.300000, 0.500000 };
	double gamma1 = 0.50000;
	double x01 = 0.001;

	vec val1 =
	{ 0.636414, 0.028752, 0.318947 };
	vec res1 = zeros<vec>(3);
	double x02 = 2;
	double gamma2 = 2;

	vec val2 =
	{ 0.079976, 0.155653, 0.101859 };
	vec res2 = zeros<vec>(3);

	for (int i = 0; i < 3; i++)
	{
		//exponential
		res1(i) = pdf_cauchy(data(i), gamma1, x01);
		res2(i) = pdf_cauchy(data(i), gamma2, x02);

		//cout << "res1(i) " << res1(i) << ", res2(i) " << res2(i) << endl;
		if (!compareDouble(res1(i), val1(i)))
		{
			return (false);
		}
		if (!compareDouble(res2(i), val2(i)))
		{
			return (false);
		}
	}
	return (true);
}

inline bool DataProcessor::test_cdf_cauchy()
{

	vec data =
	{ 0.010000, 2.300000, 0.500000 };
	double gamma1 = 0.50000;
	double x01 = 0.001;

	vec val1 =
	{ 0.50573, 0.93183, 0.74968 };
	vec res1 = zeros<vec>(3);
	double x02 = 2;
	double gamma2 = 2;

	vec val2 =
	{ 0.25080, 0.54739, 0.29517 };
	vec res2 = zeros<vec>(3);

	for (int i = 0; i < 3; i++)
	{
		//exponential
		res1(i) = cdf_cauchy(data(i), gamma1, x01);
		res2(i) = cdf_cauchy(data(i), gamma2, x02);

		//cout << "res1(i) " << res1(i) << ", res2(i) " << res2(i) << endl;
		if (!compareDouble(res1(i), val1(i)))
		{
			return (false);
		}
		if (!compareDouble(res2(i), val2(i)))
		{
			return (false);
		}
	}
	return (true);
}

inline bool DataProcessor::test_fitModels()
{
	//mat M;
	//M.load("CppAlgorithms/data_sample.txt");
	//vec interArrival = sort(M.col(3)) + min_time;
	vec interArrival = sort(interArrivalSample) + min_time;

	int m = interArrival.size();
	list<double> list_interArrival;
	vec* interArrivalCdf;
	for (int i = 0; i < m; i++)
	{
		list_interArrival.push_back(interArrival(i));
	}
	interArrivalCdf = empiricalCdf(list_interArrival);

	//list of expected values
	double weibull_alpha = 0.24881;
	double weibull_betha = 0.0012639;
	double normal_mu = 0.054792;
	double normal_sigma = 0.205602;
	double exponentialMe_lambda = 18.250783;
	double exponentialLr_lambda = 2.023115;
	double paretoLr_alpha = 0.225451;
	double paretoLr_xm = 0.000000;
	double paretoMlh_alpha = 0.171674;
	double paretoMlh_xm = 0.000000;
	double cauchy_gamma = 0.000067;
	double cauchy_x0 = 0.005750;
	double acErr = 0.001;

	vec paramVec = zeros<vec>(2);
	vec infoCriterion = zeros<vec>(2);

	weibullFitting(interArrival, *interArrivalCdf, paramVec, infoCriterion);
	if (!compareDouble(paramVec(0), weibull_alpha, acErr))
	{
		cout << "weibullFitting alpha" << endl;
		return (false);
	}
	if (!compareDouble(paramVec(1), weibull_betha, acErr))
	{
		cout << "weibullFitting betha" << endl;
		return (false);
	}

	normalFitting(interArrival, paramVec, infoCriterion);
	if (!compareDouble(paramVec(0), normal_mu, acErr))
	{
		cout << "normalFitting mu" << endl;
		return (false);
	}
	if (!compareDouble(paramVec(1), normal_sigma, acErr))
	{
		cout << "normalFitting sigma" << endl;
		return (false);
	}

	exponentialMeFitting(interArrival, paramVec, infoCriterion);
	if (!compareDouble(paramVec(0), exponentialMe_lambda, acErr))
	{
		cout << "exponentialLrFitting lambda" << endl;
		return (false);
	}

	exponentialLrFitting(interArrival, *interArrivalCdf, paramVec,
			infoCriterion);
	if (!compareDouble(paramVec(0), exponentialLr_lambda, acErr))
	{
		cout << exponentialLr_lambda << ":" << paramVec(0) << endl;
		cout << "exponentialLrFitting lambda" << endl;
		return (false);
	}

	paretoLrFitting(interArrival, *interArrivalCdf, paramVec, infoCriterion);
	if (!compareDouble(paramVec(0), paretoLr_alpha, acErr))
	{
		cout << "paretoLrFitting alpha" << endl;
		return (false);
	}
	if (!compareDouble(paramVec(1), paretoLr_xm, acErr))
	{
		cout << "paretoLrFitting xm" << endl;
		return (false);
	}

	paretoMlhFitting(interArrival, *interArrivalCdf, paramVec, infoCriterion);
	if (!compareDouble(paramVec(0), paretoMlh_alpha, acErr))
	{
		cout << "paretoMlhFitting alpha" << endl;
		return (false);
	}
	if (!compareDouble(paramVec(1), paretoMlh_xm, acErr))
	{
		cout << "paretoMlhFitting xm" << endl;
		return (false);
	}

	cauchyFitting(interArrival, *interArrivalCdf, paramVec, infoCriterion);
	if (!compareDouble(paramVec(0), cauchy_gamma, acErr))
	{
		cout << "cauchyFitting" << endl;
		return (false);
	}
	if (!compareDouble(paramVec(1), cauchy_x0, acErr))
	{
		return (false);
	}

	delete interArrivalCdf;

	return (true);
}

inline bool DataProcessor::test_modelSelection()
{

	//mat M;
	//M.load("CppAlgorithms/data_sample.txt");
	//vec interArrival = sort(M.col(3)) + min_time;
	vec interArrival = sort(interArrivalSample) + min_time;
	int m = interArrival.size();

	list<double> list_interArrival;
	vec* interArrivalCdf;
	for (int i = 0; i < m; i++)
	{
		list_interArrival.push_back(interArrival(i));
	}
	interArrivalCdf = empiricalCdf(list_interArrival);

	StochasticModelFit* modelVet = NULL;
	modelVet = fitModels(list_interArrival, "aic");
	//fitModels(list_interArrival, "aic", modelVet);

	int numberOfModels = modelVet[0].size;
	for (int i = 0; i < numberOfModels; i++)
	{
		cout << modelVet[i].modelName << " " << "modelVet[" << i << "] = "
				<< modelVet[i].aic << " param1=" << modelVet[i].param1
				<< " param2=" << modelVet[i].param2 << endl;
	}

	delete interArrivalCdf;
	delete[] modelVet;
	return (true);
}

#endif

