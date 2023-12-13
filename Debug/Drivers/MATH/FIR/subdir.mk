################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MATH/FIR/FIR.c 

OBJS += \
./Drivers/MATH/FIR/FIR.o 

C_DEPS += \
./Drivers/MATH/FIR/FIR.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MATH/FIR/%.o Drivers/MATH/FIR/%.su Drivers/MATH/FIR/%.cyclo: ../Drivers/MATH/FIR/%.c Drivers/MATH/FIR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-MATH-2f-FIR

clean-Drivers-2f-MATH-2f-FIR:
	-$(RM) ./Drivers/MATH/FIR/FIR.cyclo ./Drivers/MATH/FIR/FIR.d ./Drivers/MATH/FIR/FIR.o ./Drivers/MATH/FIR/FIR.su

.PHONY: clean-Drivers-2f-MATH-2f-FIR

