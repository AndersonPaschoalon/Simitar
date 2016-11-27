#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using std::ios;
using std::cout;
using std::endl;
using std::ifstream;


int getHostIP(int* counter, char* ipAddr);
bool isEmpty(std::ifstream& pFile);

int getHostIP(int* counter, char* ipAddr)
{
	int filePosition = 0;
	char defaultIpAddr[] = "127.0.0.1";

	if(*counter == 0)
		*counter = 1;
	
	ifstream hostIpList("hostIpList.txt", ios::in);
	if(!hostIpList || isEmpty(hostIpList))
	{
		printf("*Warning*: hostIpList.txt file is empty or do not exist.\nUsing default IP address 127.0.0.1\n");
		strcpy(ipAddr, defaultIpAddr);
		return (1);
	}
	else{ //no empty file
	
		hostIpList >> ipAddr;
		filePosition++;

		while( !hostIpList.eof() )
		{
			if( filePosition < *counter)
			{
				hostIpList >> ipAddr;
				filePosition++;
			}
			else
			{
				(*counter)++;
				break;
			}
		}
		if(hostIpList.eof())
		{
			//EOF reached
			hostIpList.clear();
			hostIpList.seekg(0);
			hostIpList >> ipAddr;
			*counter = 2;
		}
	}

	return(0);
}

bool isEmpty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}


int main()
{
	int* counter = NULL;
	int i = 0;
	char ipAddr[30];

	counter = (int*)malloc(sizeof(int));
	*counter = 0;

	(*counter) = 0;	


	for(i = 0; i < 30; i++)
	{
		getHostIP(counter, ipAddr); 
		cout << i << ": " << ipAddr << endl;

	}

	free(counter);

	return 0;
}

