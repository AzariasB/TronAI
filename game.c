


#include "game.h"
#include "game_state.h"
#include "state_play.h"
#include "state_pause.h"

#ifdef GAME_H

game *game_create() {
    game *g = utils_safe_malloc(sizeof(game), "game creation");

    g->players = list_create();
    player *p1 = player_create(1, sfFalse);
    player *p2 = player_create(2, sfTrue);
    player *p3 = player_create(3, sfTrue);
    list_push(g->players, p1);
    list_push(g->players, p2);
    list_push(g->players, p3);
    grid *board = grid_create(BOARD_WIDTH, BOARD_HEIGHT);

    g->board = board;
    g->ended = sfFalse;
    g->paused = sfTrue;
    g->st_manager = state_manager_create();
    g->audio_manager = audio_manager_create();
    (*g->st_manager->current_state->resume)(g);

    g->background_texture = sfTexture_createFromFile("background.png", NULL);
    g->background_sprite = sfSprite_create();

    sfSprite_setTexture(g->background_sprite, g->background_texture, sfFalse);

    sfFloatRect background_bounds = sfSprite_getGlobalBounds(g->background_sprite);
    sfVector2f background_scale = {(SCREEN_WIDTH) / background_bounds.width, (SCREEN_HEIGHT) / background_bounds.height};
    sfSprite_setScale(g->background_sprite, background_scale);

    g->background_glow_texture = sfTexture_createFromFile("glow.png", NULL);
    g->background_glow_sprite = sfSprite_create();

    sfSprite_setTexture(g->background_glow_sprite, g->background_glow_texture, sfFalse);
    sfFloatRect glow_bounds = sfSprite_getGlobalBounds(g->background_glow_sprite);
    sfVector2f glow_scale = {SCREEN_WIDTH / glow_bounds.width, SCREEN_HEIGHT / glow_bounds.height};
    sfSprite_setScale(g->background_glow_sprite, glow_scale);

    return g;
}

sfVector2i game_window_size(const game* g) {
    sfVector2i size = {g->board->width * CELL_SIDE, g->board->height * CELL_SIDE};
    return size;
}

void game_main_loop(game* g) {
    sfEvent ev;
    while (sfRenderWindow_pollEvent(g->window, &ev)) {
        if (ev.type == sfEvtClosed) {
            sfRenderWindow_close(g->window);
        } else if (ev.type == sfEvtKeyPressed && ev.key.code == sfKeyM) {
            //Toggle game music
        } else {
            (*g->st_manager->current_state->handle_event)(g, ev);

        }
    }
    (*g->st_manager->current_state->update)(g);
    sfRenderWindow_clear(g->window, sfBlack);
    sfRenderWindow_drawSprite(g->window, g->background_sprite, NULL);
    sfRenderWindow_drawSprite(g->window, g->background_glow_sprite, NULL);
    (*g->st_manager->current_state->draw)(g);
    sfRenderWindow_display(g->window);

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
    for (int i = 0; i < g->players->size; i++) {
        sfBool already_taken = sfFalse;
        sfVector2i rand_pos = utils_vector_random(g->board->width, g->board->height);
        do {
            already_taken = sfFalse;
            rand_pos = utils_vector_random(g->board->width, g->board->height);
            for (int j = 0; j < i; j++) {
                player *p = list_get(g->players, j);
                already_taken = utils_vector_same(p->position, rand_pos) || already_taken;

            }
        } while (already_taken);
        player *p = list_get(g->players, i);
        p->position = rand_pos;
        grid_set(g->board, p->position, p->id);
    }
}

void game_add_player_pos(game* g, player* p) {
    grid_set(g->board, p->position, p->id);
}

void game_change_state(game* g, char* state_name) {
    state_manager_change_state(g->st_manager, g, state_name);
}

game *game_copy(const game* g) {
    game *copy = utils_safe_malloc(sizeof(game), "Copying game");
    copy->background_texture = sfTexture_copy(g->background_texture);
    copy->background_sprite = sfSprite_copy(g->background_sprite);
    copy->background_glow_texture = sfTexture_copy(g->background_glow_texture);
    copy->background_glow_sprite = sfSprite_copy(g->background_glow_sprite);
    copy->board = grid_copy(g->board);
    copy->players = list_copy(g->players, &player_copy);
    copy->paused = g->paused;
    copy->ended = g->ended;
    copy->st_manager = state_manager_copy(g->st_manager);
    copy->audio_manager = NULL; //can't copy audio_manager because can't copy sfMusic
    copy->window = g->window;
    return copy;
}

void game_destroy(game* g) {
    grid_destroy(g->board);
    list_destroy(g->players, &player_destroy);
    state_manager_destroy(g->st_manager);
    if (g->audio_manager != NULL) {
        audio_manager_destroy(g->audio_manager);
    }
    sfSprite_destroy(g->background_sprite);
    sfTexture_destroy(g->background_texture);
    sfSprite_destroy(g->background_glow_sprite);
    sfTexture_destroy(g->background_glow_texture);
    free(g);
}

#endif
