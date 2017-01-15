


#include "state_manager.h"
#include "game.h"

#ifdef STATE_MANAGER_H

state_manager *state_manager_create() {
    state_manager *m = malloc(sizeof (state_manager));
    m->st_menu = state_menu_create();
    m->st_pause = state_pause_create();
    m->st_play = state_play_create();

    m->current_state = m->st_menu->super;

    return m;
}

void state_manager_destroy(state_manager *m) {
    state_menu_destroy(m->st_menu);
    state_play_destroy(m->st_play);
    state_pause_destroy(m->st_pause);
    free(m);
}

state_manager *state_manager_copy(state_manager *m) {
    state_manager *copy = malloc(sizeof (state_manager));
    copy->st_menu = state_menu_copy(m->st_menu);
    copy->st_play = state_play_copy(m->st_play);
    copy->st_pause = state_pause_copy(m->st_pause);

    copy->current_state = copy->st_menu->super;
    return copy;
}

void state_manager_change_state(state_manager* m, game *g, char* name) {
    game_state *nw_state = NULL;
    if (SAME(name, "play")) {
        nw_state = m->st_play->super;
    } else if (SAME(name, "pause")) {
        nw_state = m->st_pause->super;
    } else {
        nw_state = m->st_menu->super;
    }

    (m->current_state)->pause(g);
    m->current_state = nw_state;
    (m->current_state)->resume(g);
}

#endif