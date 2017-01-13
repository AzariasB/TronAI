

#include "direction.h"

#ifdef DIRECTION_H

sfVector2i direction_to_vector(direction d) {
    sfVector2i vec;
    switch (d) {
        case DIR_UP:
            vec = {0, -1};
            break;
        case DIR_DOWN:
            vec = {0, 1};
            break;
        case DIR_LEFT:
            vec = {-1, 0};
            break;
        case DIR_RIGHT:
            vec = {1, 0};
            break;
    }
    return vec;
}

direction direction_from_key_code(const sfKeyCode key_c) {
    if (key_c == sfKeyUp) {
        return DIR_UP;
    } else if (key_c == sfKeyDown) {
        return DIR_DOWN;
    } else if (key_c == sfKeyLeft) {
        return DIR_LEFT;
    } else if (key_c == sfKeyRight) {
        return DIR_RIGHT;
    }
    // exception ?
    return DIR_UP;
}

#endif