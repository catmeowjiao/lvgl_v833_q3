#include "page_audio.h"

static void back_click(lv_event_t * e);

lv_obj_t * page_audio(char * filename)
{
    lv_obj_t * screen = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(screen);
    lv_obj_set_size(screen, lv_pct(100), lv_pct(100));

    system("echo 1 > /dev/spk_crtl");
    audio_player_t * player = player_create(filename); // /mnt/app/factory/play_test.wav
    player_play(player);

    lv_obj_t * btn_back = lv_btn_create(screen);
    lv_obj_set_size(btn_back, lv_pct(25), lv_pct(12));
    lv_obj_align(btn_back, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_t * btn_back_label = lv_label_create(btn_back);
    lv_label_set_text(btn_back_label, "back");
    lv_obj_center(btn_back_label);
    lv_obj_add_event_cb(btn_back, back_click, LV_EVENT_CLICKED, player);

    return screen;
}

static void back_click(lv_event_t * e)
{
    printf("click");
    audio_player_t * player = e->user_data;
    printf("destroy");
    player_destroy(player);
    printf("done");
    system("echo 0 > /dev/spk_crtl");
    page_back();
}