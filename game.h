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


game *game_create();

sfVector2i game_window_size(const game *g);

void game_main_loop(game *g);


void game_add_player_pos(game *g, player *p);

sfBool game_player_is_dead(game *g, player *p);

sfBool game_cell_is_empty(game *g, sfVector2i pos);

game *game_copy(const game *g);

void game_change_state(game *g, char *state_name);

void game_init_player_pos(game *g);


void game_destroy(game* g);

#endif /* GAME_H */

