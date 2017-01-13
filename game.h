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

#include "grid.h"
#include "player.h"
#include "utils.h"

typedef struct game {
    player *player1;
    player *player2; //IA
    grid *board;
    sfBool paused;
} game;


game *game_create();

void game_resize_window(const game *g, sfRenderWindow *window);

void game_main_loop(game *g, sfRenderWindow *window);

void game_process(game *g, sfEvent ev);

void game_add_player_pos(game *g, player *p);

sfBool game_player_is_dead(game *g, player *p);

game *game_copy(const game *g);

void game_render(const game *g, sfRenderWindow *window);

void game_init_player_pos(game *g);


void game_destroy(game* g);

#endif /* GAME_H */

