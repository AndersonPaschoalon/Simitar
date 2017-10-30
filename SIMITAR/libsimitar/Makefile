################################################################################
# libsimitar makefile
################################################################################

# exec file name
EXEC_FILE	:= 

# static lib name
STATIC_LIB	:= libsimitar.a

# static lib name
SHARED_LIB	:= 

# Directory where the make command will be done. If it is the same were the
# makefile is placed, just put "."
WORKSPACE	:= ..

#
SRC_DIR		:= $(WORKSPACE)/libsimitar

#
HEADER_DIR	:= $(WORKSPACE)/libsimitar

#
OBJ_DIR		:= $(WORKSPACE)/libsimitar/obj

# compiler default
CC 			:= g++

# compiler
CXX 		:= g++

# static lybrary archiver
AR			:= ar rvs  

# shared lybrary 
LD 			:= g++ -shared -o  

#
RM 			:= rm -rf

#
CPP_FILES 	:= $(wildcard $(SRC_DIR)/*.cpp) # do not change

#
H_FILES 	:= $(wildcard $(HEADER_DIR)/*.h) # do not change

#
OBJ_FILES 	:= $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o))) # do not change

#
LD_FLAGS 	:= 

#
CC_FLAGS 	:=  -fmessage-length=0 -std=c++11 -O0 -g3 -p -pg -ftest-coverage -fprofile-arcs -Wall

# dynamic lybrary argument: "-Wl,-Bdynamic -ldynamic-lib-name". Eg.: "-Wl,-Bdynamic -lpthread"
# LD_LIBS 	:= -Wl,-Bdynamic -lpthread -llog4cpp -lsqlite3 -larmadillo -lITG 


# static lybrary argument: "-Wl,-Bstatic static-lib-name" 
#LS_LIBS		:= -Wl,-Bstatic $(WORKSPACE)/libs/libsimitar.a
LS_LIBS		:= 

# place here any include directory argument in the format "-Idir-name/"
INCLUDES 	:=  -I $(WORKSPACE)/deps/ -I $(WORKSPACE)/libsimitar/

# Macros for timing compilation
ifeq ($(UNAME_S),Darwin)
	CUR_TIME = awk 'BEGIN{srand(); print srand()}'
	TIME_FILE = $(dir $@).$(notdir $@)_time
	START_TIME = $(CUR_TIME) > $(TIME_FILE)
	END_TIME = read st < $(TIME_FILE) ; \
		$(RM) $(TIME_FILE) ; \
		st=$$((`$(CUR_TIME)` - $$st)) ; \
		echo $$st
else
	TIME_FILE = $(dir $@).$(notdir $@)_time
	START_TIME = date '+%s' > $(TIME_FILE)
	END_TIME = read st < $(TIME_FILE) ; \
		$(RM) $(TIME_FILE) ; \
		st=$$((`date '+%s'` - $$st - 86400)) ; \
		echo `date -u -d @$$st '+%H:%M:%S'`
endif


all: $(STATIC_LIB)

$(EXEC_FILE): $(OBJ_FILES)
	mkdir -p $(OBJ_DIR)
	@printf  "\n* Linking: $@"
	@$(START_TIME)
	$(CC) $(LD_FLAGS) -o $@ $^ $(INCLUDES) $(LD_LIBS) $(LS_LIBS)
	@printf "\t Link time: " 
	@$(END_TIME)

$(STATIC_LIB): $(OBJ_FILES)
	mkdir -p $(OBJ_DIR)
	@printf  "\n* Archiving: $@"
	@$(START_TIME)
	$(AR) $@  $^ 
	@printf "\t Link time: " 
	@$(END_TIME)

$(SHARED_LIB): $(OBJ_FILES)
	echo "\nTODO"
	#$(LD) $@  $^ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	@printf  "\n* Compiling: $< -> $@"
	@$(START_TIME)
	$(CC) $(CC_FLAGS) -c -o $@ $< $(INCLUDES)
	@printf "\t Compile time: " 
	@$(END_TIME)

clean:
	$(RM) $(OBJ_DIR)/*
	$(RM) $(EXEC_FILE)
	$(RM) $(STATIC_LIB)
	$(RM) $(SHARED_LIB)

test:
	make all 
	$(CC) $(LD_FLAGS) -o $@ $^ $(INCLUDES) $(LD_LIBS) $(LS_LIBS)
	./test

remake: clean  all






