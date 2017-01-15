

#include "state_menu.h"
#include "game.h"

#ifdef STATE_MENU_H

state_menu *state_menu_create() {
    state_menu *menu = malloc(sizeof (state_menu));
    menu->super = game_state_create("menu");

    menu->super->pause = &state_menu_pause;
    menu->super->init = &state_menu_init;
    menu->super->draw = &state_menu_draw;
    menu->super->handle_event = &state_menu_handle_event;
    menu->super->resume = &state_menu_resume;
    menu->super->update = &state_menu_update;

    menu->text_menu = utils_create_text("Menu", 110);
    menu->text_play = utils_create_text("Play", 75);
    menu->text_exit = utils_create_text("Exit", 75);

    sfVector2f menu_pos = {0, 0};
    sfText_setPosition(menu->text_menu, menu_pos);

    sfVector2f play_pos = {0, 100};
    sfText_setPosition(menu->text_play, play_pos);


    sfVector2f exit_pos = {0, 175};
    sfText_setPosition(menu->text_exit, exit_pos);

    menu->music = sfMusic_createFromFile("menu_music.ogg");

    return menu;
}

void state_menu_init(game *g) {

}

void state_menu_pause(game *g) {
    state_menu *m = g->st_manager->st_menu;
    sfMusic_stop(m->music);
}

void state_menu_resume(game *g) {
    state_menu *m = g->st_manager->st_menu;
    sfMusic_play(m->music);
}

void state_menu_handle_event(game *g) {
    //Handle click
    sfEvent event;
    state_menu *st_menu = g->st_manager->st_menu;
    while (sfRenderWindow_pollEvent(g->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(g->window);
        } else if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeySpace) {
                game_change_state(g, "play");
            } else if (event.key.code == sfKeyM) {
                utils_toggle_music(st_menu->music);
            }
        } else if (event.type == sfEvtMouseButtonPressed) {
            state_menu_button_clicked(g, event.mouseButton);
        } else if (event.type == sfEvtMouseMoved) {
            state_menu_mouse_moved(g->st_manager->st_menu, event.mouseMove);
        }
    }
}

void state_menu_mouse_moved(state_menu *s, sfMouseMoveEvent ev) {
    utils_hilight_text(s->text_play, ev);
    utils_hilight_text(s->text_exit, ev);
}

void state_menu_button_clicked(game* g, sfMouseButtonEvent ev) {
    //Check resume
    state_menu *st_menu = g->st_manager->st_menu;

    if (utils_text_contains(st_menu->text_play, ev.x, ev.y)) {
        game_change_state(g, "play");
    } else if (utils_text_contains(st_menu->text_exit, ev.x, ev.y)) {
        sfRenderWindow_close(g->window);
    }

    state_pause *st_pause = g->st_manager->st_pause;
    if (utils_text_contains(st_pause->resume_texte, ev.x, ev.y)) {
        game_change_state(g, "play");
        return;
        //change state - return
    } else if (utils_text_contains(st_pause->exit_text, ev.x, ev.y)) {
        //Change state -return
        sfRenderWindow_close(g->window);
        return;
    } else if (utils_text_contains(st_pause->menu_text, ev.x, ev.y)) {
        game_change_state(g, "menu");
        return;
    }
}

void state_menu_draw(game* g) {
    state_menu *m = g->st_manager->st_menu;
    sfRenderWindow_drawText(g->window, m->text_menu, NULL);
    sfRenderWindow_drawText(g->window, m->text_play, NULL);
    sfRenderWindow_drawText(g->window, m->text_exit, NULL);
}

void state_menu_update(game *g) {

}

state_menu *state_menu_copy(state_menu* s) {
    state_menu *copy = malloc(sizeof (state_menu));
    copy->super = game_state_copy(s->super);
    copy->text_exit = sfText_copy(s->text_exit);
    copy->text_menu = sfText_copy(s->text_menu);
    copy->text_play = sfText_copy(s->text_play);
    copy->music = sfMusic_createFromFile("menu_music.ogg");

    return copy;
}

void state_menu_destroy(state_menu *s) {
    game_state_destroy(s->super);
    sfText_destroy(s->text_menu);
    sfText_destroy(s->text_play);
    sfText_destroy(s->text_exit);
    sfMusic_destroy(s->music);
    free(s);
}

#endif
