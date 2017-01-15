/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 09:12
 */

#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "grid.h"
#include "player.h"
#include "utils.h"
#include "state_manager.h"

/**
 * The game is the main structure of this project
 * It contains 2 players (an array later maybe ... ?)
 * The board/grid
 * A state manager to handle the different GUIs/menus
 * The window in which to draw
 * A boolean to tell wether the game is paused
 * A boolean to tell wether the game ended
 * A sprite and a texture for the background image
 */
typedef struct game {
    player *player1;
    player *player2; //IA
    grid *board;
    
    state_manager *st_manager;

    sfRenderWindow *window;
    sfBool paused;
    sfBool ended;
    
    sfTexture *background_texture;
    sfSprite *background_sprite;
} game;

/**
 * Creates a whole new game using the config
 * The game is set as paused
 * 
 * @return the game created
 */
game *game_create();

/**
 * Returns the min window to fit the games board
 * 
 * @param g the game
 * @return the min size of the windows to fit the game needs
 */
sfVector2i game_window_size(const game *g);

/**
 * Starts the game main loop.
 * Ends only when the window is closed
 * The window is closed by the user, either directly or bly clicking the "exit" button
 * 
 * @param g the game
 */
void game_main_loop(game *g);

/**
 * Add the player id to the grid, at the
 * players position
 * 
 * @param g the game
 * @param p the player to add to the grid
 */
void game_add_player_pos(game *g, player *p);

/**
 * Checks wether the player is dead given is position
 * A player is dead if he reached the border
 * or if the cell is currently in is not empty
 * 
 * @param g the game
 * @param p the player who might be dead
 * @return 
 */
sfBool game_player_is_dead(game *g, player *p);

/**
 * Checks if the cell at the given position is empty
 * 
 * @param g the game
 * @param pos the position to check
 * @return wether the cell at the given position is empty ( == 0)
 */
sfBool game_cell_is_empty(game *g, sfVector2i pos);

/**
 * Copies the game
 * The window is not copied since it's not copyiable
 * So the same pointer is shared between the game copied
 * and the original game
 * 
 * @param g the game to copy
 * @return the copied game
 */
game *game_copy(const game *g);

/**
 * Changes the state of the game,
 * for example to go from the state 'menu' to the state 'play'
 * 
 * @param g the game
 * @param state_name the name of the destination state
 */
void game_change_state(game *g, char *state_name);

/**
 * Init the players position in the game
 * Checks for no collision between the player
 * when creating the game
 * 
 * @param g the game 
 */
void game_init_player_pos(game *g);

/**
 * Destroys the game
 * 
 * @param g the game to destroy
 */
void game_destroy(game* g);

#endif /* GAME_H */

