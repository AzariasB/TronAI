

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
    sfVector2i vec = {pos.x, pos.y};
    switch (dir) {
        case DIR_UP:
            vec.y--;
            break;
        case DIR_DOWN:
            vec.y++;
            break;
        case DIR_LEFT:
            vec.x--;
            break;
        case DIR_RIGHT:
            vec.x++;
    }
    return vec;
}

sfRectangleShape *utils_rec_from_xy_color(int x, int y, int color) {
    sfRectangleShape *rect = sfRectangleShape_create();
    sfRectangleShape_setFillColor(rect, utils_int_to_color(color));
    sfVector2f rectSize = {CELL_SIDE, CELL_SIDE};
    sfRectangleShape_setSize(rect, rectSize);

    sfVector2f rectPos = {CELL_SIDE*x, CELL_SIDE * y};
    sfRectangleShape_setPosition(rect, rectPos);
    return rect;
}

sfText *utils_create_text(char* content, int charSize) {
    sfText *text = sfText_create();

    sfText_setCharacterSize(text, charSize);
    sfText_setString(text, content);

    sfFont *tron_font = sfFont_createFromFile("tron.ttf");
    sfText_setFont(text, tron_font);
    return text;
}

sfBool utils_text_contains(sfText* text, float x, float y) {
    sfFloatRect bound = sfText_getGlobalBounds(text);
    return sfFloatRect_contains(&bound, x, y);
}

void utils_hilight_text(sfText *text, sfMouseMoveEvent ev) {
    if (utils_text_contains(text, ev.x, ev.y)) {
        sfText_setColor(text, sfRed);
    } else {
        sfText_setColor(text, sfWhite);
    }
}
#endif