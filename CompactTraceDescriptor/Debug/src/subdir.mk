################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataProcessor.cpp \
../src/DatabaseInterface.cpp \
../src/DitgFlow.cpp \
../src/DummyFlow.cpp \
../src/Main.cpp \
../src/NetworkFlow.cpp \
../src/NetworkTrace.cpp \
../src/StochasticModelFit.cpp \
../src/TestClass.cpp 

OBJS += \
./src/DataProcessor.o \
./src/DatabaseInterface.o \
./src/DitgFlow.o \
./src/DummyFlow.o \
./src/Main.o \
./src/NetworkFlow.o \
./src/NetworkTrace.o \
./src/StochasticModelFit.o \
./src/TestClass.o 

CPP_DEPS += \
./src/DataProcessor.d \
./src/DatabaseInterface.d \
./src/DitgFlow.d \
./src/DummyFlow.d \
./src/Main.d \
./src/NetworkFlow.d \
./src/NetworkTrace.d \
./src/StochasticModelFit.d \
./src/TestClass.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O2 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


