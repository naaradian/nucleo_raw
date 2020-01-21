################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Storage.c \
../Src/adc.c \
../Src/cgi_handlers.c \
../Src/dma.c \
../Src/ethernetif.c \
../Src/flash_if.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/httpd_post.c \
../Src/lwip.c \
../Src/main.c \
../Src/mb.c \
../Src/mbascii.c \
../Src/mbcrc.c \
../Src/mbfunccoils.c \
../Src/mbfuncdiag.c \
../Src/mbfuncdisc.c \
../Src/mbfuncholding.c \
../Src/mbfuncinput.c \
../Src/mbfuncother.c \
../Src/mbrtu.c \
../Src/mbtcp.c \
../Src/mbutils.c \
../Src/multipart_parser.c \
../Src/portevent.c \
../Src/portother.c \
../Src/porttcp.c \
../Src/remote.c \
../Src/rtc.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c \
../Src/tftpserver.c \
../Src/tim.c \
../Src/usart.c \
../Src/usb_device.c \
../Src/usbd_cdc_if.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c \
../Src/wwdg.c 

OBJS += \
./Src/Storage.o \
./Src/adc.o \
./Src/cgi_handlers.o \
./Src/dma.o \
./Src/ethernetif.o \
./Src/flash_if.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/httpd_post.o \
./Src/lwip.o \
./Src/main.o \
./Src/mb.o \
./Src/mbascii.o \
./Src/mbcrc.o \
./Src/mbfunccoils.o \
./Src/mbfuncdiag.o \
./Src/mbfuncdisc.o \
./Src/mbfuncholding.o \
./Src/mbfuncinput.o \
./Src/mbfuncother.o \
./Src/mbrtu.o \
./Src/mbtcp.o \
./Src/mbutils.o \
./Src/multipart_parser.o \
./Src/portevent.o \
./Src/portother.o \
./Src/porttcp.o \
./Src/remote.o \
./Src/rtc.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o \
./Src/tftpserver.o \
./Src/tim.o \
./Src/usart.o \
./Src/usb_device.o \
./Src/usbd_cdc_if.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o \
./Src/wwdg.o 

C_DEPS += \
./Src/Storage.d \
./Src/adc.d \
./Src/cgi_handlers.d \
./Src/dma.d \
./Src/ethernetif.d \
./Src/flash_if.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/httpd_post.d \
./Src/lwip.d \
./Src/main.d \
./Src/mb.d \
./Src/mbascii.d \
./Src/mbcrc.d \
./Src/mbfunccoils.d \
./Src/mbfuncdiag.d \
./Src/mbfuncdisc.d \
./Src/mbfuncholding.d \
./Src/mbfuncinput.d \
./Src/mbfuncother.d \
./Src/mbrtu.d \
./Src/mbtcp.d \
./Src/mbutils.d \
./Src/multipart_parser.d \
./Src/portevent.d \
./Src/portother.d \
./Src/porttcp.d \
./Src/remote.d \
./Src/rtc.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d \
./Src/tftpserver.d \
./Src/tim.d \
./Src/usart.d \
./Src/usb_device.d \
./Src/usbd_cdc_if.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d \
./Src/wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D_TIMEVAL_DEFINED -D_SYS_TIME_H_ '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F429xx -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Inc" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/system" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/apps/httpd" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include/lwip" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include/netif" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include/posix" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Middlewares/Third_Party/LwIP/system/arch" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Drivers/CMSIS/Include" -I"D:/Users/user/keil/stm32cubemx/three_discav/mb6_raw/Drivers/modbus/include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


