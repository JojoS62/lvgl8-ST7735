/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "lvgl/lvgl.h"
#include "lvglDriver/LVGLDispDriver_GC9A01.h"
#include "lvglDriver/TARGET_STM32F407VE_BLACK/LVGLDispDriverSTM32F407VE_BLACK.h"
#include "lvglDriver/LVGLInputDriverBase.h"

SPI spiDisplay(PB_5, NC, PB_3);
DigitalOut led1(LED1, 0);   // onboard LED D2 1: off, 0: on

// simple lv screen 

void btn_event_cb(lv_event_t * e)
{
    printf("Clicked\n");
}

void create_lv_screen(lv_disp_t* disp) 
{
    lv_obj_t * scr = lv_disp_get_scr_act(disp);

    lv_obj_t * btn = lv_btn_create(scr);                            /*Add a button to the current screen*/
    lv_obj_set_pos(btn, 70, 95);                                    /*Set its position*/
    lv_obj_set_size(btn, 100, 50);                                  /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);                        /*Add a label to the button*/
    lv_label_set_text(label, "hello");                              /*Set the labels text*/
    lv_obj_center(label);                                           /*Align the label to the center*/
}

void create_lv_screen_2(lv_disp_t* disp) 
{
    lv_obj_t * scr = lv_disp_get_scr_act(disp);

    lv_obj_t * label1 = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label1, "Sonne");                             /*Set the labels text*/
    lv_obj_set_pos(label1, 30, 60);                                    /*Set its position*/

    lv_obj_t * label1V = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label1V, "1000 W");                             /*Set the labels text*/
    lv_obj_align_to(label1V, label1, LV_ALIGN_BOTTOM_LEFT, 100, 0);


    lv_obj_t * label2 = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label2, "Verbrauch");                             /*Set the labels text*/
    lv_obj_align_to(label2, label1, LV_ALIGN_BOTTOM_LEFT, -10, 30);

    lv_obj_t * label2V = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label2V, "1000 W");                             /*Set the labels text*/
    lv_obj_align_to(label2V, label2, LV_ALIGN_BOTTOM_LEFT, 120, 0);


    lv_obj_t * label3 = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label3, "Netz");                             /*Set the labels text*/
    lv_obj_align_to(label3, label2, LV_ALIGN_BOTTOM_LEFT,  0, 30);

    lv_obj_t * label3V = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label3V, "1000 W");                             /*Set the labels text*/
    lv_obj_align_to(label3V, label3, LV_ALIGN_BOTTOM_LEFT, 120, 0);


    lv_obj_t * label4 = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label4, "Batterie");                             /*Set the labels text*/
    lv_obj_align_to(label4, label3, LV_ALIGN_BOTTOM_LEFT, 10, 30);

    lv_obj_t * label4V = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label4V, " 100 %");                             /*Set the labels text*/
    lv_obj_align_to(label4V, label4, LV_ALIGN_BOTTOM_LEFT, 100, 0);
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

    //lv_init();
    [[maybe_unused]] LVGLDispDriver* lvglDisplay_main = LVGLDispDriver::get_target_default_instance();
    LVGLInputDriver::get_target_default_instance_touchdrv(lvglDisplay_main);

    [[maybe_unused]] LVGLDispGC9A01* lvglDisplayGC9A01_1 = new LVGLDispGC9A01(spiDisplay, PB_9, PB_6, PB_7, PB_8);

    Ticker tickerLvgl;
    tickerLvgl.attach(callback(&fnLvTicker), 2ms);

    create_lv_screen_2(lvglDisplayGC9A01_1->getLVDisp());
    create_lv_screen(lvglDisplay_main->getLVDisp());

    while(true) {
        lv_task_handler();
        ThisThread::sleep_for(10ms);
        led1 = !led1;
    }
}