################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataProcessor.cpp \
../src/DatabaseInterface.cpp \
../src/DummyFlow.cpp \
../src/Main.cpp \
../src/NetworkFlow.cpp \
../src/NetworkTrace.cpp \
../src/RegressionTests.cpp \
../src/StochasticModelFit.cpp \
../src/cfunctions.cpp 

OBJS += \
./src/DataProcessor.o \
./src/DatabaseInterface.o \
./src/DummyFlow.o \
./src/Main.o \
./src/NetworkFlow.o \
./src/NetworkTrace.o \
./src/RegressionTests.o \
./src/StochasticModelFit.o \
./src/cfunctions.o 

CPP_DEPS += \
./src/DataProcessor.d \
./src/DatabaseInterface.d \
./src/DummyFlow.d \
./src/Main.d \
./src/NetworkFlow.d \
./src/NetworkTrace.d \
./src/RegressionTests.d \
./src/StochasticModelFit.d \
./src/cfunctions.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -p -pg -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


