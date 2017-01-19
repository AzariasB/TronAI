

/* 
 * File:   state_menu.h
 * Author: azarias
 *
 * Created on 14 janvier 2017, 11:39
 */

#ifndef STATE_MENU_H
#define STATE_MENU_H

#include <stdlib.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include "game_state.h"
#include "utils.h"
#include "menu.h"

typedef struct game game;

typedef struct state_menu {
    game_state *super;
    menu *menu;
} state_menu;

state_menu *state_menu_create();

state_menu *state_menu_copy(state_menu *s);

void state_menu_destroy(state_menu *s);

void state_menu_init(game *g);

void state_menu_draw(game *g);

void state_menu_pause(game *g);

void state_menu_resume(game *g);

void state_menu_handle_event(game *g, sfEvent event);

void state_menu_update(game *g);

#endif /* STATE_MENU_H */

