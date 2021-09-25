/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "lvgl/lvgl.h"
#include "lvglDriver/LVGLDispDriver_GC9A01.h"

SPI spiDisplay(PB_5, NC, PB_3);

// simple lv screen 

// void btn_event_cb(lv_event_t * e)
// {
//     printf("Clicked\n");
// }

// void create_lv_screen() 
// {
//     lv_obj_t * btn = lv_btn_create(lv_scr_act());                   /*Add a button to the current screen*/
//     lv_obj_set_pos(btn, 10, 10);                                    /*Set its position*/
//     lv_obj_set_size(btn, 100, 50);                                  /*Set its size*/
//     lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/

//     lv_obj_t * label = lv_label_create(btn);                        /*Add a label to the button*/
//     lv_label_set_text(label, "Button");                             /*Set the labels text*/
//     lv_obj_center(label);                                           /*Align the label to the center*/
// }


int main()
{
    printf("Hello World, Mbed!\n");

    lv_init();
    spiDisplay.frequency(40e6);
    [[maybe_unused]] LVGLDispGC9A01* lvglDisplayGC9A01_1 = new LVGLDispGC9A01(spiDisplay, PB_9, PB_6, PB_7, PB_8);

    //create_lv_screen();

    while(true) {
        ThisThread::sleep_for(5ms);
    }
}