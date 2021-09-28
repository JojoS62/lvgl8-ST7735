/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "lvgl/lvgl.h"
#include "lvglDriver/LVGLDispDriver_GC9A01.h"

SPI spiDisplay(PB_5, NC, PB_3);
DigitalOut led1(LED1, 0);   // onboard LED D2 1: off, 0: on

// simple lv screen 

void btn_event_cb(lv_event_t * e)
{
    printf("Clicked\n");
}

void create_lv_screen() 
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());                   /*Add a button to the current screen*/
    lv_obj_set_pos(btn, 70, 95);                                    /*Set its position*/
    lv_obj_set_size(btn, 100, 50);                                  /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);                        /*Add a label to the button*/
    lv_label_set_text(label, "hello");                             /*Set the labels text*/
    lv_obj_center(label);                                           /*Align the label to the center*/
}


void fnLvTicker()
{
    lv_tick_inc(2); /*Tell LittlevGL that 2 milliseconds were elapsed*/
}



int main()
{
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    spiDisplay.frequency(40e6);

    lv_init();
    [[maybe_unused]] LVGLDispGC9A01* lvglDisplayGC9A01_1 = new LVGLDispGC9A01(spiDisplay, PB_9, PB_6, PB_7, PB_8);

    Ticker tickerLvgl;
    tickerLvgl.attach(&fnLvTicker, 2ms);

    create_lv_screen();

    while(true) {
        lv_task_handler();
        ThisThread::sleep_for(50ms);
        led1 = !led1;
    }
}