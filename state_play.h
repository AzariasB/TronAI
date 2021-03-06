

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
#include <SFML/Audio/Types.h>
#include "game_state.h"
#include "utils.h"
#include "player.h"

typedef struct game game;

/**
 * This struct 'implements' the game_state interface
 * This is the 'main' state of the game. The one
 * where you can actually play the game.
 * It has a music, and (as a test) a glow texture/sprite
 */
typedef struct state_play
{
    game_state *super;
    sfText *end_text;

} state_play;

/**
 * Created a state_play
 * 
 * @return  the state_play created
 */
state_play *state_play_create();

/**
 * Copies the game state
 * 
 * @param s the state_play to copy
 * @return the state_play copied
 */
state_play *state_play_copy(state_play *s);

void state_play_destroy(state_play *s);

void state_play_init(game *g);

void state_play_pause(game *g);

void state_play_resume(game *g);

void state_play_handle_event(game *g, sfEvent event);

void state_play_update(game *g);

void state_play_draw(game *g);

/**
 * Called whenever a player dies
 * If more than two players are still alive
 * the game continues
 * else, the game is finished
 * 
 * @param g the game 
 * @param p the player who died
 */
void state_play_player_died(game *g, player *p);


#endif /* STATE_PLAY_H */

