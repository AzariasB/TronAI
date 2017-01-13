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

typedef struct grid {
	int ** m_grid;
	int width;
	int height;
} grid;


grid *grid_create(int width, int height);

grid *grid_copy(const grid *to_copy);

sfBool grid_contains(const grid *g, sfVector2i pos);

int grid_at(const grid *g, sfVector2i pos);

void grid_destroy(grid* g);

#endif /* GRID_H */

