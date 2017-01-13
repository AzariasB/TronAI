


#include "game.h"
#include "game_state.h"
#include "state_play.h"
#include "state_pause.h"


#ifdef GAME_H

game *game_create() {
    game *g = malloc(sizeof (game));

    player *p1 = player_create(1);
    player *p2 = player_create(2);
    grid *board = grid_create(BOARD_WIDTH, BOARD_HEIGHT);

    g->player1 = p1;
    g->player2 = p2;
    g->board = board;
    g->ended = sfFalse;
    g->paused = sfTrue;
    g->m_state_play = state_play_create();
    g->m_state_pause = state_pause_create();

    g->current_state = g->m_state_play->super;

    return g;
}

sfVector2i game_window_size(const game* g) {
    sfVector2i size = {g->board->width * CELL_SIDE, g->board->height * CELL_SIDE};
    return size;
}

void game_main_loop(game* g, sfRenderWindow *window) {
    (g->current_state->handle_event)(g);
    (g->current_state->handle_event)(g);
    (g->current_state->update)(g);
    sfRenderWindow_clear(window, sfBlack);
    (g->current_state->draw)(g);
    sfRenderWindow_display(window);

}

sfBool game_player_is_dead(game* g, player* p) {
    if (p->is_dead || !grid_contains(g->board, p->position)) {
        return sfTrue;
    }
    return !game_cell_is_empty(g, p->position);
}

sfBool game_cell_is_empty(game* g, sfVector2i pos) {
    if (!grid_contains(g->board, pos)) {
        return sfFalse;
    }
    return g->board->m_grid[pos.y][pos.x] == 0;
}

void game_init_player_pos(game* g) {
    g->player1->position = utils_vector_random(g->board->width, g->board->height);
    do {
        g->player2->position = utils_vector_random(g->board->width, g->board->height);
    } while (utils_vector_same(g->player1->position, g->player2->position));
    game_add_player_pos(g, g->player1);
    game_add_player_pos(g, g->player2);
}

void game_add_player_pos(game* g, player* p) {
    g->board->m_grid[p->position.y][p->position.x] = p->id;
}

void game_change_state(game* g, char* state_name) {
    //Change with looping in array
    if (strcmp(state_name, "play") == 0) {
        (g->current_state)->pause(g);
        g->current_state = g->m_state_play->super;
        (g->current_state)->resume(g);
    } else {
        (g->current_state)->pause(g);
        g->current_state = g->m_state_pause->super;
        (g->current_state)->resume(g);
    }
}

game *game_copy(const game* g) {
    game *copy = malloc(sizeof (game));

    player *p1_copy = player_copy(g->player1);
    player *p2_copy = player_copy(g->player2);
    grid *board_copy = grid_copy(g->board);
    game_state *state_copy = game_state_copy(g->current_state);

    copy->board = board_copy;
    copy->player1 = p1_copy;
    copy->player2 = p2_copy;
    copy->paused = g->paused;
    copy->current_state = state_copy;

    return copy;
}

void game_destroy(game* g) {
    grid_destroy(g->board);
    player_destroy(g->player1);
    player_destroy(g->player2);
    game_state_destroy(g->current_state);
    free(g);
}

#endif