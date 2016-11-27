#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

#define FACTORY 1


class FlowIf
{
public: 
	FlowIf(){};
	virtual ~FlowIf(){};
	virtual void flow_generate() = 0;
	virtual void constFunc() const = 0;

#ifdef FACTORY
	static FlowIf *make_flow(int choise);
#endif

};


class DummyFlow: public FlowIf
{
public:

	void constFunc() const
	{
		cout << "test const" << endl;
	}
	void flow_generate()
	{
		cout << "[generating dummy flow]" << endl;
	}

};

class DitgFlow: public DummyFlow
{
public:
	void flow_generate()
	{
		cout << "[generating D-ITG flow]" << endl;
	}

};

class OstinatoFlow: public DummyFlow
{
public:
	void flow_generate()
	{
		cout << "[generating Ostinato flow]" << endl;
	}

};

class TgFlow: public DummyFlow
{
public:
	void flow_generate()
	{
		cout << "[generating TG flow]" << endl;
	}

};

class SeagullFlow: public DummyFlow
{
public:
	void flow_generate()
	{
		cout << "[generating Seagull flow]" << endl;
	}

};

#ifndef FACTORY
int main ()
{
	vector<FlowIf*> traceFlows;
	int choise;

	while (true)
	{
		cout << "D-ITG(1) Ostinato(2) TG(3) Seagull(4)  Dummy(default) Exit(0):" << endl;
		cin >> choise;
		if(choise == 0) 
			break;
		else if (choise == 1)
			traceFlows.push_back(new DitgFlow);
		else if (choise == 2)
			traceFlows.push_back(new OstinatoFlow);
	
		else if (choise == 3)
			traceFlows.push_back(new TgFlow);
	
		else if (choise == 4)
			traceFlows.push_back(new SeagullFlow);
	
		else
			traceFlows.push_back(new DummyFlow);
	
	}
	for (int i = 0; i < traceFlows.size(); i++)
		traceFlows[i]->flow_generate();
	for (int i = 0; i < traceFlows.size(); i++)
		delete traceFlows[i];

	return(0);

}
#endif

#ifdef FACTORY
FlowIf *FlowIf::make_flow(int choise)
{
	cout << "Factory call. opt=" << choise << endl;
	if (choise == 1)
		return new DitgFlow;
	else if (choise == 2)
		return new OstinatoFlow;
	else if (choise == 3)
		return new TgFlow;
	else if (choise == 4)
		return new SeagullFlow;
	else 
		return new DummyFlow;
}

int main ()
{
	vector<FlowIf*> traceFlows;
	int choise;

	while (true)
	{
		cout << "D-ITG(1) Ostinato(2) TG(3) Seagull(4)  Dummy(default) Exit(0):" << endl;
		cin >> choise;
		if(choise == 0) 
			break;
		else
			traceFlows.push_back(FlowIf::make_flow(choise));
	
	}
	for (unsigned int i = 0; i < traceFlows.size(); i++)
		traceFlows[i]->flow_generate();
	for (unsigned int i = 0; i < traceFlows.size(); i++)
		delete traceFlows[i];

	return(0);

}
#endif




