
#include <string.h>

#include "game.h"
#include "game_state.h"


#ifdef GAME_STATE_H

game_state *game_state_create(char* name) {
    game_state *state = malloc(sizeof (game_state));
    state->name = name;
    return state;
}

game_state *game_state_copy(const game_state* to_copy) {
    printf("game state copy\n");
    game_state *copy = malloc(sizeof(game_state));
    memcpy(copy, to_copy, sizeof(*copy));

    return copy;
}

void game_state_destroy(game_state* s) {
    free(s);
}

#endif