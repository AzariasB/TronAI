
/* 
 * File:   game_state.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 19:26
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef struct game game;

#include <SFML/Window/Event.h>
#include <string.h>

/**
 * A game state is an interface
 * The game state has a name
 * It must contains the following functions 
 *  - init called when created
 *  - pause called when the state of the game is changing, and the current state is 'left'
 *  - resume called when the state of the game is changin, and the new state resumes
 *  - handle_event to handle the window event. MUST be implemented to communicate with the system
 *  - update called to compute the next step of rendering
 *  - draw draws the current state
 */
typedef struct game_state {
    char *name;
    void (*init)(game *);
    void (*pause)(game *);
    void (*resume)(game *);
    void (*handle_event)(game *, sfEvent);
    void (*update)(game *);
    void (*draw)(game *);
} game_state;

/**
 * Creates a state with the given name
 * 
 * @param name the name of the state
 * @return the game_state created
 */
game_state *game_state_create(char *name);

/**
 * Copies the given game_state
 * 
 * @param to_copy the game_state to copy
 * @return the copied game state
 */
game_state *game_state_copy(const game_state *to_copy);

/**
 * Destroys the given game_state
 * 
 * @param s the game_state to destroy
 */
void game_state_destroy(game_state *s);

#endif /* GAME_STATE_H */

