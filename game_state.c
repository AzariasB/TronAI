
#include <string.h>

#include "game.h"
#include "game_state.h"


#ifdef GAME_STATE_H

game_state *game_state_create(char* name) {
    game_state *state = utils_safe_malloc(sizeof(game_state), "Creating game state");
    state->name = name;
    return state;
}

game_state *game_state_copy(const game_state* to_copy) {
    game_state *copy = utils_safe_malloc(sizeof(game_state), "copying game state");
    memcpy(copy, to_copy, sizeof(*copy));
    return copy;
}

void game_state_destroy(game_state* s) {
    free(s);
}

#endif