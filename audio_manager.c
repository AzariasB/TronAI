
#include <SFML/Audio/Types.h>
#include <SFML/Audio/Music.h>




//Music specific

#include "audio_manager.h"
#ifdef AUDIO_MANAGER_H

typedef struct music_pair {
    music_enum key;
    sfMusic *value;
} music_pair;


char *music_filename(music_enum m_enum) {
    if (m_enum == MUSIC_MENU) {
        return "menu_music.ogg";
    } else {
        return "play_music.ogg";
    }
}

music_pair *music_create(music_enum m_enum) {
    music_pair *pair = malloc(sizeof (music_pair));
    pair->key = m_enum;
    pair->value = sfMusic_createFromFile(music_filename(m_enum));
    sfMusic_setLoop(pair->value, sfTrue);
    return pair;
}

void music_destroy(void* data) {
    music_pair *pair = data;
    sfMusic_destroy(pair->value);
    free(pair);
    pair = 0;
}



//Audio manager

audio_manager *audio_manager_create() {
    audio_manager *manager = malloc(sizeof (audio_manager));
    manager->musics = list_create();
    for (music_enum e = MUSIC_MENU; e <= MUSIC_PLAY; e++) {
        music_pair *p = music_create(e);
        list_push(manager->musics, p);
    }
    manager->current_music = NULL;
    return manager;
}

void audio_manager_change_music(audio_manager* manager, music_enum m_enum) {
    if (manager->current_music != NULL) {
        sfMusic_pause(manager->current_music->value);
    }
    manager->current_music = NULL;
    for (int i = 0; i < manager->musics->size; i++) {
        music_pair *p = list_get(manager->musics, i);
        if (p->key == m_enum) {
            manager->current_music = p;
            sfMusic_play(manager->current_music->value);
            break;
        }
    }
}

void audio_manager_destroy(audio_manager* to_destroy) {
    list_destroy(to_destroy->musics, &music_destroy);
    to_destroy->current_music = NULL;
    free(to_destroy);
    to_destroy = 0;
}

#endif