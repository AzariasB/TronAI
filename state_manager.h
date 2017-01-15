

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

/**
 * The state manager is used by the game
 * to manage its states.
 * The state_manager has a current state,
 * and 'available' states,
 *  currently, the available states are :
 *  - menu
 *  - play
 *  - pause
 */
typedef struct state_manager {
    game_state *current_state;

    state_menu *st_menu;
    state_pause *st_pause;
    state_play *st_play;

} state_manager;

/**
 * Creates a state_manager
 * 
 * @return the created state_manager
 */
state_manager *state_manager_create();

/**
 * Changes the current_state of the state_manager
 * The game parameter is required to give it as argument
 * (todo : add game * type in the struct)
 * 
 * @param m the state_manager
 * @param g the game
 * @param name the name of the state_manager
 */
void state_manager_change_state(state_manager *m, game *g, char *name);

/**
 * Destroys the given state_manager
 * 
 * @param m the state_manager to destroy
 */
void state_manager_destroy(state_manager *m);

/**
 * Copies the given state manager
 * 
 * @param m the state_manager to copy
 * @return the copied state_manager
 */
state_manager *state_manager_copy(state_manager *m);

#endif /* STATE_MANAGER_H */

