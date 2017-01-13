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
#define CELL_SIDE 20


#include <stdlib.h>
#include <SFML/Graphics.h>

#include "direction.h"



sfVector2i utils_vector_random(int max_x, int max_y);

sfColor utils_int_to_color(int id);

sfBool utils_vector_same(const sfVector2i v1, const sfVector2i v2);

sfBool utils_is_valid_key(sfKeyCode keyCode);

sfVector2i utils_update_pos(sfVector2i pos, direction dir);

sfRectangleShape *utils_rec_from_xy_color(int x, int y, int color);

#endif /* UTILS_H */

