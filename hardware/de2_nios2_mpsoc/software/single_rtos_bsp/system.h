/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu_0' in SOPC Builder design 'nios2_mpsoc'
 * SOPC Builder design path: ../../nios2_mpsoc.sopcinfo
 *
 * Generated: Thu Feb 14 15:52:59 UTC 2019
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * Buttons configuration
 *
 */

#define ALT_MODULE_CLASS_Buttons altera_up_avalon_parallel_port
#define BUTTONS_BASE 0x105140
#define BUTTONS_IRQ 4
#define BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BUTTONS_NAME "/dev/Buttons"
#define BUTTONS_SPAN 16
#define BUTTONS_TYPE "altera_up_avalon_parallel_port"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x104820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x19
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x80020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x19
#define ALT_CPU_NAME "cpu_0"
#define ALT_CPU_RESET_ADDR 0x80000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x104820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x19
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x80020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x19
#define NIOS2_RESET_ADDR 0x80000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_FIFO
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_MUTEX
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PERFORMANCE_COUNTER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS
#define __ALTERA_UP_AVALON_PARALLEL_PORT
#define __ALTERA_UP_AVALON_SRAM


/*
 * HEX3_HEX0 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX3_HEX0 altera_up_avalon_parallel_port
#define HEX3_HEX0_BASE 0x105160
#define HEX3_HEX0_IRQ -1
#define HEX3_HEX0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX3_HEX0_NAME "/dev/HEX3_HEX0"
#define HEX3_HEX0_SPAN 16
#define HEX3_HEX0_TYPE "altera_up_avalon_parallel_port"


/*
 * HEX7_HEX4 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX7_HEX4 altera_up_avalon_parallel_port
#define HEX7_HEX4_BASE 0x105150
#define HEX7_HEX4_IRQ -1
#define HEX7_HEX4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX7_HEX4_NAME "/dev/HEX7_HEX4"
#define HEX7_HEX4_SPAN 16
#define HEX7_HEX4_TYPE "altera_up_avalon_parallel_port"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone II"
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x1051d0
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x1051d0
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x1051d0
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "nios2_mpsoc"


/*
 * fifo_0_in configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_0_in altera_avalon_fifo
#define FIFO_0_IN_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_0_IN_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_0_IN_BASE 0x1051e4
#define FIFO_0_IN_BITS_PER_SYMBOL 16
#define FIFO_0_IN_CHANNEL_WIDTH 8
#define FIFO_0_IN_ERROR_WIDTH 8
#define FIFO_0_IN_FIFO_DEPTH 16
#define FIFO_0_IN_IRQ -1
#define FIFO_0_IN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FIFO_0_IN_NAME "/dev/fifo_0_in"
#define FIFO_0_IN_SINGLE_CLOCK_MODE 0
#define FIFO_0_IN_SPAN 4
#define FIFO_0_IN_SYMBOLS_PER_BEAT 2
#define FIFO_0_IN_TYPE "altera_avalon_fifo"
#define FIFO_0_IN_USE_AVALONMM_READ_SLAVE 1
#define FIFO_0_IN_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_0_IN_USE_AVALONST_SINK 0
#define FIFO_0_IN_USE_AVALONST_SOURCE 0
#define FIFO_0_IN_USE_BACKPRESSURE 1
#define FIFO_0_IN_USE_IRQ 1
#define FIFO_0_IN_USE_PACKET 1
#define FIFO_0_IN_USE_READ_CONTROL 1
#define FIFO_0_IN_USE_REGISTER 0
#define FIFO_0_IN_USE_WRITE_CONTROL 1


/*
 * fifo_0_in_csr configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_0_in_csr altera_avalon_fifo
#define FIFO_0_IN_CSR_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_0_IN_CSR_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_0_IN_CSR_BASE 0x1050c0
#define FIFO_0_IN_CSR_BITS_PER_SYMBOL 16
#define FIFO_0_IN_CSR_CHANNEL_WIDTH 8
#define FIFO_0_IN_CSR_ERROR_WIDTH 8
#define FIFO_0_IN_CSR_FIFO_DEPTH 16
#define FIFO_0_IN_CSR_IRQ 16
#define FIFO_0_IN_CSR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define FIFO_0_IN_CSR_NAME "/dev/fifo_0_in_csr"
#define FIFO_0_IN_CSR_SINGLE_CLOCK_MODE 0
#define FIFO_0_IN_CSR_SPAN 32
#define FIFO_0_IN_CSR_SYMBOLS_PER_BEAT 2
#define FIFO_0_IN_CSR_TYPE "altera_avalon_fifo"
#define FIFO_0_IN_CSR_USE_AVALONMM_READ_SLAVE 1
#define FIFO_0_IN_CSR_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_0_IN_CSR_USE_AVALONST_SINK 0
#define FIFO_0_IN_CSR_USE_AVALONST_SOURCE 0
#define FIFO_0_IN_CSR_USE_BACKPRESSURE 1
#define FIFO_0_IN_CSR_USE_IRQ 1
#define FIFO_0_IN_CSR_USE_PACKET 1
#define FIFO_0_IN_CSR_USE_READ_CONTROL 1
#define FIFO_0_IN_CSR_USE_REGISTER 0
#define FIFO_0_IN_CSR_USE_WRITE_CONTROL 1


/*
 * fifo_0_out configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_0_out altera_avalon_fifo
#define FIFO_0_OUT_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_0_OUT_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_0_OUT_BASE 0x1051e0
#define FIFO_0_OUT_BITS_PER_SYMBOL 16
#define FIFO_0_OUT_CHANNEL_WIDTH 8
#define FIFO_0_OUT_ERROR_WIDTH 8
#define FIFO_0_OUT_FIFO_DEPTH 16
#define FIFO_0_OUT_IRQ -1
#define FIFO_0_OUT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FIFO_0_OUT_NAME "/dev/fifo_0_out"
#define FIFO_0_OUT_SINGLE_CLOCK_MODE 0
#define FIFO_0_OUT_SPAN 4
#define FIFO_0_OUT_SYMBOLS_PER_BEAT 2
#define FIFO_0_OUT_TYPE "altera_avalon_fifo"
#define FIFO_0_OUT_USE_AVALONMM_READ_SLAVE 1
#define FIFO_0_OUT_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_0_OUT_USE_AVALONST_SINK 0
#define FIFO_0_OUT_USE_AVALONST_SOURCE 0
#define FIFO_0_OUT_USE_BACKPRESSURE 1
#define FIFO_0_OUT_USE_IRQ 1
#define FIFO_0_OUT_USE_PACKET 1
#define FIFO_0_OUT_USE_READ_CONTROL 1
#define FIFO_0_OUT_USE_REGISTER 0
#define FIFO_0_OUT_USE_WRITE_CONTROL 1


/*
 * fifo_0_out_csr configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_0_out_csr altera_avalon_fifo
#define FIFO_0_OUT_CSR_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_0_OUT_CSR_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_0_OUT_CSR_BASE 0x1050e0
#define FIFO_0_OUT_CSR_BITS_PER_SYMBOL 16
#define FIFO_0_OUT_CSR_CHANNEL_WIDTH 8
#define FIFO_0_OUT_CSR_ERROR_WIDTH 8
#define FIFO_0_OUT_CSR_FIFO_DEPTH 16
#define FIFO_0_OUT_CSR_IRQ 15
#define FIFO_0_OUT_CSR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define FIFO_0_OUT_CSR_NAME "/dev/fifo_0_out_csr"
#define FIFO_0_OUT_CSR_SINGLE_CLOCK_MODE 0
#define FIFO_0_OUT_CSR_SPAN 32
#define FIFO_0_OUT_CSR_SYMBOLS_PER_BEAT 2
#define FIFO_0_OUT_CSR_TYPE "altera_avalon_fifo"
#define FIFO_0_OUT_CSR_USE_AVALONMM_READ_SLAVE 1
#define FIFO_0_OUT_CSR_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_0_OUT_CSR_USE_AVALONST_SINK 0
#define FIFO_0_OUT_CSR_USE_AVALONST_SOURCE 0
#define FIFO_0_OUT_CSR_USE_BACKPRESSURE 1
#define FIFO_0_OUT_CSR_USE_IRQ 1
#define FIFO_0_OUT_CSR_USE_PACKET 1
#define FIFO_0_OUT_CSR_USE_READ_CONTROL 1
#define FIFO_0_OUT_CSR_USE_REGISTER 0
#define FIFO_0_OUT_CSR_USE_WRITE_CONTROL 1


/*
 * fifo_1_in configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_1_in altera_avalon_fifo
#define FIFO_1_IN_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_1_IN_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_1_IN_BASE 0x1051dc
#define FIFO_1_IN_BITS_PER_SYMBOL 16
#define FIFO_1_IN_CHANNEL_WIDTH 8
#define FIFO_1_IN_ERROR_WIDTH 8
#define FIFO_1_IN_FIFO_DEPTH 16
#define FIFO_1_IN_IRQ -1
#define FIFO_1_IN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FIFO_1_IN_NAME "/dev/fifo_1_in"
#define FIFO_1_IN_SINGLE_CLOCK_MODE 0
#define FIFO_1_IN_SPAN 4
#define FIFO_1_IN_SYMBOLS_PER_BEAT 2
#define FIFO_1_IN_TYPE "altera_avalon_fifo"
#define FIFO_1_IN_USE_AVALONMM_READ_SLAVE 1
#define FIFO_1_IN_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_1_IN_USE_AVALONST_SINK 0
#define FIFO_1_IN_USE_AVALONST_SOURCE 0
#define FIFO_1_IN_USE_BACKPRESSURE 1
#define FIFO_1_IN_USE_IRQ 1
#define FIFO_1_IN_USE_PACKET 1
#define FIFO_1_IN_USE_READ_CONTROL 1
#define FIFO_1_IN_USE_REGISTER 0
#define FIFO_1_IN_USE_WRITE_CONTROL 1


/*
 * fifo_1_in_csr configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_1_in_csr altera_avalon_fifo
#define FIFO_1_IN_CSR_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_1_IN_CSR_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_1_IN_CSR_BASE 0x105080
#define FIFO_1_IN_CSR_BITS_PER_SYMBOL 16
#define FIFO_1_IN_CSR_CHANNEL_WIDTH 8
#define FIFO_1_IN_CSR_ERROR_WIDTH 8
#define FIFO_1_IN_CSR_FIFO_DEPTH 16
#define FIFO_1_IN_CSR_IRQ 18
#define FIFO_1_IN_CSR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define FIFO_1_IN_CSR_NAME "/dev/fifo_1_in_csr"
#define FIFO_1_IN_CSR_SINGLE_CLOCK_MODE 0
#define FIFO_1_IN_CSR_SPAN 32
#define FIFO_1_IN_CSR_SYMBOLS_PER_BEAT 2
#define FIFO_1_IN_CSR_TYPE "altera_avalon_fifo"
#define FIFO_1_IN_CSR_USE_AVALONMM_READ_SLAVE 1
#define FIFO_1_IN_CSR_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_1_IN_CSR_USE_AVALONST_SINK 0
#define FIFO_1_IN_CSR_USE_AVALONST_SOURCE 0
#define FIFO_1_IN_CSR_USE_BACKPRESSURE 1
#define FIFO_1_IN_CSR_USE_IRQ 1
#define FIFO_1_IN_CSR_USE_PACKET 1
#define FIFO_1_IN_CSR_USE_READ_CONTROL 1
#define FIFO_1_IN_CSR_USE_REGISTER 0
#define FIFO_1_IN_CSR_USE_WRITE_CONTROL 1


/*
 * fifo_1_out configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_1_out altera_avalon_fifo
#define FIFO_1_OUT_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_1_OUT_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_1_OUT_BASE 0x1051d8
#define FIFO_1_OUT_BITS_PER_SYMBOL 16
#define FIFO_1_OUT_CHANNEL_WIDTH 8
#define FIFO_1_OUT_ERROR_WIDTH 8
#define FIFO_1_OUT_FIFO_DEPTH 16
#define FIFO_1_OUT_IRQ -1
#define FIFO_1_OUT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FIFO_1_OUT_NAME "/dev/fifo_1_out"
#define FIFO_1_OUT_SINGLE_CLOCK_MODE 0
#define FIFO_1_OUT_SPAN 4
#define FIFO_1_OUT_SYMBOLS_PER_BEAT 2
#define FIFO_1_OUT_TYPE "altera_avalon_fifo"
#define FIFO_1_OUT_USE_AVALONMM_READ_SLAVE 1
#define FIFO_1_OUT_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_1_OUT_USE_AVALONST_SINK 0
#define FIFO_1_OUT_USE_AVALONST_SOURCE 0
#define FIFO_1_OUT_USE_BACKPRESSURE 1
#define FIFO_1_OUT_USE_IRQ 1
#define FIFO_1_OUT_USE_PACKET 1
#define FIFO_1_OUT_USE_READ_CONTROL 1
#define FIFO_1_OUT_USE_REGISTER 0
#define FIFO_1_OUT_USE_WRITE_CONTROL 1


/*
 * fifo_1_out_csr configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_1_out_csr altera_avalon_fifo
#define FIFO_1_OUT_CSR_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_1_OUT_CSR_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_1_OUT_CSR_BASE 0x1050a0
#define FIFO_1_OUT_CSR_BITS_PER_SYMBOL 16
#define FIFO_1_OUT_CSR_CHANNEL_WIDTH 8
#define FIFO_1_OUT_CSR_ERROR_WIDTH 8
#define FIFO_1_OUT_CSR_FIFO_DEPTH 16
#define FIFO_1_OUT_CSR_IRQ 17
#define FIFO_1_OUT_CSR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define FIFO_1_OUT_CSR_NAME "/dev/fifo_1_out_csr"
#define FIFO_1_OUT_CSR_SINGLE_CLOCK_MODE 0
#define FIFO_1_OUT_CSR_SPAN 32
#define FIFO_1_OUT_CSR_SYMBOLS_PER_BEAT 2
#define FIFO_1_OUT_CSR_TYPE "altera_avalon_fifo"
#define FIFO_1_OUT_CSR_USE_AVALONMM_READ_SLAVE 1
#define FIFO_1_OUT_CSR_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_1_OUT_CSR_USE_AVALONST_SINK 0
#define FIFO_1_OUT_CSR_USE_AVALONST_SOURCE 0
#define FIFO_1_OUT_CSR_USE_BACKPRESSURE 1
#define FIFO_1_OUT_CSR_USE_IRQ 1
#define FIFO_1_OUT_CSR_USE_PACKET 1
#define FIFO_1_OUT_CSR_USE_READ_CONTROL 1
#define FIFO_1_OUT_CSR_USE_REGISTER 0
#define FIFO_1_OUT_CSR_USE_WRITE_CONTROL 1


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0_A
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x1051d0
#define JTAG_UART_0_IRQ 5
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * leds_green configuration
 *
 */

#define ALT_MODULE_CLASS_leds_green altera_avalon_pio
#define LEDS_GREEN_BASE 0x105190
#define LEDS_GREEN_BIT_CLEARING_EDGE_REGISTER 0
#define LEDS_GREEN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDS_GREEN_CAPTURE 0
#define LEDS_GREEN_DATA_WIDTH 8
#define LEDS_GREEN_DO_TEST_BENCH_WIRING 0
#define LEDS_GREEN_DRIVEN_SIM_VALUE 0
#define LEDS_GREEN_EDGE_TYPE "NONE"
#define LEDS_GREEN_FREQ 50000000
#define LEDS_GREEN_HAS_IN 0
#define LEDS_GREEN_HAS_OUT 1
#define LEDS_GREEN_HAS_TRI 0
#define LEDS_GREEN_IRQ -1
#define LEDS_GREEN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDS_GREEN_IRQ_TYPE "NONE"
#define LEDS_GREEN_NAME "/dev/leds_green"
#define LEDS_GREEN_RESET_VALUE 0
#define LEDS_GREEN_SPAN 16
#define LEDS_GREEN_TYPE "altera_avalon_pio"


/*
 * leds_red configuration
 *
 */

#define ALT_MODULE_CLASS_leds_red altera_avalon_pio
#define LEDS_RED_BASE 0x105170
#define LEDS_RED_BIT_CLEARING_EDGE_REGISTER 0
#define LEDS_RED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDS_RED_CAPTURE 0
#define LEDS_RED_DATA_WIDTH 18
#define LEDS_RED_DO_TEST_BENCH_WIRING 0
#define LEDS_RED_DRIVEN_SIM_VALUE 0
#define LEDS_RED_EDGE_TYPE "NONE"
#define LEDS_RED_FREQ 50000000
#define LEDS_RED_HAS_IN 0
#define LEDS_RED_HAS_OUT 1
#define LEDS_RED_HAS_TRI 0
#define LEDS_RED_IRQ -1
#define LEDS_RED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDS_RED_IRQ_TYPE "NONE"
#define LEDS_RED_NAME "/dev/leds_red"
#define LEDS_RED_RESET_VALUE 0
#define LEDS_RED_SPAN 16
#define LEDS_RED_TYPE "altera_avalon_pio"


/*
 * mutex_0 configuration
 *
 */

#define ALT_MODULE_CLASS_mutex_0 altera_avalon_mutex
#define MUTEX_0_BASE 0x1051c0
#define MUTEX_0_IRQ -1
#define MUTEX_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MUTEX_0_NAME "/dev/mutex_0"
#define MUTEX_0_OWNER_INIT 0
#define MUTEX_0_OWNER_WIDTH 16
#define MUTEX_0_SPAN 8
#define MUTEX_0_TYPE "altera_avalon_mutex"
#define MUTEX_0_VALUE_INIT 0
#define MUTEX_0_VALUE_WIDTH 16


/*
 * mutex_1 configuration
 *
 */

#define ALT_MODULE_CLASS_mutex_1 altera_avalon_mutex
#define MUTEX_1_BASE 0x1051b8
#define MUTEX_1_IRQ -1
#define MUTEX_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MUTEX_1_NAME "/dev/mutex_1"
#define MUTEX_1_OWNER_INIT 0
#define MUTEX_1_OWNER_WIDTH 16
#define MUTEX_1_SPAN 8
#define MUTEX_1_TYPE "altera_avalon_mutex"
#define MUTEX_1_VALUE_INIT 0
#define MUTEX_1_VALUE_WIDTH 16


/*
 * mutex_2 configuration
 *
 */

#define ALT_MODULE_CLASS_mutex_2 altera_avalon_mutex
#define MUTEX_2_BASE 0x1051b0
#define MUTEX_2_IRQ -1
#define MUTEX_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MUTEX_2_NAME "/dev/mutex_2"
#define MUTEX_2_OWNER_INIT 0
#define MUTEX_2_OWNER_WIDTH 16
#define MUTEX_2_SPAN 8
#define MUTEX_2_TYPE "altera_avalon_mutex"
#define MUTEX_2_VALUE_INIT 0
#define MUTEX_2_VALUE_WIDTH 16


/*
 * mutex_3 configuration
 *
 */

#define ALT_MODULE_CLASS_mutex_3 altera_avalon_mutex
#define MUTEX_3_BASE 0x1051a8
#define MUTEX_3_IRQ -1
#define MUTEX_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MUTEX_3_NAME "/dev/mutex_3"
#define MUTEX_3_OWNER_INIT 0
#define MUTEX_3_OWNER_WIDTH 16
#define MUTEX_3_SPAN 8
#define MUTEX_3_TYPE "altera_avalon_mutex"
#define MUTEX_3_VALUE_INIT 0
#define MUTEX_3_VALUE_WIDTH 16


/*
 * mutex_4 configuration
 *
 */

#define ALT_MODULE_CLASS_mutex_4 altera_avalon_mutex
#define MUTEX_4_BASE 0x1051a0
#define MUTEX_4_IRQ -1
#define MUTEX_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MUTEX_4_NAME "/dev/mutex_4"
#define MUTEX_4_OWNER_INIT 0
#define MUTEX_4_OWNER_WIDTH 16
#define MUTEX_4_SPAN 8
#define MUTEX_4_TYPE "altera_avalon_mutex"
#define MUTEX_4_VALUE_INIT 0
#define MUTEX_4_VALUE_WIDTH 16


/*
 * performance_counter_0 configuration
 *
 */

#define ALT_MODULE_CLASS_performance_counter_0 altera_avalon_performance_counter
#define PERFORMANCE_COUNTER_0_BASE 0x105000
#define PERFORMANCE_COUNTER_0_HOW_MANY_SECTIONS 5
#define PERFORMANCE_COUNTER_0_IRQ -1
#define PERFORMANCE_COUNTER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PERFORMANCE_COUNTER_0_NAME "/dev/performance_counter_0"
#define PERFORMANCE_COUNTER_0_SPAN 128
#define PERFORMANCE_COUNTER_0_TYPE "altera_avalon_performance_counter"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x1000000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x16
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 8
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 12
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 8388608
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * shared_onchip configuration
 *
 */

#define ALT_MODULE_CLASS_shared_onchip altera_avalon_onchip_memory2
#define SHARED_ONCHIP_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define SHARED_ONCHIP_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define SHARED_ONCHIP_BASE 0x102000
#define SHARED_ONCHIP_CONTENTS_INFO ""
#define SHARED_ONCHIP_DUAL_PORT 0
#define SHARED_ONCHIP_GUI_RAM_BLOCK_TYPE "AUTO"
#define SHARED_ONCHIP_INIT_CONTENTS_FILE "nios2_mpsoc_shared_onchip"
#define SHARED_ONCHIP_INIT_MEM_CONTENT 1
#define SHARED_ONCHIP_INSTANCE_ID "NONE"
#define SHARED_ONCHIP_IRQ -1
#define SHARED_ONCHIP_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SHARED_ONCHIP_NAME "/dev/shared_onchip"
#define SHARED_ONCHIP_NON_DEFAULT_INIT_FILE_ENABLED 0
#define SHARED_ONCHIP_RAM_BLOCK_TYPE "AUTO"
#define SHARED_ONCHIP_READ_DURING_WRITE_MODE "DONT_CARE"
#define SHARED_ONCHIP_SINGLE_CLOCK_OP 0
#define SHARED_ONCHIP_SIZE_MULTIPLE 1
#define SHARED_ONCHIP_SIZE_VALUE 8192
#define SHARED_ONCHIP_SPAN 8192
#define SHARED_ONCHIP_TYPE "altera_avalon_onchip_memory2"
#define SHARED_ONCHIP_WRITABLE 1


/*
 * sram configuration
 *
 */

#define ALT_MODULE_CLASS_sram altera_up_avalon_sram
#define SRAM_BASE 0x80000
#define SRAM_IRQ -1
#define SRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAM_NAME "/dev/sram"
#define SRAM_SPAN 524288
#define SRAM_TYPE "altera_up_avalon_sram"


/*
 * switches configuration
 *
 */

#define ALT_MODULE_CLASS_switches altera_avalon_pio
#define SWITCHES_BASE 0x105180
#define SWITCHES_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCHES_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWITCHES_CAPTURE 0
#define SWITCHES_DATA_WIDTH 18
#define SWITCHES_DO_TEST_BENCH_WIRING 0
#define SWITCHES_DRIVEN_SIM_VALUE 0
#define SWITCHES_EDGE_TYPE "NONE"
#define SWITCHES_FREQ 50000000
#define SWITCHES_HAS_IN 1
#define SWITCHES_HAS_OUT 0
#define SWITCHES_HAS_TRI 0
#define SWITCHES_IRQ -1
#define SWITCHES_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SWITCHES_IRQ_TYPE "NONE"
#define SWITCHES_NAME "/dev/switches"
#define SWITCHES_RESET_VALUE 0
#define SWITCHES_SPAN 16
#define SWITCHES_TYPE "altera_avalon_pio"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x1051c8
#define SYSID_ID 538186246
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1423040903
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer_0_A configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0_A altera_avalon_timer
#define TIMER_0_A_ALWAYS_RUN 0
#define TIMER_0_A_BASE 0x105120
#define TIMER_0_A_COUNTER_SIZE 32
#define TIMER_0_A_FIXED_PERIOD 0
#define TIMER_0_A_FREQ 50000000
#define TIMER_0_A_IRQ 2
#define TIMER_0_A_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_A_LOAD_VALUE 49999
#define TIMER_0_A_MULT 0.0010
#define TIMER_0_A_NAME "/dev/timer_0_A"
#define TIMER_0_A_PERIOD 1
#define TIMER_0_A_PERIOD_UNITS "ms"
#define TIMER_0_A_RESET_OUTPUT 0
#define TIMER_0_A_SNAPSHOT 1
#define TIMER_0_A_SPAN 32
#define TIMER_0_A_TICKS_PER_SEC 1000.0
#define TIMER_0_A_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_A_TYPE "altera_avalon_timer"


/*
 * timer_0_B configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0_B altera_avalon_timer
#define TIMER_0_B_ALWAYS_RUN 0
#define TIMER_0_B_BASE 0x105100
#define TIMER_0_B_COUNTER_SIZE 32
#define TIMER_0_B_FIXED_PERIOD 0
#define TIMER_0_B_FREQ 50000000
#define TIMER_0_B_IRQ 3
#define TIMER_0_B_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_B_LOAD_VALUE 49999
#define TIMER_0_B_MULT 0.0010
#define TIMER_0_B_NAME "/dev/timer_0_B"
#define TIMER_0_B_PERIOD 1
#define TIMER_0_B_PERIOD_UNITS "ms"
#define TIMER_0_B_RESET_OUTPUT 0
#define TIMER_0_B_SNAPSHOT 1
#define TIMER_0_B_SPAN 32
#define TIMER_0_B_TICKS_PER_SEC 1000.0
#define TIMER_0_B_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_B_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
