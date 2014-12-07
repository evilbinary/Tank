################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/agent.cpp \
../src/bullet.cpp \
../src/config.cpp \
../src/effect.cpp \
../src/game.cpp \
../src/main.cpp \
../src/map.cpp \
../src/object.cpp \
../src/phys.cpp \
../src/resource.cpp \
../src/tank.cpp \
../src/warfield.cpp 

OBJS += \
./src/agent.o \
./src/bullet.o \
./src/config.o \
./src/effect.o \
./src/game.o \
./src/main.o \
./src/map.o \
./src/object.o \
./src/phys.o \
./src/resource.o \
./src/tank.o \
./src/warfield.o 

CPP_DEPS += \
./src/agent.d \
./src/bullet.d \
./src/config.d \
./src/effect.d \
./src/game.d \
./src/main.d \
./src/map.d \
./src/object.d \
./src/phys.d \
./src/resource.d \
./src/tank.d \
./src/warfield.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


