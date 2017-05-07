################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/kits/common/drivers/efm8_retargetserial/retargetio.c \
/Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/kits/common/drivers/efm8_retargetserial/retargetserial.c 

OBJS += \
./lib/bsp/efm8_retargetserial/retargetio.OBJ \
./lib/bsp/efm8_retargetserial/retargetserial.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/bsp/efm8_retargetserial/retargetio.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/kits/common/drivers/efm8_retargetserial/retargetio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/bsp/efm8_retargetserial/retargetserial.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/kits/common/drivers/efm8_retargetserial/retargetserial.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/bsp/efm8_retargetserial/retargetserial.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/kits/common/drivers/efm8_retargetserial/retargetserial.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/REG51.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDIO.H


