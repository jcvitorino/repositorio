################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Arvore.o \
../NoArvore.o \
../main.o 

CPP_SRCS += \
../Arvore.cpp \
../NoArvore.cpp \
../main.cpp 

OBJS += \
./Arvore.o \
./NoArvore.o \
./main.o 

CPP_DEPS += \
./Arvore.d \
./NoArvore.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


