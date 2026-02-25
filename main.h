#ifndef DENDRO_MAIN_H
#define DENDRO_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************                                                                                                 \
 *      INCLUDES                                                                                                       \
 *********************/
// 万能大头，别的文件都请引用我
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <string.h>
#include <math.h>

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lv_drv_conf.h"
#include "lv_lib_100ask/lv_lib_100ask.h"

#include "cJSON/cJSON.h"

#include "platform/audio_ctrl.h"
#include "platform/str_utils.h"
#include "platform/ff_player.h"

// 请教DeepSeek实现了简易页面管理器，100ask那个实际上不太好用……
#include "pages/page_manager.h"

// 页面列表，新加的页面在这里引用一下喵
#include "pages/page_main.h"
#include "pages/page_demo.h"
#include "pages/page_audio.h"
#include "pages/page_file_manager.h"
#include "pages/page_calculator.h"
#include "pages/page_apple.h"
#include "pages/page_image.h"
#include "pages/page_ftp.h"

// 控件列表喵
#include "views/lv_text_clock.h"

/*********************
 *      DEFINES
 *********************/
#define DISP_BUF_SIZE (LV_SCR_WIDTH * LV_SCR_HEIGHT)
#define PATH_MAX_LENGTH 256

char homepath[PATH_MAX_LENGTH] = {0};
int dispd  = 0; // 背光
int fbd    = 0; // 帧缓冲设备
int powerd = 0; // 电源按钮
int homed  = 0; // 主页按钮

uint32_t sleepTs        = -1;
uint32_t homeClickTs    = -1;
uint32_t backgroundTs   = -1;

bool deepSleep     = false;
bool dontDeepSleep = false;

void lcdBrightness(int brightness);
void sysSleep(void);
void sysWake(void);
void sysDeepSleep(void);
void setDontDeepSleep(bool b);
void switchRobot(void);
void switchBackground(void);
void switchForeground(void);

void lcdInit(void);
void lcdOpen(void);
void lcdClose(void);
void lcdRefresh(void);
void touchOpen(void);
void touchClose(void);

lv_style_t getFontStyle(const char * filename, uint16_t weight, uint16_t style);

uint32_t tick_get(void);

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
