

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

typedef struct game game;

typedef struct state_menu{
    game_state *super;
    sfText *text_menu;
    sfText *text_play;
    sfText *text_exit;
    sfMusic *music;
} state_menu;

state_menu *state_menu_create();

state_menu *state_menu_copy(state_menu *s);

void state_menu_destroy(state_menu *s);

void state_menu_init(game *g);

void state_menu_draw(game *g);

void state_menu_pause(game *g);

void state_menu_resume(game *g);

void state_menu_handle_event(game *g);

void state_menu_update(game *g);


void state_menu_button_clicked(game *g, sfMouseButtonEvent ev);

void state_menu_mouse_moved(state_menu *s, sfMouseMoveEvent ev);

#endif /* STATE_MENU_H */

