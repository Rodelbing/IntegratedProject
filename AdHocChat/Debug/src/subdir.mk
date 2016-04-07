################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/receiver.cpp \
../src/sender.cpp \
../src/server.cpp \
../src/thread.cpp 

OBJS += \
./src/receiver.o \
./src/sender.o \
./src/server.o \
./src/thread.o 

CPP_DEPS += \
./src/receiver.d \
./src/sender.d \
./src/server.d \
./src/thread.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


