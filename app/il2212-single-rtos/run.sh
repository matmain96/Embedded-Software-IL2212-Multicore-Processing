#!/bin/bash

APP=lab2
BSP_DIR=../../bsp
BSP=lab2
CORE_DIR=../../hardware/de2_nios2_mpsoc
SOPCINFO=nios2_mpsoc
SOF=de2_nios2_mpsoc
CPU=cpu_0


# Create BSP-Package

'rm' -Rf $BSP_DIR/${BSP}

nios2-bsp ucosii $BSP_DIR/${BSP} $CORE_DIR/$SOPCINFO.sopcinfo \
      --cpu-name $CPU \
      --default_sections_mapping sram \
      --set hal.sys_clk_timer timer_0_A \
      --set hal.make.bsp_cflags_debug -g \
      --set hal.make.bsp_cflags_optimization -Os \
      --set hal.enable_sopc_sysid_check 1 \
      --set ucosii.os_tmr_en 1

echo " "
echo "BSP package creation finished"
echo " "

# Create Application
nios2-app-generate-makefile --bsp-dir $BSP_DIR/$BSP --elf-name $APP.elf --src-dir src_0/ --set APP_CFLAGS_OPTIMIZATION -Os

# Create ELF-file
make

# Download Hardware to Board

echo ""
echo "***********************************************"
echo "Download hardware to board"
echo "***********************************************"
echo ""

nios2-configure-sof $CORE_DIR/$SOF.sof

# Start Nios II Terminal

echo ""
echo "Start NiosII terminal ..."

xterm -e "nios2-terminal -i 0" &

echo ""
echo "***********************************************"
echo "Download software to board"
echo "***********************************************"
echo ""

nios2-download -g $APP.elf --cpu_name $CPU --jdi $CORE_DIR/$SOF.jdi

echo ""
echo "Statistics"
nios2-elf-size $APP.elf
