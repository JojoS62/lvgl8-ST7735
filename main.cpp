/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "lvgl/lvgl.h"
#include "lvglDriver/LVGLDispDriver_GC9A01.h"

SPI spiDisplay(PB_5, NC, PB_3);

int main()
{
    printf("Hello World, Mbed!\n");

    lv_init();
    spiDisplay.frequency(40e6);
    LVGLDispGC9A01* lvglDisplayGC9A01_1 = new LVGLDispGC9A01(spiDisplay, PB_9, PB_6, PB_7, PB_8);

    return 0;
}