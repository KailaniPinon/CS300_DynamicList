################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/pqueue.c \
../src/pqueuedriver.c 

OBJS += \
./src/pqueue.o \
./src/pqueuedriver.o 

C_DEPS += \
./src/pqueue.d \
./src/pqueuedriver.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/pino3567/CS300_fall2020_assignments/CS300_DynamicList/GenericDynamicList/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


