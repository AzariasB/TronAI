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


typedef enum direction{
    DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT
} direction;

sfVector2i direction_to_vector(direction d);

direction direction_from_key_code(const sfKeyCode key_c);



#endif /* DIRECTION_H */

