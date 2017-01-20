/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "player.h"
#include "config.h"

#ifdef PLAYER_H

player *player_create(int p_id, sfBool is_AI)
{
	player *p = utils_safe_malloc(sizeof(player), "Creating player");
	p->id = p_id;
	p->m_direction = DIR_UP;
	p->is_AI = is_AI;
	p->is_dead = sfFalse;
	sfVector2i position;
	position.x = 0;
	position.y = 0;
	p->position = position;
	return p;
}

void *player_copy(void * ptr)
{
	player *p = ptr;
	player *copy = utils_safe_malloc(sizeof(player), "Copying player");

	copy->m_direction = p->m_direction;
	copy->position = p->position;
	copy->id = p->id;
	copy->is_AI = p->is_AI;
	copy->is_dead = p->is_dead;

	return copy;
}

sfRectangleShape *player_to_rect(const player* p, config *g)
{
	sfRectangleShape *rect = sfRectangleShape_create();
	int cell_side = config_get_int(main_configuration, "CELL_SIDE", 16);
	printf("Player %d, cell side : %d\n", p->id, cell_side);
	sfVector2f size;
	size.x = (float) cell_side;
	size.y = (float) cell_side;

	sfRectangleShape_setSize(rect, size);

	sfVector2f position;
	position.x = cell_side * p->position.x;
	position.y = cell_side * p->position.y;

	sfRectangleShape_setPosition(rect, position);

	sfColor rectColor = utils_int_to_color(p->id);
	sfRectangleShape_setFillColor(rect, rectColor);

	return rect;
}

void player_destroy(void* ptr)
{
	player *p = ptr;
	free(p);
}

void player_update(player* p)
{
	p->position = utils_update_pos(p->position, p->m_direction);
}

#endif