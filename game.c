/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "game.h"

#ifdef GAME_H

game *game_create() {
    game *g = malloc(sizeof (game));

    player *p1 = player_create(1);
    player *p2 = player_create(2);
    grid *board = grid_create(BOARD_WIDTH, BOARD_HEIGHT);

    g->player1 = p1;
    g->player2 = p2;
    g->board = board;
    g->paused = sfTrue;

    return g;
}

void game_resize_window(const game* g, sfRenderWindow* window) {
    sfVector2u size;
    size.x = g->board->width * CELL_SIDE;
    size.y = g->board->height * CELL_SIDE;
    sfRenderWindow_setSize(window, size);
}

void game_render(const game* g, sfRenderWindow* window) {

    sfRectangleShape *p1_rect = player_to_rect(g->player1);
    sfRectangleShape *p2_rect = player_to_rect(g->player2);

    sfRenderWindow_drawRectangleShape(window, p1_rect, NULL);
    sfRenderWindow_drawRectangleShape(window, p2_rect, NULL);

}

void game_main_loop(game* g, sfRenderWindow *window) {

    sfEvent event;


    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        } else if (event.type == sfEvtKeyPressed && utils_is_valid_key(event.key.code)) {
            g->paused = sfFalse;
        }
    }

    game *g_cpy = game_copy(g);
    game_destroy(g_cpy);

    sfRenderWindow_clear(window, sfBlack);

    if (!g->paused) {
        game_process(g, event);
    }

    game_render(g, window);

    sfRenderWindow_display(window);

}

void game_process(game* g, sfEvent ev) {
    if (ev.type == sfEvtKeyPressed && utils_is_valid_key(ev.key.code)) {
        direction dir = direction_from_key_code(ev.key.code);
        sfVector2i nw_pos = utils_update_pos(g->player1->position, dir);
        //Check if dead
        
        g->player1->position = nw_pos;
    }
}

void game_init_player_pos(game* g) {
    g->player1->position = utils_vector_random(g->board->width, g->board->height);
    do {
        g->player2->position = utils_vector_random(g->board->width, g->board->height);
    } while (utils_vector_same(g->player1->position, g->player2->position));
}

game *game_copy(const game* g) {
    game *copy = malloc(sizeof (game));

    player *p1_copy = player_copy(g->player1);
    player *p2_copy = player_copy(g->player2);
    grid *board_copy = grid_copy(g->board);

    copy->board = board_copy;
    copy->player1 = p1_copy;
    copy->player2 = p2_copy;
    copy->paused = g->paused;

    return copy;
}

void game_destroy(game* g) {
    grid_destroy(g->board);
    player_destroy(g->player1);
    player_destroy(g->player2);
    free(g);
}

#endif