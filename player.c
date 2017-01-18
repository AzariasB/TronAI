/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "player.h"

#ifdef PLAYER_H

player *player_create(int p_id, sfBool is_AI) {
    player *p = malloc(sizeof (player));
    p->id = p_id;
    p->m_direction = DIR_UP;

    sfVector2i position;
    position.x = 0;
    position.y = 0;
    p->position = position;
    return p;
}

void *player_copy(void * ptr) {
    player *p = ptr;
    player *copy = malloc(sizeof (player));

    copy->m_direction = p->m_direction;
    copy->position = p->position;
    copy->id = p->id;
    copy->is_AI = p->is_AI;

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

void player_destroy(void* ptr) {
    player *p = ptr;
    free(p);
}

void player_update(player* p) {
    p->position = utils_update_pos(p->position, p->m_direction);
}

#endif