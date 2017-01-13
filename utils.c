

#include "utils.h"

#ifdef UTILS_H

sfVector2i utils_vector_random(int max_x, int max_y) {
    sfVector2i vect;
    vect.x = rand() % max_x;
    vect.y = rand() % max_y;
    return vect;
}

sfBool utils_vector_same(const sfVector2i v1, const sfVector2i v2) {
    return v1.x == v2.x && v1.y == v2.y;
}

sfColor utils_int_to_color(int id) {
    //Add more color if more players
    switch (id) {
        case 1:
            return sfBlue;
        case 2:
            return sfRed;
        default:
            return sfYellow;
    }
}

sfBool utils_is_valid_key(sfKeyCode keyCode) {
    return keyCode == sfKeyUp || keyCode == sfKeyDown || keyCode == sfKeyLeft || keyCode == sfKeyRight;
}

sfVector2i utils_update_pos(sfVector2i pos, direction dir) {
    sfVector2i vec;
    switch (dir) {
        case DIR_UP:
            vec = {pos.x, pos.y - 1};
            break;
        case DIR_DOWN:
            vec ={pos.x, pos.y + 1};
            break;
        case DIR_LEFT:
            vec = {pos.x - 1, pos.y};
            break;
        case DIR_RIGHT:
            vec = {pos.x + 1, pos.y};
    }
    return vec;
}

#endif