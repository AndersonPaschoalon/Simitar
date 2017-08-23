WORKSPACE = ..
CC = g++ 
#LIB_DIR = $(WORKSPACE)/libs
LIB_FILE_NAME = libsimitar.a
SOURCE_DIR = $(WORKSPACE)/common
HEADERS_DIR = $(WORKSPACE)/common
SOURCES = $(SOURCE_DIR)/*.cpp
HEADERS = $(SOURCE_DIR)/*.h


all:target clean-obj

target:
	g++ -c $(SOURCES) $(HEADERS)
	ar rvs $(LIB_FILE_NAME)   *.o

clean-obj:
	rm -f *.o  *.gch

clean-target:
	rm -f *.a

clean:clean-obj clean-target

remake: clean  all


