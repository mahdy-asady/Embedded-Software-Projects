cmake_minimum_required(VERSION 3.20)

if( MCU STREQUAL "cortex-m3" )

    add_definitions(-DHAL_GPIO_MODULE_ENABLED)
    add_definitions(-DHAL_UART_MODULE_ENABLED)
    add_definitions(-DTIM_ENABLED)


    set(INC_FILES main.c
        ../../shared/CliInterface/SimpleInterface.c
        ../../shared/CommandInterpreter/CommandInterpreter.c
        ../../mcu/stm32/GPIOModule.c
        ../../mcu/stm32/TimerModule.c
        ../../mcu/stm32/GPIO.c
        ../../mcu/stm32/stm32f1xx_it.c
        ../../mcu/stm32/stm32f1xx_hal_msp.c
        ../../mcu/stm32/system_stm32f1xx.c
        ../../mcu/stm32/retarget.c
        ../../mcu/stm32/ErrorHandler.c
        ../../mcu/stm32/mcu.c
        ../../mcu/stm32/USART.c
        ../../mcu/stm32/TIMER.c

        ../../mcu/stm32/ErrorHandler.h
        ../../mcu/stm32/stm32f1xx_hal_conf.h
        ../../mcu/stm32/stm32f1xx_it.h

        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
        ../../mcu/stm32/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c

        ../../mcu/stm32/startup_stm32f107xc.s
    )

elseif( MCU STREQUAL "m16" )
    message(FATAL_ERROR "Program is not ready for ARM MicroController!")
#    set(INC_FILES main.c
#        ../../mcu/avr/GPIO.c
#        ../../mcu/avr/mcu.c
#    )

endif()

# Project setup
add_executable(${PROJECT_NAME} ${INC_FILES})