
/* 
 * File:   AI.h
 * Author: azarias
 *
 * Created on 18 janvier 2017, 16:20
 */

#ifndef AI_H
#define AI_H


#include "direction.h"
#include "grid.h"
#include "list.h"

/**
 * Called to make an ia play
 * The grid given is a copy of the game grid
 * the given list of the players is a copy
 * of the game's list
 * The given id is the ID of the IA to play
 * The grid and the player list must NOT
 * be destroyed (will be destroyed in the main loop)
 * 
 * @param grid the game's grid
 * @param players the game's player
 * @param my_id the id of the IA to play
 * @return 
 */
direction ia_play(grid *grid, list *players, int my_id) {
    //TODO : IMPLEMENT
    return DIR_DOWN;
}


#endif /* AI_H */

