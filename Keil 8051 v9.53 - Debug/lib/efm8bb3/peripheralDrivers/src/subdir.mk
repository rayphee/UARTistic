################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/Device/EFM8BB3/peripheral_driver/src/spi_0.c 

OBJS += \
./lib/efm8bb3/peripheralDrivers/src/spi_0.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/efm8bb3/peripheralDrivers/src/spi_0.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/Device/EFM8BB3/peripheral_driver/src/spi_0.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/efm8bb3/peripheralDrivers/src/spi_0.OBJ: /Users/rafi/SimplicityStudio/v4_workspace/UARTisticFucK/inc/config/efm8_config.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/Device/EFM8BB3/inc/SI_EFM8BB3_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/Device/EFM8BB3/peripheral_driver/inc/spi_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/Device/EFM8BB3/inc/SI_EFM8BB3_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/si_toolchain.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/stdbool.h


