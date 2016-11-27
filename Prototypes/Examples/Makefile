
all:
	clear
	g++  cpp_tests.cpp  -l sqlite3 -Wall -std=c++11 -o cpp_tests_1
	g++  cpp_tests2.cpp  -l sqlite3 -Wall -std=c++11 -o cpp_tests_2 -pthread
	g++  cpp_tests3.cpp  -l sqlite3 -Wall -std=c++11 -o cpp_tests_3
	g++ cpp_factory.cpp -Wall -o cpp_factory
	g++ cpp_getHostIP.cpp -Wall -o cpp_getHostIP 
	g++ cpp_armadillo.cpp -o cpp_armadillo  -O2 -larmadillo -std=c++0x
	g++ cpp_fileStream.cpp -o cpp_fileStream

clean:
	rm -f cpp_tests_1 cpp_tests_2 cpp_tests_3
