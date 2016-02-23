# Copyright 2009 Uwe Hermann <uwe@hermann-uwe.de>
# Copyright 2010 Piotr Esden-Tempski <piotr@esden.net>
# Copyright 2012 Michael Ossmann <mike@ossmann.com>
# Copyright 2012 Benjamin Vernoux <titanmkd@gmail.com>
# Copyright 2012 Jared Boone <jared@sharebrained.com>
#
# This file is part of HackRF.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

# derived primarily from Makefiles in libopencm3

enable_language(C CXX ASM)

include(../dfu-util.cmake)

SET(PATH_HACKRF ../..)
SET(PATH_HACKRF_FIRMWARE ${PATH_HACKRF}/firmware)
SET(PATH_HACKRF_FIRMWARE_COMMON ${PATH_HACKRF_FIRMWARE}/common)
SET(LIBOPENCM3 ${PATH_HACKRF_FIRMWARE}/libopencm3)

execute_process(
	COMMAND git log -n 1 --format=%h
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	RESULT_VARIABLE GIT_VERSION_FOUND
	ERROR_QUIET
	OUTPUT_VARIABLE GIT_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
if (GIT_VERSION_FOUND)
	set(VERSION "unknown")
else (GIT_VERSION_FOUND)
	set(VERSION ${GIT_VERSION})
endif (GIT_VERSION_FOUND)

if(NOT DEFINED BOARD)
	set(BOARD HACKRF_ONE)
endif()

if(NOT DEFINED RUN_FROM)
	set(RUN_FROM SPIFI)
endif()

if(BOARD STREQUAL "HACKRF_ONE")
	set(MCU_PARTNO LPC4320)
else()
	set(MCU_PARTNO LPC4330)
endif()

if(NOT DEFINED SRC_M0)
	set(SRC_M0 "${PATH_HACKRF_FIRMWARE_COMMON}/m0_sleep.c")
endif()

SET(HACKRF_OPTS "-D${BOARD} -DLPC43XX -D${MCU_PARTNO} -DTX_ENABLE -D'VERSION_STRING=\"git-${VERSION}\"' -DRUN_FROM=${RUN_FROM}")

SET(LDSCRIPT_M4 "-T${PATH_HACKRF_FIRMWARE_COMMON}/${MCU_PARTNO}_M4_memory.ld")
if( RUN_FROM STREQUAL "RAM")
	SET(LDSCRIPT_M4 "${LDSCRIPT_M4} -Tlibopencm3_lpc43xx.ld")
else()
	SET(LDSCRIPT_M4 "${LDSCRIPT_M4} -Tlibopencm3_lpc43xx_rom_to_ram.ld")
endif()
SET(LDSCRIPT_M4 "${LDSCRIPT_M4} -T${PATH_HACKRF_FIRMWARE_COMMON}/LPC43xx_M4_M0_image_from_text.ld")

SET(LDSCRIPT_M0 "-T${PATH_HACKRF_FIRMWARE_COMMON}/LPC43xx_M0_memory.ld -Tlibopencm3_lpc43xx_m0.ld")

SET(CFLAGS_COMMON "-Os -g3 -Wall -Wextra ${HACKRF_OPTS} ${COMMON_FLAGS} -fno-common -MD")
SET(LDFLAGS_COMMON "-nostartfiles -Wl,--gc-sections")

if(V STREQUAL "1")
	SET(LDFLAGS_COMMON "${LDFLAGS_COMMON} -Wl,--print-gc-sections")
endif()

SET(CPUFLAGS_M0 "-mthumb -mcpu=cortex-m0 -mfloat-abi=soft")
SET(CFLAGS_M0 "-std=gnu99 ${CFLAGS_COMMON} ${CPUFLAGS_M0} -DLPC43XX_M0")
SET(CXXFLAGS_M0 "-std=gnu++0x ${CFLAGS_COMMON} ${CPUFLAGS_M0} -DLPC43XX_M0")
SET(LDFLAGS_M0 "${LDFLAGS_COMMON} ${CPUFLAGS_M0} ${LDSCRIPT_M0} -Xlinker -Map=m0.map --specs=nano.specs")

SET(CPUFLAGS_M4 "-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")
SET(CFLAGS_M4 "-std=gnu99 ${CFLAGS_COMMON} ${CPUFLAGS_M4} -DLPC43XX_M4")
SET(CXXFLAGS_M4 "-std=gnu++0x ${CFLAGS_COMMON} ${CPUFLAGS_M4} -DLPC43XX_M4")
SET(LDFLAGS_M4 "${LDFLAGS_COMMON} ${CPUFLAGS_M4} ${LDSCRIPT_M4} -Xlinker -Map=m4.map")

set(BUILD_SHARED_LIBS OFF)

include_directories("${LIBOPENCM3}/include/")
include_directories("${PATH_HACKRF_FIRMWARE_COMMON}")

macro(DeclareTargets)
	configure_file(
		${PATH_HACKRF_FIRMWARE_COMMON}/m0_bin.s.cmake
		m0_bin.s
	)

	link_directories(
		"${PATH_HACKRF_FIRMWARE_COMMON}"
		"${LIBOPENCM3}/lib"
		"${LIBOPENCM3}/lib/lpc43xx"
		"${CMAKE_INSTALL_PREFIX}/lib/armv7e-m/fpu"
	)

	add_executable(${PROJECT_NAME}_m0.elf ${SRC_M0})

	target_link_libraries(
		${PROJECT_NAME}_m0.elf
		c
		nosys
		opencm3_lpc43xx_m0
	)

	set_target_properties(${PROJECT_NAME}_m0.elf PROPERTIES COMPILE_FLAGS "${CFLAGS_M0}")
	set_target_properties(${PROJECT_NAME}_m0.elf PROPERTIES LINK_FLAGS "${LDFLAGS_M0}")

	add_custom_target(
		${PROJECT_NAME}_m0.bin
		DEPENDS ${PROJECT_NAME}_m0.elf
		COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}_m0.elf ${PROJECT_NAME}_m0.bin
	)

	add_executable(${PROJECT_NAME}.elf
		${SRC_M4}
		${PATH_HACKRF_FIRMWARE_COMMON}/hackrf_core.c
		${PATH_HACKRF_FIRMWARE_COMMON}/sgpio.c
		${PATH_HACKRF_FIRMWARE_COMMON}/rf_path.c
		${PATH_HACKRF_FIRMWARE_COMMON}/si5351c.c
		${PATH_HACKRF_FIRMWARE_COMMON}/max2837.c
		${PATH_HACKRF_FIRMWARE_COMMON}/max2837_target.c
		${PATH_HACKRF_FIRMWARE_COMMON}/max5864.c
		${PATH_HACKRF_FIRMWARE_COMMON}/max5864_target.c
		${PATH_HACKRF_FIRMWARE_COMMON}/rffc5071.c
		${PATH_HACKRF_FIRMWARE_COMMON}/i2c_bus.c
		${PATH_HACKRF_FIRMWARE_COMMON}/i2c_lpc.c
		${PATH_HACKRF_FIRMWARE_COMMON}/rffc5071_spi.c
		${PATH_HACKRF_FIRMWARE_COMMON}/w25q80bv.c
		${PATH_HACKRF_FIRMWARE_COMMON}/w25q80bv_target.c
		${PATH_HACKRF_FIRMWARE_COMMON}/spi_bus.c
		${PATH_HACKRF_FIRMWARE_COMMON}/spi_ssp.c
		${PATH_HACKRF_FIRMWARE_COMMON}/gpio_lpc.c
		m0_bin.s
	)

	add_dependencies(${PROJECT_NAME}.elf ${PROJECT_NAME}_m0.bin)

	target_link_libraries(
		${PROJECT_NAME}.elf
		c
		nosys
		opencm3_lpc43xx
		m
	)

	set_target_properties(${PROJECT_NAME}.elf PROPERTIES COMPILE_FLAGS "${CFLAGS_M4}")
	set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_FLAGS "${LDFLAGS_M4}")

	add_custom_target(
		${PROJECT_NAME}.bin
		DEPENDS ${PROJECT_NAME}.elf
		COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
	)

	add_custom_target(
		${PROJECT_NAME}.dfu ${DFU_ALL}
		DEPENDS ${PROJECT_NAME}.bin
		COMMAND rm -f _tmp.dfu _header.bin
		COMMAND cp ${PROJECT_NAME}.bin _tmp.dfu
		COMMAND ${DFU_COMMAND}
		COMMAND python -c \"import os.path\; import struct\; print\('0000000: da ff ' + ' '.join\(map\(lambda s: '%02x' % ord\(s\), struct.pack\('<H', os.path.getsize\('${PROJECT_NAME}.bin'\) / 512 + 1\)\)\) + ' ff ff ff ff'\)\" | xxd -g1 -r > _header.bin
		COMMAND cat _header.bin _tmp.dfu >${PROJECT_NAME}.dfu
		COMMAND rm -f _tmp.dfu _header.bin
	)

	add_custom_target(
		${PROJECT_NAME}-program
		DEPENDS ${PROJECT_NAME}.dfu
		COMMAND dfu-util --device 1fc9:000c --alt 0 --download ${PROJECT_NAME}.dfu
	)
endmacro()
