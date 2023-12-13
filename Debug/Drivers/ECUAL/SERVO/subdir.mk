################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ECUAL/SERVO/SERVO.c \
../Drivers/ECUAL/SERVO/SERVO_cfg.c 

OBJS += \
./Drivers/ECUAL/SERVO/SERVO.o \
./Drivers/ECUAL/SERVO/SERVO_cfg.o 

C_DEPS += \
./Drivers/ECUAL/SERVO/SERVO.d \
./Drivers/ECUAL/SERVO/SERVO_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ECUAL/SERVO/%.o Drivers/ECUAL/SERVO/%.su Drivers/ECUAL/SERVO/%.cyclo: ../Drivers/ECUAL/SERVO/%.c Drivers/ECUAL/SERVO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ECUAL-2f-SERVO

clean-Drivers-2f-ECUAL-2f-SERVO:
	-$(RM) ./Drivers/ECUAL/SERVO/SERVO.cyclo ./Drivers/ECUAL/SERVO/SERVO.d ./Drivers/ECUAL/SERVO/SERVO.o ./Drivers/ECUAL/SERVO/SERVO.su ./Drivers/ECUAL/SERVO/SERVO_cfg.cyclo ./Drivers/ECUAL/SERVO/SERVO_cfg.d ./Drivers/ECUAL/SERVO/SERVO_cfg.o ./Drivers/ECUAL/SERVO/SERVO_cfg.su

.PHONY: clean-Drivers-2f-ECUAL-2f-SERVO

