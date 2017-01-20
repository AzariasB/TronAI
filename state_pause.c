



#include "state_pause.h"
#include "game.h"

#ifdef STATE_PAUSE_H

void state_pause_resume_clicked(game *g, sfEvent ev) {
    game_change_state(g, "play");
}

void state_pause_exit_clicked(game *g, sfEvent ev) {
    game_exit(g);
}

void state_pause_menu_clicked(game *g, sfEvent ev) {
    //reset game
    game_change_state(g, "menu");
}

state_pause *state_pause_create() {
    state_pause *s_p = utils_safe_malloc(sizeof (state_pause), "Creating state pause");
    s_p->super = game_state_create("pause");
    s_p->super->pause = &state_pause_pause;
    s_p->super->init = &state_pause_init;
    s_p->super->draw = &state_pause_draw;
    s_p->super->handle_event = &state_pause_handle_event;
    s_p->super->resume = &state_pause_resume;
    s_p->super->update = &state_pause_update;

    s_p->menu = menu_create("Pause");
    menu_add_text(s_p->menu, "Resume", &state_pause_resume_clicked);
    menu_add_text(s_p->menu, "Menu", &state_pause_menu_clicked);
    menu_add_text(s_p->menu, "Exit", &state_pause_exit_clicked);

    return s_p;
}

void state_pause_init(game *g) {

}

void state_pause_pause(game *g) {
    g->paused = sfTrue;
}

void state_pause_resume(game *g) {
    g->paused = sfFalse;
}

void state_pause_handle_event(game *g, sfEvent event) {
    //Handle click
    state_pause *p = g->st_manager->st_pause;
    menu_handle_event(p->menu, g, event);

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeySpace) {
        game_change_state(g, "play");
    }
}

void state_pause_update(game *g) {

}

void state_pause_draw(game *g) {
    state_pause *st_pause = g->st_manager->st_pause;
    menu_draw(st_pause->menu, g->window);
    //    sfRenderWindow_drawText(g->window, st_pause->pause_text, NULL);
    //    sfRenderWindow_drawText(g->window, st_pause->resume_texte, NULL);
    //    sfRenderWindow_drawText(g->window, st_pause->exit_text, NULL);
    //    sfRenderWindow_drawText(g->window, st_pause->menu_text, NULL);
}

state_pause *state_pause_copy(state_pause* s) {
    state_pause *copy = utils_safe_malloc(sizeof (state_pause), "Copying state pause");
    copy->super = game_state_copy(s->super);
    copy->menu = menu_copy(s->menu);
    return copy;
}

void state_pause_destroy(state_pause *s) {
    game_state_destroy(s->super);
    menu_destroy(s->menu);
    free(s);
    s = 0;
}

#endif