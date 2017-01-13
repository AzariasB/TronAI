/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game_state.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 19:26
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef struct game game;

typedef struct game_state{
    char *name;
    void (*init)(game *);
    void (*cleanup)(game *);
    void (*pause)(game *);
    void (*resume)(game *);
    void (*handle_event)(game *);
    void (*update)(game *);
    void (*draw)(game *);
} game_state;


game_state *game_state_create(char *name);

game_state *game_state_copy(const game_state *to_copy);

void game_state_destroy(game_state *s );

#endif /* GAME_STATE_H */

