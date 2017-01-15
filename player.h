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

/**
 * A player can be an IA or a human player
 * The player can be dead, it has a position
 * ,a direction and an ID
 */
typedef struct player{
	sfVector2i position;
        sfBool is_dead;
	direction m_direction;
	int id;
} player;

/**
 * Creates the player
 * 
 * @param p_id the player's id
 * @return the created player
 */
player *player_create(int p_id);

/**
 * Copies the given player
 * 
 * @param p the player to copy
 * @return the copied player
 */
player *player_copy(const player *p);

/**
 * Creates a rectangleshape from the given player position
 * 
 * @param p the player
 * @return the created rectangle
 */
sfRectangleShape *player_to_rect(const player *p);

/**
 * Destroys the given player
 * 
 * @param p the player to destroy
 */
void player_destroy(player *p);

#endif /* PLAYER_H */

