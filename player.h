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
#include "config.h"

/**
 * A player can be an IA or a human player
 * The player can be dead, it has a position
 * ,a direction and an ID
 */
typedef struct player
{
    sfVector2i position;
    sfBool is_dead;
    sfBool is_AI;
    direction m_direction;
    int id;
} player;

/**
 * Creates the player
 * 
 * @param p_id the player's id
 * @return the created player
 */
player *player_create(int p_id, sfBool is_AI);

/**
 * Copies the given player
 * 
 * @param p the player to copy
 * @return the copied player
 */
void *player_copy(void *ptr);

/**
 * Creates a rectangleshape from the given player position
 * 
 * @param p the player
 * @return the created rectangle
 */
sfRectangleShape *player_to_rect(const player *p, config *g);

/**
 * Destroys the given player
 * 
 * @param p the player to destroy
 */
void player_destroy(void *ptr);

/**
 * Updates the player position
 * given its current position
 * and its direction
 * 
 * @param p the player to update
 */
void player_update(player *p);

/**
 * Returns wether the player is alive
 * 
 * @param p the player to check
 * @return wether the player is alive
 */
sfBool player_is_alive(void *p);

#endif /* PLAYER_H */

