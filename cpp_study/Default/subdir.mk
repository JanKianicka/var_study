################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Cepek_cpp_chapter1.o \
../Fraction.o \
../fractiontest.o \
../ftest.o 

CPP_SRCS += \
../Cepek_cpp_chapter1.cpp \
../cpp_hello_world.cpp 

CC_SRCS += \
../Fraction.cc \
../fractiontest.cc \
../ftest.cc 

OBJS += \
./Cepek_cpp_chapter1.o \
./Fraction.o \
./cpp_hello_world.o \
./fractiontest.o \
./ftest.o 

CC_DEPS += \
./Fraction.d \
./fractiontest.d \
./ftest.d 

CPP_DEPS += \
./Cepek_cpp_chapter1.d \
./cpp_hello_world.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/lib64/root/cint/cint/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/lib64/root/cint/cint/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


