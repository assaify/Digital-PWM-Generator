################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ECUAL/LCD16x2/LCD16x2.c \
../Drivers/ECUAL/LCD16x2/LCD16x2_cfg.c 

OBJS += \
./Drivers/ECUAL/LCD16x2/LCD16x2.o \
./Drivers/ECUAL/LCD16x2/LCD16x2_cfg.o 

C_DEPS += \
./Drivers/ECUAL/LCD16x2/LCD16x2.d \
./Drivers/ECUAL/LCD16x2/LCD16x2_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ECUAL/LCD16x2/%.o Drivers/ECUAL/LCD16x2/%.su Drivers/ECUAL/LCD16x2/%.cyclo: ../Drivers/ECUAL/LCD16x2/%.c Drivers/ECUAL/LCD16x2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ECUAL-2f-LCD16x2

clean-Drivers-2f-ECUAL-2f-LCD16x2:
	-$(RM) ./Drivers/ECUAL/LCD16x2/LCD16x2.cyclo ./Drivers/ECUAL/LCD16x2/LCD16x2.d ./Drivers/ECUAL/LCD16x2/LCD16x2.o ./Drivers/ECUAL/LCD16x2/LCD16x2.su ./Drivers/ECUAL/LCD16x2/LCD16x2_cfg.cyclo ./Drivers/ECUAL/LCD16x2/LCD16x2_cfg.d ./Drivers/ECUAL/LCD16x2/LCD16x2_cfg.o ./Drivers/ECUAL/LCD16x2/LCD16x2_cfg.su

.PHONY: clean-Drivers-2f-ECUAL-2f-LCD16x2

