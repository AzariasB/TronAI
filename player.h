/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 09:12
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "utils.h"
#include "direction.h"

typedef struct player{
	sfVector2i position;
        sfBool is_dead;
	direction m_direction;
	int id;
} player;

player *player_create(int p_id);

player *player_copy(const player *p);

sfRectangleShape *player_to_rect(const player *p);


void player_destroy(player *p);

#endif /* PLAYER_H */

