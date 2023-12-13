################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ECUAL/HCSR04/HCSR04.c \
../Drivers/ECUAL/HCSR04/HCSR04_cfg.c 

OBJS += \
./Drivers/ECUAL/HCSR04/HCSR04.o \
./Drivers/ECUAL/HCSR04/HCSR04_cfg.o 

C_DEPS += \
./Drivers/ECUAL/HCSR04/HCSR04.d \
./Drivers/ECUAL/HCSR04/HCSR04_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ECUAL/HCSR04/%.o Drivers/ECUAL/HCSR04/%.su Drivers/ECUAL/HCSR04/%.cyclo: ../Drivers/ECUAL/HCSR04/%.c Drivers/ECUAL/HCSR04/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ECUAL-2f-HCSR04

clean-Drivers-2f-ECUAL-2f-HCSR04:
	-$(RM) ./Drivers/ECUAL/HCSR04/HCSR04.cyclo ./Drivers/ECUAL/HCSR04/HCSR04.d ./Drivers/ECUAL/HCSR04/HCSR04.o ./Drivers/ECUAL/HCSR04/HCSR04.su ./Drivers/ECUAL/HCSR04/HCSR04_cfg.cyclo ./Drivers/ECUAL/HCSR04/HCSR04_cfg.d ./Drivers/ECUAL/HCSR04/HCSR04_cfg.o ./Drivers/ECUAL/HCSR04/HCSR04_cfg.su

.PHONY: clean-Drivers-2f-ECUAL-2f-HCSR04

