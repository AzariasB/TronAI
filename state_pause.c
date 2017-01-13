



#include "state_pause.h"
#include "game.h"

#ifdef STATE_PAUSE_H

state_pause *state_pause_create() {
    state_pause *s_p = malloc(sizeof (state_pause));
    s_p->super = game_state_create("pause");
    s_p->super = game_state_create("pause");
    s_p->super->cleanup = &state_pause_cleanup;
    s_p->super->pause = &state_pause_pause;
    s_p->super->init = &state_pause_init;
    s_p->super->draw = &state_pause_draw;
    s_p->super->handle_event = &state_pause_handle_event;
    s_p->super->resume = &state_pause_resume;
    s_p->super->update = &state_pause_update;

    s_p->pause_text = utils_create_text("Paused", 110);
    s_p->exit_text = utils_create_text("Exit", 75);
    s_p->resume_texte = utils_create_text("Resume", 75);
    s_p->menu_text = utils_create_text("Menu", 75);

    sfVector2f pause_position = {0, 0};
    sfText_setPosition(s_p->pause_text, pause_position);

    sfVector2f resume_position = {0, 100};
    sfText_setPosition(s_p->resume_texte, resume_position);

    sfVector2f menu_position = {0, 175};
    sfText_setPosition(s_p->menu_text, menu_position);

    sfVector2f exit_position = {0, 250};
    sfText_setPosition(s_p->exit_text, exit_position);



    return s_p;
}

void state_pause_destroy(state_pause *s) {
    game_state_destroy(s->super);
    sfText_destroy(s->exit_text);
    sfText_destroy(s->pause_text);
    sfText_destroy(s->menu_text);
    sfText_destroy(s->resume_texte);
    free(s);
}

void state_pause_init(game *g) {

}

void state_pause_cleanup(game *g) {

}

void state_pause_pause(game *g) {
    g->paused = sfTrue;
}

void state_pause_resume(game *g) {
    g->paused = sfFalse;
}

void state_pause_handle_event(game *g) {
    //Handle click
    sfEvent event;
    while (sfRenderWindow_pollEvent(g->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(g->window);
        } else if (event.type == sfEvtKeyPressed && event.key.code == sfKeySpace) {
            game_change_state(g, "play");
        } else if (event.type == sfEvtMouseButtonPressed) {
            state_pause_button_clicked(g, event.mouseButton);
        } else if (event.type == sfEvtMouseMoved) {
            state_pause_mouse_moved(g->m_state_pause, event.mouseMove);
        }
    }
}

void state_pause_button_clicked(game *g, sfMouseButtonEvent ev) {
    //Check resume
    if (state_pause_in_text(g->m_state_pause->resume_texte, ev.x, ev.y)) {
        game_change_state(g, "play");
        return;
        //change state - return
    } else if (state_pause_in_text(g->m_state_pause->exit_text, ev.x, ev.y)) {
        //Change state -return
        sfRenderWindow_close(g->window);
        return;
    } else if (state_pause_in_text(g->m_state_pause->menu_text, ev.x, ev.y)) {
        // game_change_state(g, "menu");
        return;
    }

}

void state_pause_mouse_moved(state_pause* p, sfMouseMoveEvent ev) {
    state_pause_hilight_text(p->resume_texte, ev);
    state_pause_hilight_text(p->exit_text, ev);
    state_pause_hilight_text(p->menu_text, ev);
}

void state_pause_hilight_text(sfText* t, sfMouseMoveEvent ev) {
    if (state_pause_in_text(t, ev.x, ev.y)) {
        sfText_setColor(t, sfRed);
    } else {
        sfText_setColor(t, sfWhite);
    }
}

sfBool state_pause_in_text(sfText *text, float x, float y) {
    sfFloatRect pos = sfText_getGlobalBounds(text);
    return sfFloatRect_contains(&pos, x, y);
}

void state_pause_update(game *g) {

}

void state_pause_draw(game *g) {
    sfRenderWindow_drawText(g->window, g->m_state_pause->pause_text, NULL);
    sfRenderWindow_drawText(g->window, g->m_state_pause->resume_texte, NULL);
    sfRenderWindow_drawText(g->window, g->m_state_pause->exit_text, NULL);
    sfRenderWindow_drawText(g->window, g->m_state_pause->menu_text, NULL);
}

#endif