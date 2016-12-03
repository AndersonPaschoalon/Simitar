#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string>
#include <array>
#include <cstring>
#include <string.h>
#include <list>

using namespace std;

/*
 - classes, getters e setters
 - classe string
 - sqlite3
 */

static int sqlite_callback(void *data, int argc, char **argv, char **azColName);

struct foo
{
	foo() :
			a(true), b(true)
	{
	}
	bool a;
	bool b;
	bool c;
} bar;

int sqlite3_opendb()
{
	sqlite3 *db;
//	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("trace.db", &db);

	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);

	return (0);
}

int string_tests()
{
	string str1 = "blablabla";
	string str2[4] =
	{ "1", "2", "3", "4" };
	string* p_str1 = NULL;
	string str_vet[10];
	string* str_vet2;

	cout << "str1: " << str1 << endl;

	cout << "str2[2]: " << str2[2] << endl;

	p_str1 = new string("---->");
	cout << "p_str: " << *p_str1 << endl;

	str_vet[0] = "vetor1<<<<<<<<>>>>>>>>>>>>>>>>>    >>";
	str_vet[1] = "2";
	cout << "str_vet[1:2]: " << str_vet[0] << ", " << str_vet[1] << endl;

	str_vet2 = new string[5];
	str_vet2[0] = "str0";
	str_vet2[1] = "str1";
	str_vet2[2] = "str2";
	str_vet2[3] = "str3";
	str_vet2[4] = "str4";

	cout << "str_vet2[0].size() = " << str_vet2[0].size() << endl;
	cout << "str_vet2[0].length() = " << str_vet2[0].length() << endl;
	cout << "str_vet[0:3]: " << str_vet2[0] << ", " << str_vet2[1] << ", "
			<< str_vet2[2] << ", " << str_vet2[3] << endl;
	str_vet2[0] = "str0str0str0str0str0str0str0str0str0str0";
	cout << "str_vet[0:3]: " << str_vet2[0] << ", " << str_vet2[1] << ", "
			<< str_vet2[2] << ", " << str_vet2[3] << endl;
	str_vet2[0] = "0";
	cout << "str_vet[0:3]: " << str_vet2[0] << ", " << str_vet2[1] << ", "
			<< str_vet2[2] << ", " << str_vet2[3] << endl;
	str_vet2[0] = "str0";
	str_vet2[0] = str_vet2[0] + str_vet2[1] + str_vet2[2];
	cout << str_vet2[0] << endl;
	cout << "str_vet2[0].size() = " << str_vet2[0].size() << endl;
	cout << "str_vet2[0].length() = " << str_vet2[0].length() << endl;

	delete p_str1;
	// usar delete[] quando for deletar um vetor
	delete[] str_vet2;
	p_str1 = 0;
	str_vet2 = 0;

	return (0);
}

int array_test()
{
	int i = 0;

	//--------------------------------------
	array<int, 5> myints;
	myints[0] = 0;
	myints[1] = 11;
	myints[2] = 222;
	myints[3] = 3333;
	myints[4] = 44444;
	cout << "myints[]:";
	for (i = 0; i < 5; i++)
		cout << " " << myints[i];
	cout << endl;

	//--------------------------------------
	array<string, 3> mystring;
	mystring[0] = "a";
	mystring[1] = mystring[0] + "bb";
	mystring[2] = mystring[1] + "ccc";
	cout << "mystring[]:";
	for (i = 0; i < 3; i++)
		cout << " " << mystring[i];
	cout << endl;

	cout << "myints.size() = " << myints.size() << endl;
	cout << "mystring.size() = " << mystring.size() << endl;

	return (0);
}

class nest
{
public:
	nest()
	{
	}
	virtual ~nest()
	{
	}
	void toString()
	{
		cout << "Nested method" << endl;
	}

};

class test_class
{
public:
	test_class()
	{
		intTest = 0;
		strTest = "default";
		p_nest = NULL;
	}

	virtual ~test_class()
	{
	}

	const int& getIntTest() const
	{
		return intTest;
	}
	const string& getStrTest() const
	{
		return (strTest);
	}

	void setIntTest(const int& value)
	{
		intTest = value;
	}
	void setStrTest(const string& str)
	{
		strTest = str;
	}

	nest* p_nest;

private:
	string strTest;
	int intTest;
};

int class_test()
{
	int i = 10;
	string r = "string teste r";
	test_class t;
	cout << "t.getIntTest() = " << t.getIntTest() << endl;
	i = 5;
	t.setIntTest(i);
	cout << "t.getIntTest() = " << t.getIntTest() << endl;
	i = 2222;
	cout << "t.getIntTest() = " << t.getIntTest() << endl;
	t.setStrTest(r);
	cout << "t.getIntTest() = " << t.getStrTest() << endl;
	r = "aaaaaaaa";
	t.setStrTest("teste2");
	cout << "t.getIntTest() = " << t.getStrTest() << endl;

	cout << endl << "Nested class test" << endl;
	test_class* a;
	nest* n;
	a = new test_class();
	n = new nest();
	a->p_nest = n;
	a->p_nest->toString();

	return (0);
}

int new_delete_test()
{
	int* p = NULL;
	int i = 0;

	p = new int[10];
	for (i = 0; i < 10; i++)
	{
		p[i] = i + 1;
	}
	for (i = 0; i < 10; i++)
		cout << ' ' << i;

	delete p;
	p = 0;
	return (0);
}

class Flow
{
public:
	Flow() :
			p1(1), p2(2), p3(3), s1("f1"), s2("f2")
	{
		v1[0] = 11;
		v1[1] = 12;
		v2[0] = 21;
		v2[1] = 22;
		cout << "Flow constructed." << endl;
	}

	const int& getP1() const
	{
		return p1;
	}
	const int& getP2() const
	{
		return p2;
	}
	const int& getP3() const
	{
		return p3;
	}
	const int* getV1() const
	{
		return v1;
	}
	const int* getV2() const
	{
		return v2;
	}
	const string& getS1() const
	{
		return s1;
	}
	const string& getS2() const
	{
		return s2;
	}
	const string& getS3() const
	{
		return s3;
	}
	void setP1(int val)
	{
		p1 = val;
	}
	string toString()
	{
		return ("[" + s1 + ", " + s2 + "] ");
	}

private:
	int p1;
	int p2;
	int p3;
	int v1[2];
	int v2[2];
	string s1;
	string s2;
	string s3;
};

class Trace
{
public:
	Trace(int nflows)
	{
		nFlows = nflows;
		flow = NULL;
		flow = new Flow[nFlows];
		flow_counter = 0;

	}

	virtual ~Trace()
	{
		delete[] flow;
	}

	string toString()
	{
		string msg = "\n>nFlows: ";
		msg = msg + std::to_string(nFlows);

		return (msg);

	}

//	int pushBackFlow(Flow* newflow){
//		if(flow_counter > nFlows){
//			return(1);
//		}
//	
//		flow[flow_counter].setP1(newflow.getP1());
//		flow_counter++;
//
//
//		return(0);
//	}

	Flow* flow;
private:
	int nFlows;
	int flow_counter;
};

int sqlite_select_callback()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("trace.db", &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return (0);
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	//sql = "SELECT * from COMPANY";
	string sqlQuery = "select ip__dst from TraceCapture;";

	sql = new char[sqlQuery.length() + 1];
	strcpy(sql, sqlQuery.c_str());

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, sqlite_callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Operation done successfully\n");
	}

	delete[] sql;
	sqlite3_close(db);
	return 0;
}

static int sqlite_callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*) data);
	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int sqlite_select_version()
{
	sqlite3 *db;
	sqlite3_stmt *res;
	int rc;
	string sqlQuery;
	char* sql = NULL;

	//Open Database
	rc = sqlite3_open("trace.db", &db);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return 1;
	}

	/* Create SQL statement */
	sqlQuery = "select ip__dst from TraceCapture;";
	sql = new char[sqlQuery.length() + 1];
	strcpy(sql, sqlQuery.c_str());

	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	rc = sqlite3_step(res);
	if (rc == SQLITE_ROW)
	{
		printf("%s\n", sqlite3_column_text(res, 0));
	}

	delete[] sql;
	sqlite3_finalize(res);
	sqlite3_close(db);

	return 0;
}

int sqlite_select()
{
	sqlite3 *db;
	sqlite3_stmt *res;
	int rc;

	//open database
	rc = sqlite3_open("trace.db", &db);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return 1;
	}

	//create SQL statement	
	rc = sqlite3_prepare_v2(db, "select ip__dst from TraceCapture;", -1, &res,
			0);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	while (true)
	{
		rc = sqlite3_step(res);
		if (rc != SQLITE_ROW)
		{
			break;
		}

		printf("%s\n", sqlite3_column_text(res, 0));
	}

	sqlite3_finalize(res);
	sqlite3_close(db);

	return 0;
}

int string_test42()
{
	cout << "Blabla\"" << endl;

	return (0);
}

void f(int* p)
{
	*p = 55;

}

int simple_pointer_test()
{
	int * pointer = NULL;
	pointer = new int;
	*pointer = 10;

	cout << "*pointer = " << *pointer << endl;
	f(pointer);
	cout << "*pointer = " << *pointer << endl;

	cout << endl << "silly string test" << endl;

	string batata;
	char potato[] = "batatafrita";
	batata = potato;

	cout << "batata = " << batata << endl;

	cout << endl << "atoi()" << endl;
	int some_int = atoi("45");
	cout << "some_int(45) = " << some_int << endl;
	int int_to_string = 234;
	char buffer[30];
	snprintf(buffer, sizeof(buffer), "%d", int_to_string);
	cout << "buffer = " << buffer << endl;
	string dstr = "2015.2231";
	double buffer_stod = 0;
	buffer_stod = stod(dstr, NULL);
	cout << "buffer_stod = " << buffer_stod << endl;

	std::string orbits("365.24 29.53");
	std::string::size_type sz;     // alias of size_t
	double earth = std::stod(orbits, &sz);
	double moon = std::stod(orbits.substr(sz));
	std::cout << "The moon completes " << (earth / moon)
			<< " orbits per Earth year.\n";

	delete pointer;
	return 0;
}

int list_outsider(list<int>& framboesa)
{
	framboesa.push_back(2);
	framboesa.push_back(4);
	framboesa.push_back(8);
	framboesa.push_back(16);
	framboesa.push_back(32);
	framboesa.push_back(64);

	return 0;
}

int list_tests()
{
	cout << "Testint simple integer list" << endl;
	list<int> banana;

	banana.push_back(1);
	banana.push_back(2);
	banana.push_back(4);
	banana.push_back(5);
	banana.push_back(44);
	banana.push_back(45);
	cout << "list banana: ";
	for (list<int>::iterator it = banana.begin(); it != banana.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << endl;
	list<int> framboesa;
	list_outsider(framboesa);
	cout << "list framboesa: ";
	for (list<int>::iterator it = framboesa.begin(); it != framboesa.end();
			it++)
	{
		cout << *it << ' ';
	}
	cout << endl;

	cout << endl << "Testing lists of custom objects (Flow)" << endl;
	Flow f1;
	Flow f2;
	Flow f3;
	Flow f4;
	Flow f5;
	Flow f6;
	list<Flow> flow_list;
	flow_list.push_back(f1);
	flow_list.push_back(f2);
	flow_list.push_back(f3);
	flow_list.push_back(f4);
	flow_list.push_back(f5);
	flow_list.push_back(f6);
	cout << "Flows: ";
	for (std::list<Flow>::iterator it = flow_list.begin();
			it != flow_list.end(); it++)
	{
		//std::cout << *it << ' ';
		std::cout << it->toString() << ' ';
	}
	cout << "; size = " << flow_list.size() << endl;

	return 0;
}

long int most_frequent(list<long int>& thelist)
{
	int maxSize = 0;
	int* vetSizeOcurrence = NULL;
	int itVet = 0; //vector iterator
	int numberOccurrences = 0;
	int mostFrequent = 0;

	for (list<long int>::iterator it = thelist.begin(); it != thelist.end();
			it++)
	{
		if (*it > maxSize)
		{
			maxSize = *it;
		}
	}

	vetSizeOcurrence = new int[maxSize + 1];
	//init vector
	for (itVet = 0; itVet < maxSize + 1; itVet++)
	{
		vetSizeOcurrence[itVet] = 0;
	}
	//fill vector with the number of ocurrences of each size
	for (list<long int>::iterator it = thelist.begin(); it != thelist.end();
			it++)
	{
		vetSizeOcurrence[*it]++;
	}
	//choose the value with more occurences
	for (itVet = 0; itVet < maxSize + 1; itVet++)
	{
		if (vetSizeOcurrence[itVet] > numberOccurrences)
		{
			numberOccurrences = vetSizeOcurrence[itVet];
			mostFrequent = itVet;
			//DEBUG
			cout << "now the most frequent is " << itVet << " (x"
					<< numberOccurrences << ")" << endl;
		}
	}

	delete[] vetSizeOcurrence;

	return ((long int) mostFrequent);
}

int mostFrequent_test()
{
	list<long int> f;
	long int val = 0;

	f.push_back(1);
	f.push_back(2);
	f.push_back(3);
	f.push_back(7);
	f.push_back(9);
	f.push_back(2);
	f.push_back(12);
	f.push_back(44);
	f.push_back(9);
	f.push_back(1);
	f.push_back(12);
	f.push_back(12);
	f.push_back(6);
	f.push_back(12);
	f.push_back(12);
	f.push_back(9);
	f.push_back(0);

	val = most_frequent(f);

	cout << "most frequent return: " << val << endl;

	return 0;
}
int testRef1(const int& a1, int& a2)
{
	//a1 = 13;//error!!
	a2 = 14;
	cout << "a1 = " << a1 << " a2 = " << a2 << endl;

	return (0);
}
int testPointer1(const int* a1, int* a2)
{
	*a2 = 22;
	//*a1 = 11;//error!!
	cout << "a1 = " << *a1 << " a2 = " << *a2 << endl;
	return (0);
}

int main(int argc, char * argv[])
{
	string test = "misc";

	if (test == "classes")
	{
		printf("\n>sqlite3_tests()\n");
		sqlite3_opendb();

		printf("\n array_test()\n");
		array_test();

		printf("class_test()\n");
		class_test();

		printf("new_delete_test()\n");
		new_delete_test();

		printf("\nTrace-flow test\n");
		Trace t(5);
		cout << t.toString() << endl;
		cout << t.flow[1].getP1() << endl;
		t.flow[1].setP1(8);
		cout << t.flow[1].getP1() << endl;

		printf("\n>ending tests.\n");
	}
	else if (test == "sqlite")
	{
		//sqlite_select_callback();
		sqlite_select();

	}
	else if (test == "string")
	{
		printf("\n>string_tests()\n");
		string_tests();
		string_test42();
		simple_pointer_test();
	}
	else if (test == "list")
	{
		list_tests();
		mostFrequent_test();

	}
	else if (test == "classes2")
	{

	}
	else if (test == "misc")
	{
		int a1 = 1;
		int a2 = 2;
		testRef1(a1, a2);
		testPointer1(&a1, &a2);
		cout << "a1 = " << a1 << " a2 = " << a2 << endl;
	}
	

	return (0);
}

