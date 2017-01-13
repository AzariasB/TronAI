/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: azarias
 *
 * Created on 11 janvier 2017, 21:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#include <time.h>
#include "game.h"

void processRectPos(sfIntRect *rect) {
    rect->left = (rect->left + rect->width);
    if (rect->left >= (rect->width * 5)) {
        rect->left = 0;
        rect->top = (rect->top + rect->height) % (rect->height * 2);
    }

}

int main(int argc, char** argv) {
    srand(time(NULL)); //Rand number init

    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow * window = sfRenderWindow_create(mode, "SFML", sfClose, NULL);

    game *m_game = game_create();
    game_init_player_pos(m_game);
    game_resize_window(m_game, window);

    printf("Player 1 => x :%d, y :%d\nPlayer 2 => x:%d, y :%d \n",
            m_game->player1->position.x,
            m_game->player1->position.y,
            m_game->player2->position.x,
            m_game->player2->position.y);


    sfRenderWindow_setFramerateLimit(window, 20);

    game *g_cpy = game_copy(m_game);
    game_destroy(g_cpy);
    
    //	sfMusic_play(music);
    while (sfRenderWindow_isOpen(window)) {
        game_main_loop(m_game, window);
    }


    game_destroy(m_game);
    sfRenderWindow_destroy(window);

    return (EXIT_SUCCESS);
}
