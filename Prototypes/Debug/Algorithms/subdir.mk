################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Algorithms/Prototypes.cpp 

OBJS += \
./Algorithms/Prototypes.o 

CPP_DEPS += \
./Algorithms/Prototypes.d 


# Each subdirectory must supply rules for building sources it contributes
Algorithms/%.o: ../Algorithms/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


