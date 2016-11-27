################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/DitgFlow.cpp \
../src/data/DummyFlow.cpp 

OBJS += \
./src/data/DitgFlow.o \
./src/data/DummyFlow.o 

CPP_DEPS += \
./src/data/DitgFlow.d \
./src/data/DummyFlow.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/%.o: ../src/data/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"/home/ldapusers/apaschoalon/ProjetoMestrado/Components/D-ITG-2.8.1-r1023//src/libITG" -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


