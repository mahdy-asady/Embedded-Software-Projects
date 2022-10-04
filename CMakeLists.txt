cmake_minimum_required(VERSION 3.20)

list(GET ${PROFILE} 0 PROCESSOR)
list(GET ${PROFILE} 1 F_CPU)
list(GET ${PROFILE} 2 MCU)
list(GET ${PROFILE} 3 FLASHER)

set(PROJECT_PATH "src/app/${PROJECT}")


set(CDEFS     "-DF_CPU=${F_CPU} -DBAUD=${BAUD} -D${PROCESSOR}")
set(CSTANDARD "-std=gnu99")
set(CWARN     "-Wall -Wstrict-prototypes -Wl,--gc-sections -Wl,--relax")

if( MCU STREQUAL "cortex-m3" )

    # Cmake test use nosys.spec for testing arm-none-eabi-gcc
    set(CMAKE_EXE_LINKER_FLAGS_INIT "-specs=nosys.specs -specs=nano.specs")

    set(PREFIX arm-none-eabi-)
    set(CDEBUG    "-Og -g")
    set(CTUNING   "-fno-builtin -ffunction-sections -fdata-sections")
    set(COPT      "-Os -lm")
    set(CMCU      "-mcpu=${MCU} -mthumb -DUSE_HAL_DRIVER")

elseif( MCU STREQUAL "m16" )

    set(PREFIX avr-)
    # Compiler flags
    set(CDEBUG    "-gstabs -g -ggdb")
    set(CTUNING   "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections")
    set(COPT      "-Os -lm -lprintf_flt")
    set(CMCU      "-mmcu=${PROCESSOR}")

else()
    message( FATAL_ERROR "MCU Not Specified Correctly")
endif()

set(CFLAGS   "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CWARN} ${CSTANDARD} ${CTUNING}")
set(CXXFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CTUNING}")

# program names
set(CPP   ${PREFIX}g++)
set(CC     ${PREFIX}gcc)
set(STRIP ${PREFIX}strip)
set(OBJCOPY  ${PREFIX}objcopy)
set(OBJDUMP  ${PREFIX}objdump)
set(SIZE  ${PREFIX}size)



# Sets the compiler
# Needs to come before the project function
set(CMAKE_SYSTEM_NAME  Generic)
set(CMAKE_CXX_COMPILER ${CPP})
set(CMAKE_C_COMPILER   ${CC})
set(CMAKE_ASM_COMPILER ${CC})

set(CMAKE_C_FLAGS   "${CFLAGS}")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")
set(CMAKE_ASM_FLAGS   "${CFLAGS}")

project(Embedded C ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

# Project setup
add_subdirectory(${PROJECT_PATH})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

target_include_directories(${PROJECT_NAME} PUBLIC "src/peripheral")
target_include_directories(${PROJECT_NAME} PUBLIC "src/shared")

if( MCU STREQUAL "cortex-m3" )

    target_link_options(${PROJECT_NAME} PRIVATE
        -T../../../../src/mcu/stm32/STM32F107VCTx_FLASH.ld
        -mcpu=cortex-m3
        -mthumb
        #-specs=nano.specs
        #-nostdlib
        -lc
        -lm
        -lc_nano
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
    )

    add_custom_target(binary   ALL     ${OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin && ${SIZE} --format=berkeley ${PROJECT_NAME}.elf DEPENDS ${PROJECT_NAME})
    
    if( FLASHER STREQUAL "j-link" )

        add_custom_target(flash JFlash -openprj../JFlash/${PROCESSOR}.jflash -open${PROJECT_NAME}.bin,0x8000000 -auto -startapp -exit DEPENDS binary)

    elseif( FLASHER STREQUAL "st-link" )

        add_custom_target(flash st-flash write ${PROJECT_NAME}.bin 0x8000000 && st-flash reset DEPENDS binary)

    endif()


    target_include_directories(${PROJECT_NAME} PUBLIC "src/mcu/stm32")
    target_include_directories(${PROJECT_NAME} PUBLIC "src/mcu/stm32/STM32F1xx_HAL_Driver/Inc")
    target_include_directories(${PROJECT_NAME} PUBLIC "src/mcu/stm32/STM32F1xx_HAL_Driver/Inc/Legacy")
    target_include_directories(${PROJECT_NAME} PUBLIC "src/mcu/stm32/CMSIS/Device/ST/STM32F1xx/Include")
    target_include_directories(${PROJECT_NAME} PUBLIC "src/mcu/stm32/CMSIS/Include")


elseif( MCU STREQUAL "m16" )

    # Compiling targets
    add_custom_target(strip ALL     ${STRIP} "${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
    add_custom_target(hex   ALL     ${OBJCOPY} -R .eeprom -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex" && ${SIZE} --format=berkeley ${PROJECT_NAME}.elf DEPENDS strip)
    add_custom_target(eeprom        ${OBJCOPY} -j .eeprom --change-section-lma .eeprom=0 -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.eeprom" DEPENDS strip)

    add_custom_target(flash ${FLASHER} -c usbasp -p ${MCU} -U flash:w:${PROJECT_NAME}.hex DEPENDS hex)

endif()


set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}.hex;${PROJECT_NAME}.eeprom;${PROJECT_NAME}.lst")
