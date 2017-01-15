/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   direction.h
 * Author: azarias
 *
 * Created on 13 janvier 2017, 11:29
 */

#ifndef DIRECTION_H
#define DIRECTION_H

#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>

/**
 * an enum for the available direction of the player
 * The player might go :
 *  - Up (y - 1)
 *  - Down (y + 1)
 *  - Left (x - 1)
 *  - Right( x + 1) 
 */
typedef enum direction {
    DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT
} direction;

/**
 * Returns a vector from the given direction
 * for example, if the direction is 'up', the vector will be {0, -1}
 * 
 * @param d the direction
 * @return the vector created from the direction
 */
sfVector2i direction_to_vector(direction d);


/**
 * Returns the equivalent direction of a keycode
 * for example sfKeyUp equivalent is DIR_UP
 * 
 * @param key_c the keycode
 * @return the direction from the keycode
 */
direction direction_from_key_code(const sfKeyCode key_c);



#endif /* DIRECTION_H */

