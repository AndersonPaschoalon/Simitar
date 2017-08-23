WORKSPACE = ..
TEST = $(UBA) 
CC = gcc
CXX = g++
RM = rm -f
CPPFLAGS =
LDFLAGS =
LDLIBS = -Wl,-Bdynamic -lpthread -llog4cpp -lsqlite3 -larmadillo -lITG 
LSLIBS = -Wl,-Bstatic $(WORKSPACE)/libs/libsimitar.a
INCLUDES = -I$(WORKSPACE)/common/
LIBPATH = -I$(WORKSPACE)/common/
SRCS = ./src/*.cpp ./src/*.h
OBJS = ./src/*.o
BIN = trace-analyzer

all: distclean clean trace-analyzer

trace-analyzer:
	echo $(TEST)
	$(CXX) -c $(SRCS) $(INCLUDES)
	mv *.o src/ 
	$(CXX) $(LDFLAGS) -o $(BIN) $(OBJS) $(LSLIBS) $(LDLIBS) $(INCLUDES)  $(LIBPATH) 

clean:
	$(RM) $(OBJS) src/*.gch

distclean: clean
	$(RM) $(BIN)
