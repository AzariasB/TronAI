
#include <SFML/Audio/Types.h>
#include <SFML/Audio/Music.h>
#include <SFML/Audio/SoundBuffer.h>
#include <SFML/Audio/Sound.h>





#include "audio_manager.h"
#include "utils.h"
#ifdef AUDIO_MANAGER_H

typedef struct sound_pair {
    sound_enum key;
    sfSoundBuffer *sound_buffer;
    sfSound *sound;
} sound_pair;

char *sound_filename(sound_enum s_enum) {
    if (s_enum == SOUND_CLICK1) {
        return "sounds/click.wav";
    } else {
        return "sounds/click_2.wav";
    }
}

sound_pair *sound_create(sound_enum s_enum) {
    sound_pair *pair = utils_safe_malloc(sizeof (sound_pair), "Creating sound pair");
    pair->key = s_enum;
    pair->sound_buffer = sfSoundBuffer_createFromFile(sound_filename(s_enum));
    pair->sound = sfSound_create();
    sfSound_setBuffer(pair->sound, pair->sound_buffer);
    return pair;
}

void sound_destroy(void *to_destroy) {
    sound_pair *s_pair = to_destroy;
    sfSound_destroy(s_pair->sound);
    sfSoundBuffer_destroy(s_pair->sound_buffer);
    free(s_pair);
    s_pair = 0;
}

typedef struct music_pair {
    music_enum key;
    sfMusic *value;
} music_pair;

char *music_filename(music_enum m_enum) {
    if (m_enum == MUSIC_MENU) {
        return "musics/menu_music.ogg";
    } else {
        return "musics/play_music.ogg";
    }
}

music_pair *music_create(music_enum m_enum) {
    music_pair *pair = utils_safe_malloc(sizeof (music_pair), "Creating music pair");
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
    audio_manager *manager = utils_safe_malloc(sizeof (audio_manager), "Creating audio manager");
    manager->musics = list_create();
    manager->sounds = list_create();

    for (music_enum e = MUSIC_MENU; e < MUSIC_ALL; e++) {
        music_pair *p = music_create(e);
        list_push(manager->musics, p);
    }

    for (sound_enum e = SOUND_CLICK1; e < SOUND_ALL; e++) {
        sound_pair *p = sound_create(e);
        list_push(manager->sounds, p);
    }
    manager->current_music = NULL;
    return manager;
}

void audio_manager_play_sound(audio_manager* manager, sound_enum s_enum) {
    for (int i = 0; i < manager->sounds->size; i++) {
        sound_pair *p = list_get(manager->sounds, i);
        if (p->key == s_enum) {
            sfSound_play(p->sound);
            return;
        }
    }
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
    list_destroy(to_destroy->sounds, &sound_destroy);
    to_destroy->current_music = NULL;
    free(to_destroy);
    to_destroy = 0;
}

#endif