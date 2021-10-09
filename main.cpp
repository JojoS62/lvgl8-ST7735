/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "lvgl/lvgl.h"
#include "lvglDriver/LVGLDispDriver_GC9A01.h"
#include "lvglDriver/LVGLDispDriver_ST7735.h"
#include "lvglDriver/TARGET_STM32F407VE_BLACK/LVGLDispDriverSTM32F407VE_BLACK.h"
#include "lvglDriver/LVGLInputDriverBase.h"

SPI spiDisplay(PB_5, NC, PB_3);
DigitalOut led1(LED1, 0);   // onboard LED D2 1: off, 0: on
DigitalOut csFlash(PA_15, 1);   // flash cs off

// simple lv screen 

void btn_event_cb(lv_event_t * e)
{
    printf("Clicked\n");
}

void create_lv_screen(lv_disp_t* disp) 
{
    lv_obj_t * scr = lv_disp_get_scr_act(disp);

    lv_obj_t * btn = lv_btn_create(scr);                            /*Add a button to the current screen*/
    lv_obj_set_size(btn, 100, 50);                                  /*Set its size*/
    lv_obj_center(btn);   
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

void create_lv_screen_3(lv_disp_t* disp) 
{
    lv_obj_t * scr = lv_disp_get_scr_act(disp);

    lv_obj_t * label1 = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label1, "Sonne");                             /*Set the labels text*/
    lv_obj_set_pos(label1, 0, 0);                                    /*Set its position*/

    lv_obj_t * label1V = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label1V, "1000 W");                             /*Set the labels text*/
    lv_obj_align_to(label1V, label1, LV_ALIGN_BOTTOM_LEFT, 100, 0);


    lv_obj_t * label2 = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label2, "Verbrauch");                             /*Set the labels text*/
    lv_obj_align_to(label2, label1, LV_ALIGN_BOTTOM_LEFT, 0, 20);

    lv_obj_t * label2V = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label2V, "1000 W");                             /*Set the labels text*/
    lv_obj_align_to(label2V, label2, LV_ALIGN_BOTTOM_LEFT, 100, 0);


    lv_obj_t * label3 = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label3, "Netz");                             /*Set the labels text*/
    lv_obj_align_to(label3, label2, LV_ALIGN_BOTTOM_LEFT,  0, 20);

    lv_obj_t * label3V = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label3V, "1000 W");                             /*Set the labels text*/
    lv_obj_align_to(label3V, label3, LV_ALIGN_BOTTOM_LEFT, 100, 0);


    lv_obj_t * label4 = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label4, "Batterie");                             /*Set the labels text*/
    lv_obj_align_to(label4, label3, LV_ALIGN_BOTTOM_LEFT, 0, 20);

    lv_obj_t * label4V = lv_label_create(scr);                        /*Add a label to the button*/
    lv_label_set_text(label4V, " 100 %");                             /*Set the labels text*/
    lv_obj_align_to(label4V, label4, LV_ALIGN_BOTTOM_LEFT, 100, 0);
}

void gauge_set_value(lv_obj_t* meter, lv_meter_indicator_t * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
}

/**
 * Test run time theme change
 */

typedef struct {
    lv_obj_t* meter;
    lv_meter_indicator_t * indic;
} lv_gaugescreen_param_t;

void lv_gauge_screen(lv_disp_t* disp, lv_gaugescreen_param_t* retparam)
{
    lv_obj_t * scr = lv_disp_get_scr_act(disp);
    lv_disp_load_scr(scr);

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_pad_all(&style, 0);
    lv_style_set_border_width(&style, 1);
    lv_style_set_text_font(&style, &lv_font_montserrat_10);


    lv_obj_t* meter = lv_meter_create(scr);
    lv_obj_add_style(meter, &style, LV_PART_MAIN);
    lv_obj_center(meter);
    int maxSize = min(lv_obj_get_width(scr), lv_obj_get_height(scr)) - 10;
    lv_obj_set_size(meter, maxSize, maxSize);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    //lv_obj_set_size(scale, 230, 230);
    lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);

    /*Add a blue arc to the start*/
    lv_meter_indicator_t * indic;
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    /*Make the tick lines blue at the start of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    /*Add a red arc to the end*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    /*Make the tick lines red at the end of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

    retparam->meter = meter;
    retparam->indic = indic;
}


void fnLvTicker()
{
    lv_tick_inc(2); /*Tell LittlevGL that 2 milliseconds were elapsed*/
}



int main()
{
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    spiDisplay.frequency(50e6);     // will be limited to some internal value

    //lv_init();
    [[maybe_unused]] LVGLDispDriver* lvglDisplay_main = LVGLDispDriver::get_target_default_instance();
    LVGLInputDriver::get_target_default_instance_touchdrv(lvglDisplay_main);

    [[maybe_unused]] LVGLDispGC9A01* lvglDisplay_2 = new LVGLDispGC9A01(spiDisplay, PB_9, PB_6, PB_7, PB_8);
    // [[maybe_unused]] LVGLDispST7735* lvglDisplay_2 = new LVGLDispST7735(spiDisplay, PB_9, PB_6, PB_7);

    lv_theme_t * th = lv_theme_default_init(lvglDisplay_2->getLVDisp(),  /*Use the DPI, size, etc from this display*/ 
                                            lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                            false, &lv_font_montserrat_14);
                                            
    lv_disp_set_theme(lvglDisplay_2->getLVDisp(), th); /*Assign the theme to the display*/

    Ticker tickerLvgl;
    tickerLvgl.attach(callback(&fnLvTicker), 2ms);

    create_lv_screen(lvglDisplay_main->getLVDisp());

    lv_gaugescreen_param_t gauge_param {0};
    lv_gauge_screen(lvglDisplay_2->getLVDisp(), &gauge_param);

    AnalogIn aIn(PA_0);
    float newValue;
    float maxValue = 0.0f;

    while(true) {
        lv_task_handler();
        ThisThread::sleep_for(20ms);
        led1 = !led1;

        newValue = aIn.read() * 115.0f - 15.0f;

        if (newValue < maxValue) {
            newValue = maxValue;
            maxValue *= 0.90f;
        } else {
            maxValue = newValue;
        }

        gauge_set_value(gauge_param.meter, gauge_param.indic, newValue);
    }
}