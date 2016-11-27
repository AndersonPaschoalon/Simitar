#include <iostream>
#include <fstream>
using namespace std;


void save_data_on_file(const string& fileName, const string& data )
{
	string file_out = fileName + ".txt";

	ofstream writeOnFile(file_out, ios::out);
	if (!writeOnFile)
	{
		cerr << "file could not be oppeded" << endl;
		exit(1);
	}

	writeOnFile << data << endl;

}

void exec_save_data_on_file()
{
	save_data_on_file("arq-teste","nome1" );	
	save_data_on_file("arq-teste","nome1" );	
	save_data_on_file("arq-teste","12" );	
	save_data_on_file("arq-teste","53" );	
}


int main()
{
	exec_save_data_on_file();

	return(0);
}
