

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
    state->music = sfMusic_createFromFile("play_music.ogg");
    sfMusic_setLoop(state->music, sfTrue);

    state->glow_texture = sfTexture_createFromFile("glow.png", NULL);
    state->glow_sprite = sfSprite_create();

    sfSprite_setTexture(state->glow_sprite, state->glow_texture, sfFalse);

    sfVector2f glow_position = {0, 0};
    sfSprite_setPosition(state->glow_sprite, glow_position);


    sfFloatRect s_bouds = sfSprite_getGlobalBounds(state->glow_sprite);
    sfVector2f g_scale = { CELL_SIDE / s_bouds.width, CELL_SIDE / s_bouds.height};
    sfSprite_setScale(state->glow_sprite, g_scale);

    return state;
}

state_play* state_play_copy(state_play* s) {
    state_play *copy = malloc(sizeof (state_play));
    copy->super = game_state_copy(s->super);
    copy->music = sfMusic_createFromFile("play_music.ogg");
    copy->glow_texture = sfTexture_copy(s->glow_texture);
    copy->glow_sprite = sfSprite_copy(s->glow_sprite);
    return copy;
}

void state_play_destroy(state_play* s) {
    game_state_destroy(s->super);
    sfMusic_destroy(s->music);
    sfSprite_destroy(s->glow_sprite);
    sfTexture_destroy(s->glow_texture);
    free(s);
}

void state_play_init(game* g) {

}

void state_play_cleanup(game* g) {

}

void state_play_draw(game* g) {
    state_play *st_play = g->st_manager->st_play;
        for (int y = 0; y < g->board->height; y++) {
        for (int x = 0; x < g->board->width; x++) {
            int m_v = g->board->m_grid[y][x];
            //            printf("x : %d, y: %d, v:%d\n", x, y, m_v);
            if (m_v == g->player1->id) {
                sfVector2f glow_position = {CELL_SIDE * g->player1->position.x, CELL_SIDE * g->player1->position.y};
                sfSprite_setPosition(st_play->glow_sprite, glow_position);

                sfRectangleShape *shape = utils_rec_from_xy_color(x, y, g->player1->id);
                sfRenderWindow_drawRectangleShape(g->window, shape, NULL);
                sfRenderWindow_drawSprite(g->window, st_play->glow_sprite, NULL);

            } else if (m_v == g->player2->id) {
                sfRectangleShape *shape = utils_rec_from_xy_color(x, y, g->player2->id);
                sfRenderWindow_drawRectangleShape(g->window, shape, NULL);
            }
        }
    }
}

void state_play_pause(game* g) {
    g->paused = sfTrue;
    sfMusic_pause(g->st_manager->st_play->music);
}

void state_play_resume(game* g) {
    g->paused = sfTrue; //Wait for user input
    sfMusic_play(g->st_manager->st_play->music);
}

void state_play_update(game* g) {
    if (!g->paused && !g->ended) {
        sfVector2i nw_pos = utils_update_pos(g->player1->position, g->player1->m_direction);
        g->player1->position = nw_pos;
        if (game_player_is_dead(g, g->player1)) {
            printf("Tu es mort\n");
            g->ended = sfTrue;
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
            } else if (event.key.code == sfKeyM) {
                utils_toggle_music(g->st_manager->st_play->music);
            } else if (utils_is_valid_key(event.key.code)) {
                g->paused = sfFalse;
                g->player1->m_direction = direction_from_key_code(event.key.code);
            }
        }
    }
}


#endif