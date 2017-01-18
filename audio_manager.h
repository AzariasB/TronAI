
/* 
 * File:   audio_manager.h
 * Author: azarias
 *
 * Created on 18 janvier 2017, 17:22
 */

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "list.h"

typedef enum music_enum {
    MUSIC_MENU,
    MUSIC_PLAY
} music_enum;


typedef struct music_pair music_pair;
//Audio manager

typedef struct audio_manager {
    list *musics;

    music_pair *current_music;

} audio_manager;


audio_manager *audio_manager_create();

void audio_manager_destroy(audio_manager *to_destroy);

void audio_manager_change_music(audio_manager *manager, music_enum m_enum);

#endif /* AUDIO_MANAGER_H */

