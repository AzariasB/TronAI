/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 10:40
 */

#ifndef UTILS_H
#define UTILS_H

#define BOARD_WIDTH 30
#define BOARD_HEIGHT 20

// The number of pixel for a single cell
#define CELL_SIDE 32


#define SCREEN_WIDTH CELL_SIDE * BOARD_WIDTH
#define SCREEN_HEIGHT CELL_SIDE * BOARD_HEIGHT

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <string.h>
#include <SFML/Audio/Types.h>

#include "direction.h"

/**
 * Test wether two strings are the same
 * 
 * @param a first string
 * @param b second string
 * @return wether the two strings are the same
 */
#define SAME(a,b)(strcmp(a,b) == 0)

/**
 * Generates a vector :
 *  - x between 0 and max_x
 * - y between 0 and max_y
 * 
 * @param max_x the max x of the vector
 * @param max_y the max y of the vector
 * @return the vector generated
 */
sfVector2i utils_vector_random(int max_x, int max_y);

/**
 * Returns a sfColor from a number
 * This is a simple switch statement,
 * used to assign colors to players
 * 
 * @param id the color id
 * @return the color from the given id
 */
sfColor utils_int_to_color(int id);

/**
 * Test wether two vectors are equals (same x and same y)
 * 
 * @param v1 the first vector
 * @param v2 the second vector
 * @return 
 */
sfBool utils_vector_same(const sfVector2i v1, const sfVector2i v2);

/**
 * Returns wether the given keycode is a 'valid' one
 * A valid key code is a keycode that will allow the player to change its direction
 *  namely, keys : up,down, left, right
 * 
 * @param keyCode the keyCode
 * @return wether the given keycode is a 'valid' one
 */
sfBool utils_is_valid_key(sfKeyCode keyCode);

/**
 * Update a position using the givne direction
 * for example, if the direction is up, the position's y will
 * be substracted by one
 * 
 * @param pos the old position
 * @param dir the direction
 * @return the new direction
 */
sfVector2i utils_update_pos(sfVector2i pos, direction dir);

/**
 * Creates a rectangleShape, at the given x,y position
 * and with the given color
 * 
 * @param x the x position of the rectangle
 * @param y the y position of the rectangle
 * @param color the color of the rectangle
 * @return 
 */
sfRectangleShape *utils_rec_from_xy_color(int x, int y, int color);

/**
 * Creates a text with the default font of the game (tron font)
 * and with the given charsize
 * 
 * @param content
 * @param charSize
 * @return 
 */
sfText *utils_create_text(char *content, int charSize);

/**
 * Test wether the x and y coordinates are in the
 * text global bounds
 * 
 * @param text the text to test 
 * @param x the x coordinate
 * @param y the y coordinate
 * @return wether the coordinates are in the text global bounds
 */
sfBool utils_text_contains(sfText *text, float x, float y);

/**
 * Hilights the given text if the position of the mouse
 * is in the text, otherwise, un-hilight it
 * 
 * @param text the text to (un)hilight
 * @param ev the mouseevent
 */
void utils_hilight_text(sfText *text, sfMouseMoveEvent ev);

/**
 * Toggles the music
 * (pause/unpause)
 * 
 * @param music the music to toggle
 */
void utils_toggle_music(sfMusic *music);

#endif /* UTILS_H */

