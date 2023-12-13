################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ECUAL/LM35/LM35.c \
../Drivers/ECUAL/LM35/LM35_cfg.c 

OBJS += \
./Drivers/ECUAL/LM35/LM35.o \
./Drivers/ECUAL/LM35/LM35_cfg.o 

C_DEPS += \
./Drivers/ECUAL/LM35/LM35.d \
./Drivers/ECUAL/LM35/LM35_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ECUAL/LM35/%.o Drivers/ECUAL/LM35/%.su Drivers/ECUAL/LM35/%.cyclo: ../Drivers/ECUAL/LM35/%.c Drivers/ECUAL/LM35/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ECUAL-2f-LM35

clean-Drivers-2f-ECUAL-2f-LM35:
	-$(RM) ./Drivers/ECUAL/LM35/LM35.cyclo ./Drivers/ECUAL/LM35/LM35.d ./Drivers/ECUAL/LM35/LM35.o ./Drivers/ECUAL/LM35/LM35.su ./Drivers/ECUAL/LM35/LM35_cfg.cyclo ./Drivers/ECUAL/LM35/LM35_cfg.d ./Drivers/ECUAL/LM35/LM35_cfg.o ./Drivers/ECUAL/LM35/LM35_cfg.su

.PHONY: clean-Drivers-2f-ECUAL-2f-LM35

