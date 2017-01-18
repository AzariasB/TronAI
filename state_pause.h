
/* 
 * File:   state_pause.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 21:55
 */

#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H

#include <SFML/Graphics/Types.h>
#include <SFML/Window/Event.h>

#include "game_state.h"
#include "utils.h"

typedef struct state_pause {
    game_state *super;
    sfText *pause_text;
    sfText *resume_texte;
    sfText *exit_text;
    sfText *menu_text;
} state_pause;

state_pause *state_pause_create();

state_pause *state_pause_copy(state_pause *s);

void state_pause_destroy(state_pause *s);

void state_pause_init(game *g);

void state_pause_pause(game *g);

void state_pause_resume(game *g);

void state_pause_handle_event(game *g, sfEvent event);

void state_pause_update(game *g);

void state_pause_draw(game *g);

void state_pause_button_clicked(game *g, sfMouseButtonEvent ev);

void state_pause_mouse_moved(state_pause *p, sfMouseMoveEvent ev);

#endif /* STATE_PAUSE_H */

