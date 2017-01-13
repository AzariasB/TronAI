

/* 
 * File:   state_play.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 19:32
 */

#ifndef STATE_PLAY_H
#define STATE_PLAY_H

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "game_state.h"
#include "utils.h"

typedef struct game game;

typedef struct state_play{
    game_state *super;
} state_play;

state_play *state_play_create();

void state_play_destroy(state_play *s);

void state_play_init(game *g);


void state_play_cleanup(game *g);

void state_play_pause(game *g);

void state_play_resume(game *g);

void state_play_handle_event(game *g);

void state_play_update(game *g);

void state_play_draw(game *g);

#endif /* STATE_PLAY_H */

