/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   grid.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 09:13
 */

#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <SFML/Config.h>
#include <SFML/System/Vector2.h>

#include "player.h"

/**
 * A grid is a two dimensions array
 * It has a width and a height, every element of
 * the grid is initialized with a 0
 * Then as the game goes on, numbers corresponding to user's id are added
 */
typedef struct grid
{
    int ** m_grid;
    int width;
    int height;
} grid;

/**
 * Creates a grid with the given width
 * and given height
 * 
 * @param width the grid's width
 * @param height the grid's height
 * @return the created width
 */
grid *grid_create(int width, int height);

/**
 * Copies the grid
 * 
 * @param to_copy the grid to copy
 * @return the copied grid
 */
grid *grid_copy(const grid *to_copy);

/**
 * Test wether the gird can contain the given position
 * 
 * @param g the grid
 * @param pos the position to test
 * @return wether the position can be in the grid
 */
sfBool grid_contains(const grid *g, sfVector2i pos);

/**
 * Returns the value at the given pos in the given grid
 * If the position is not valid, will print an error
 * and return 0
 * 
 * @param g the grid
 * @param pos the position
 * @return the value of the grid at the given pos
 */
int grid_at(const grid *g, sfVector2i pos);

/**
 * Set the given value at the given position
 * in the given grid
 * If the position is not valid,
 * will print a message and do nothing
 * 
 * @param g the grid to use
 * @param pos the position where to put the value
 * @param value the value to set
 */
void grid_set(grid *g, sfVector2i pos, int value);

/**
 * Destroys the grid
 * 
 * @param g the grid to destroy
 */
void grid_destroy(grid* g);

/**
 * Sets all the cells of the grid
 *  to '-1' (neutral value)
 * 
 * @param g the grid to reset
 */
void grid_reset(grid *g);

/**
 * Removes all the given value from
 * the grid, replace them with -1
 * 
 * @param g the grid to clear
 * @param val the value to remove
 */
void grid_clear_value(grid *g, int val);

/**
 * Returns wether the grid is empty 
 * (value = -1) at the given position
 * if the position is out of the grid, returns true
 * 
 * @param g the grid
 * @param pos the position where to check
 * @return wether the grid is empty at the given position
 */
sfBool grid_is_empty(grid *g, sfVector2i pos);

/**
 * Returns true if there is the
 * given value at the given position
 * if the position is out of border
 * returns false
 * 
 * @param g the grid
 * @param pos the position that may contain the value
 * @param val the value that might be at the given position
 * @return wether the grid contains the given value at the given position
 */
sfBool grid_equals(const grid *g, sfVector2i pos, int val);

/**
 * Prints the grid
 * 
 * @param g
 */
void grid_print(const grid *g);

#endif /* GRID_H */

