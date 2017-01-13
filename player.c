/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "player.h"

#ifdef PLAYER_H

player *player_create(int p_id) {
    player *p = malloc(sizeof (player));
    p->id = p_id;
    p->m_direction = DIR_UP;

    sfVector2i position;
    position.x = 0;
    position.y = 0;
    p->position = position;
    return p;
}

player *player_copy(const player* p) {
    player *copy = malloc(sizeof (player));

    copy->m_direction = p->m_direction;
    copy->position = p->position;
    copy->id = p->id;

    return copy;
}

sfRectangleShape *player_to_rect(const player* p) {
    sfRectangleShape *rect = sfRectangleShape_create();

    sfVector2f size;
    size.x = (float) CELL_SIDE;
    size.y = (float) CELL_SIDE;

    sfRectangleShape_setSize(rect, size);

    sfVector2f position;
    position.x = CELL_SIDE * p->position.x;
    position.y = CELL_SIDE * p->position.y;

    sfRectangleShape_setPosition(rect, position);

    sfColor rectColor = utils_int_to_color(p->id);
    sfRectangleShape_setFillColor(rect, rectColor);

    return rect;
}

void player_destroy(player* p) {
    free(p);
}

#endif