################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Sendtest.cpp \
../src/main.cpp \
../src/receiver.cpp \
../src/sender.cpp \
../src/sendroutes.cpp \
../src/server.cpp \
../src/thread.cpp 

OBJS += \
./src/Sendtest.o \
./src/main.o \
./src/receiver.o \
./src/sender.o \
./src/sendroutes.o \
./src/server.o \
./src/thread.o 

CPP_DEPS += \
./src/Sendtest.d \
./src/main.d \
./src/receiver.d \
./src/sender.d \
./src/sendroutes.d \
./src/server.d \
./src/thread.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x thread.cpp receiver.cpp sender.cpp -lpthread -o udp_test -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


