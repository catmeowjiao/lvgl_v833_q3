#include "page_bird.h"

static lv_timer_t * timer;
static lv_obj_t * bird;
static lv_obj_t * tubeA;
static lv_obj_t * tubeB;
static lv_obj_t * touch_area;

static int birdY;
static double birdSpeed;
static int tubeAX;
static int tubeBX;

static void back_click(lv_event_t * e);
static void reset_click(lv_event_t * e);
static void timer_tick(lv_event_t * e);

lv_obj_t * page_bird()
{
    lv_obj_t * screen = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(screen);
    lv_obj_set_size(screen, lv_pct(100), lv_pct(100));

    timer = lv_timer_create(timer_tick, 30, NULL);

    lv_obj_t * btn_back = lv_btn_create(screen);
    lv_obj_set_size(btn_back, lv_pct(25), lv_pct(12));
    lv_obj_align(btn_back, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_t * btn_back_label = lv_label_create(btn_back);
    lv_label_set_text(btn_back_label, "back");
    lv_obj_center(btn_back_label);
    lv_obj_add_event_cb(btn_back, back_click, LV_EVENT_CLICKED, NULL);

    lv_obj_t * btn_restart = lv_btn_create(screen);
    lv_obj_set_size(btn_restart, lv_pct(25), lv_pct(12));
    lv_obj_align(btn_restart, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_t * btn_restart_label = lv_label_create(btn_restart);
    lv_label_set_text(btn_restart_label, "reset");
    lv_obj_center(btn_restart_label);
    lv_obj_add_event_cb(btn_restart, reset_click, LV_EVENT_CLICKED, NULL);

    bird = lv_img_create(screen);
    lv_obj_set_size(bird, 34, 24);
    lv_img_set_src(bird, "/mnt/UDISK/lvgl/res/bird/bird2.png");

    return screen;
}

static void timer_tick(lv_event_t * e)
{
    birdSpeed -= 0.5;
    birdY += birdSpeed;
    if(birdY < 0) birdY = 0;


}

static void reset_click(lv_event_t * e)
{

}

static void back_click(lv_event_t * e)
{
    page_back();
}