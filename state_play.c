

#include "game.h"
#include "state_play.h"
#include "AI.h"


#ifdef STATE_PLAY_H

state_play *state_play_create() {
    state_play *state = malloc(sizeof (state_play));
    state->super = game_state_create("play");
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
    sfVector2f g_scale = {CELL_SIDE / s_bouds.width, CELL_SIDE / s_bouds.height};
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

void state_play_draw(game* g) {
    //                sfVector2f glow_position = {CELL_SIDE * g->player1->position.x, CELL_SIDE * g->player1->position.y};
    //    state_play *st_play = g->st_manager->st_play;
    for (int y = 0; y < g->board->height; y++) {
        for (int x = 0; x < g->board->width; x++) {
            int m_v = g->board->m_grid[y][x];
            for (int p_index = 0; p_index < g->players->size; p_index++) {
                player *m_player = list_get(g->players, p_index);
                if (m_v == m_player->id) {
                    sfRectangleShape *shape = utils_rec_from_xy_color(x, y, m_player->id);
                    sfRenderWindow_drawRectangleShape(g->window, shape, NULL);
                    break;
                }
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
        list *l = g->players;
        for (int i = 0; i < l->size; i++) {
            player *p = list_get(l, i);
            if (p->is_AI) {
                printf("IA playing\n");
                grid *g_cpy = grid_copy(g->board);
                list *p_copy = list_copy(l, &player_copy);
                p->m_direction = ia_play(g_cpy, p_copy, p->id);
                grid_destroy(g_cpy);
                list_destroy(l, &player_destroy);
            }
            player_update(p);
            if (game_player_is_dead(g, p)) {
                g->ended = sfTrue;
                g->paused = sfTrue;
                printf("Someone's dead : player number %d\n", p->id);
            }else{
                game_add_player_pos(g, p);
            }
        }
    }

}

void state_play_handle_event(game* g, sfEvent event) {
    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeySpace) {
            game_change_state(g, "pause");
        } else if (utils_is_valid_key(event.key.code)) {
            g->paused = sfFalse;
            player *human = list_get(g->players, 0); //The first player is the human player
            human->m_direction = direction_from_key_code(event.key.code);
        }
    }
}


#endif