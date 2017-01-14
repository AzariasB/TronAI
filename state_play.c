

#include "game.h"
#include "state_play.h"


#ifdef STATE_PLAY_H

state_play *state_play_create() {
    state_play *state = malloc(sizeof (state_play));
    state->super = game_state_create("play");
    state->super->cleanup = &state_play_cleanup;
    state->super->pause = &state_play_pause;
    state->super->init = &state_play_init;
    state->super->draw = &state_play_draw;
    state->super->handle_event = &state_play_handle_event;
    state->super->resume = &state_play_resume;
    state->super->update = &state_play_update;


    return state;
}

state_play* state_play_copy(state_play* s) {
    state_play *copy = malloc(sizeof (state_play));
    copy->super = game_state_copy(s->super);
    return copy;
}

void state_play_destroy(state_play* s) {
    game_state_destroy(s->super);
    free(s);
}

void state_play_init(game* g) {

}

void state_play_cleanup(game* g) {

}

void state_play_draw(game* g) {
    for (int y = 0; y < g->board->height; y++) {
        for (int x = 0; x < g->board->width; x++) {
            int m_v = g->board->m_grid[y][x];
            //            printf("x : %d, y: %d, v:%d\n", x, y, m_v);
            if (m_v == g->player1->id) {
                sfRectangleShape *shape = utils_rec_from_xy_color(x, y, g->player1->id);
                sfRenderWindow_drawRectangleShape(g->window, shape, NULL);


            } else if (m_v == g->player2->id) {
                sfRectangleShape *shape = utils_rec_from_xy_color(x, y, g->player2->id);
                sfRenderWindow_drawRectangleShape(g->window, shape, NULL);
            }
        }
    }
}

void state_play_pause(game* g) {
    g->paused = sfTrue;
}

void state_play_resume(game* g) {
    g->paused = sfTrue; //Wait for user input
}

void state_play_update(game* g) {
    if (!g->paused) {
        sfVector2i nw_pos = utils_update_pos(g->player1->position, g->player1->m_direction);
        g->player1->position = nw_pos;
        if (game_player_is_dead(g, g->player1)) {
            printf("Tu es mort\n");
            g->paused = sfTrue;
        } else {
            game_add_player_pos(g, g->player1);
        }
    }

}

void state_play_handle_event(game* g) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(g->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(g->window);
        } else if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeySpace) {
                game_change_state(g, "pause");
            } else if (utils_is_valid_key(event.key.code)) {
                g->paused = sfFalse;
                g->player1->m_direction = direction_from_key_code(event.key.code);
            }
        }
    }
}


#endif