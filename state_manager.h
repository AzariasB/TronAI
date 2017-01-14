

/* 
 * File:   state_manager.h
 * Author: azarias
 *
 * Created on 14 janvier 2017, 11:49
 */

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H


#include "game_state.h"
#include "state_menu.h"
#include "state_pause.h"
#include "state_play.h"
#include "utils.h"


typedef struct game game;

typedef struct state_manager {
    game_state *current_state;

    state_menu *st_menu;
    state_pause *st_pause;
    state_play *st_play;

} state_manager;


state_manager *state_manager_create();

void state_manager_change_state(state_manager *m, game *g, char *name);

void state_manager_destroy(state_manager *m);

state_manager *state_manager_copy(state_manager *m);

#endif /* STATE_MANAGER_H */

