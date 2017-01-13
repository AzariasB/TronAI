

#include "direction.h"

#ifdef DIRECTION_H

sfVector2i direction_to_vector(direction d) {
    sfVector2i vec = {0,0};
    switch (d) {
        case DIR_UP:
            vec.y = -1;
            break;
        case DIR_DOWN:
            vec.y = 1;
            break;
        case DIR_LEFT:
            vec.x = -1;
            break;
        case DIR_RIGHT:
            vec.x = 1;
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