#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

// FFmpeg 头文件
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>

// ALSA 头文件
#include <alsa/asoundlib.h>

typedef enum { PLAYER_STOPPED, PLAYER_PLAYING, PLAYER_PAUSED } player_state_t;

typedef struct
{
    // FFmpeg 相关
    AVFormatContext * format_ctx;
    AVCodecContext * codec_ctx;
    SwrContext * swr_ctx;
    int audio_stream_index;

    // ALSA 相关
    snd_pcm_t * pcm_handle;
    snd_pcm_uframes_t frames;
    unsigned int sample_rate;
    int channels;
    snd_mixer_t * mixer;
    snd_mixer_elem_t * elem;
    long min_volume, max_volume;
    int volume; // 0-100

    // 播放控制
    volatile int state;
    volatile int seek_request;
    volatile int64_t seek_pos;
    pthread_t play_thread;
    pthread_mutex_t mutex;

    // 进度信息
    volatile int64_t current_pts;
    AVRational time_base;
    int64_t duration;

    char * filename;
} audio_player_t;

// 函数声明
audio_player_t * player_create(const char * filename);
int player_init(audio_player_t * player);
int player_pause(audio_player_t * player);
int player_resume(audio_player_t * player);
int player_stop(audio_player_t * player);
int player_seek_pct(audio_player_t * player, double percent);
int player_seek_ms(audio_player_t * player, int64_t target_ms);
int64_t player_get_position_ms(audio_player_t * player);
int64_t player_get_duration_ms(audio_player_t * player);
double player_get_position_pct(audio_player_t * player);
player_state_t player_get_state(audio_player_t * player);
void player_destroy(audio_player_t * player);

// 音量控制
int player_set_volume(audio_player_t * player, int volume);
int player_get_volume(audio_player_t * player);
int player_init_volume_control(audio_player_t * player);
void player_close_volume_control(audio_player_t * player);

#endif