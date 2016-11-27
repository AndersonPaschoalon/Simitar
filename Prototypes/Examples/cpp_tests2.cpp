#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string>
#include <array>
#include <cstring>
#include <string.h>
#include <list>
#include <thread>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <time.h>
//string-file
#include <fstream>



using namespace std;

//Classes and functions unther test--------------------------------------------
class Flow{
public:
	Flow(){
		protocol = "";
		npackets = 0;	
	}
	~Flow(){
	}
	void setProtocol(string p){
		protocol = p;
	}
	void setNpackets(int n){
		npackets = n;
	}

	string getProtocol(){return protocol;}
	int getNpackets(){return npackets;}

	void disp(){
		cout << "protocol: " << protocol << ", npackets: " << npackets << endl;
	}

private:
	string protocol;
	int npackets;
};

class Trace{
public:
	Trace(int nf){
		vFlow = new Flow[nf];
		m_nflows = nf;
	}
	~Trace(){
		delete []  vFlow;
	}	
	void setName(string n){ m_name = n;}

	Flow* vFlow;
	int getNflows(){return m_nflows;}

	void disp(){
		cout << "name: " << m_name << endl; 
		cout << "---------------------" << endl;
		int i = 0;
		for(i = 0; i < m_nflows; i++)
		{
			cout << i << ": ";
			vFlow[i].disp();
		
		}
		
		
	}	

private:
	string m_name;	
	int m_nflows;
};

class Calc{
public:
	Calc(){}
	~Calc(){}
	void setFlows(int n , Trace* t){
		int nflow = 0;
		int i = 0;
		nflow = t->getNflows();
		t->vFlow[0].setProtocol("TCP");
		t->vFlow[0].setNpackets(10);
		for(i = 1; i< nflow; i++)
		{
			t->vFlow[i].setProtocol("UDP");
			t->vFlow[i].setNpackets(n);
		}
	
	}
private:
};

class Wrapper {
public:
	void member1() {
//		std::cout << "i am member1" << std::endl;
		valor1 = 0;
		valor2 = 3;
//		cout << "valor1 = " << valor1 << ", valor2 = " << valor2 << endl ;
		printf("i am member 1 -> valor1=%d, valor2=%d\n", valor1, valor2);
	}
	void member2(const char *arg1, unsigned arg2) {
//		std::cout << "i am member2 and my first arg is (" << arg1 << ") and second arg is (" << arg2 << ")" << std::endl;
		valor1 = (int) arg2;
		valor2 = 7;

		sleep(arg2);
//		cout << "valor1 = " << valor1 << ", valor2 = " << valor2 << endl;
		printf("i am member 2 and my first arg is (%s) and my second arg is (%d) -> valor1=%d, valor2=%d\n",arg1, (int)arg2, valor1, valor2 );

	}
	std::thread member1Thread() {
		return std::thread([=] { member1(); });
	}
	std::thread member2Thread(const char *arg1, unsigned arg2) {
		return std::thread([=] { member2(arg1, arg2); });
	}
private:
	int valor1;
	int valor2;
	string val;
	string val2;
	float b;
	double c;
	int bob;
	int mac;
};

class testC{
public:
	int getVal(){return 5;}

private:
};

//Call functions---------------------------------------------------------------
void error1(void)
{
	int* p = NULL;
	int* f = NULL;
	p = f;
	f = f+1;
	if(p == NULL)
	{
		errno = ENOMEM;
		perror("Incorrect memmory allocation");
		exit(11);
						
	}

	return;
}


void class_test()
{
	int nflows = 10;
	Trace t(nflows);
	Calc c;
	
	t.setName("blavla");
	c.setFlows(15, &t);
	t.disp();	

	return;
}

void thread1()
{
	Wrapper *w = new Wrapper();
	Wrapper *w2 = new Wrapper();
	std::thread tw11 = w->member1Thread();
	std::thread tw21 = w2->member2Thread("oi", 30);
	std::thread tw12 = w->member2Thread("hello", 100);
	sleep(2);
	std::thread tw13 = w->member1Thread();
	std::thread tw22 = w2->member1Thread();
	std::thread tw23 = w2->member2Thread("oi", 30);
	std::thread tw14 = w->member2Thread("hello", 100);
	tw11.join();
	tw12.join();
	tw13.join();
	tw14.join();
	tw21.join();
	tw22.join();
	tw23.join();

	delete w;
	delete w2;

	return;
}

void thread2(void)
{
	//Wrapper* w = new Wrapper[10]; 
	//testC* t = new testC[5];
	//testC** tt = &t;
	//cout << tt[0]->getVal() << endl;
	//cout << tt[1]->getVal() << endl;
	//cout << tt[4]->getVal() << endl;
		
	int size = 10;
	Wrapper* w = new Wrapper[size];
//	Wrapper** ww = &w; 
	std::thread* tw = new std::thread[size];
	
	for (int i = 0; i < size; i++)
	{
		//printf("%d: ", i);
		tw[i] = w[i].member2Thread("bus", i);

	}
	for (int i = 0; i < size; i++)
	{
		tw[i].join();
	}

	delete [] w;
	delete [] tw;

	return;
}

void error2()
{
	cout << "testando perror()\n" << endl;
	perror("Usando perror()");

	cout << "abrinfo um aquivo que não existe" << endl;
	FILE *fp;
	/* first rename if there is any file */
	rename("file.txt", "newfile.txt");
	/* now let's try to open same file */
	fp = fopen("file.txt", "r");
	if( fp == NULL ) 
	{
		perror("Error: ");
		return;
	}

	return;
}

int frequency_of_primes (int n) 
{
	int i,j;
	int freq=n-1;
	for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
	return freq;
}

void clockTest(void)
{
	clock_t t;
	int f;
	t = clock();
	printf ("Calculating...\n");
	f = frequency_of_primes (99999);
	printf ("The number of primes lower than 100,000 is: %d\n",f);
	t = clock() - t;
	printf ("It took me %d clicks (%f seconds).\n", (int)t,((float)t)/CLOCKS_PER_SEC);

	return;
}

void listSort(void)
{	
	list<double> mylist;

	mylist.push_back(12.222);
	mylist.push_back(12.222);
	mylist.push_back(15.555);
	mylist.push_back(0.222);
	mylist.push_back(0.022);
	mylist.push_back(0.022);
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3.3);
	mylist.push_back(16.222);
	mylist.push_back(16.222);
	
	mylist.sort();

	for (list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	return;
}

void string_file()
{
	std::string item_name;
	std::ifstream nameFileout;

	nameFileout.open("file_cpptest2.txt");
	while (nameFileout >> item_name)
	{
		std::cout << item_name;
		cout << endl;
	}
	nameFileout.close();

}


// ler esse turotial http://www.learncpp.com/cpp-tutorial/811-static-member-variables/

int main(){

	string test="string-file";

	if(test == "class"){
		class_test();
	}
	else if (test == "thread1"){
		thread1();
	}
	else if(test == "thread2")
	{
		thread2();
	}
	else if(test == "error1")
	{
		error1();		
	}
	else if (test == "error2")
	{
		error2();
	}
	else if (test == "clock")
	{
		clockTest();		
	}
	else if (test == "list-sort")
	{
		listSort();
	}
	else if (test == "string-file")
	{
		string_file();
	}

	return 0;
}

