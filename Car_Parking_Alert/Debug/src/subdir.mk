################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Car_Parking_System.c \
../src/buzzer.c \
../src/gpio.c \
../src/icu.c \
../src/lcd.c \
../src/led.c \
../src/ultra_sonic_sensor.c 

OBJS += \
./src/Car_Parking_System.o \
./src/buzzer.o \
./src/gpio.o \
./src/icu.o \
./src/lcd.o \
./src/led.o \
./src/ultra_sonic_sensor.o 

C_DEPS += \
./src/Car_Parking_System.d \
./src/buzzer.d \
./src/gpio.d \
./src/icu.d \
./src/lcd.d \
./src/led.d \
./src/ultra_sonic_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


