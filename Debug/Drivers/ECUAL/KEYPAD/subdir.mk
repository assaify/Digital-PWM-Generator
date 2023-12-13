################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ECUAL/KEYPAD/KEYPAD.c \
../Drivers/ECUAL/KEYPAD/KEYPAD_cfg.c 

OBJS += \
./Drivers/ECUAL/KEYPAD/KEYPAD.o \
./Drivers/ECUAL/KEYPAD/KEYPAD_cfg.o 

C_DEPS += \
./Drivers/ECUAL/KEYPAD/KEYPAD.d \
./Drivers/ECUAL/KEYPAD/KEYPAD_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ECUAL/KEYPAD/%.o Drivers/ECUAL/KEYPAD/%.su Drivers/ECUAL/KEYPAD/%.cyclo: ../Drivers/ECUAL/KEYPAD/%.c Drivers/ECUAL/KEYPAD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ECUAL-2f-KEYPAD

clean-Drivers-2f-ECUAL-2f-KEYPAD:
	-$(RM) ./Drivers/ECUAL/KEYPAD/KEYPAD.cyclo ./Drivers/ECUAL/KEYPAD/KEYPAD.d ./Drivers/ECUAL/KEYPAD/KEYPAD.o ./Drivers/ECUAL/KEYPAD/KEYPAD.su ./Drivers/ECUAL/KEYPAD/KEYPAD_cfg.cyclo ./Drivers/ECUAL/KEYPAD/KEYPAD_cfg.d ./Drivers/ECUAL/KEYPAD/KEYPAD_cfg.o ./Drivers/ECUAL/KEYPAD/KEYPAD_cfg.su

.PHONY: clean-Drivers-2f-ECUAL-2f-KEYPAD

