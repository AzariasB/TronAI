/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#include <string.h>

#include "grid.h"

#ifdef GRID_H

grid* grid_create(int width, int height) {
    grid* g = malloc(sizeof (grid));
    g->m_grid = malloc(sizeof (int) * width * height);
    g->height = height;
    g->width = width;

    return g;
}

grid *grid_copy(const grid* to_copy) {
    grid *g_cpy;
    g_cpy = malloc(sizeof (grid));

    int **grid_copy = malloc(sizeof (int) * to_copy->height * to_copy->width);

    memcpy(to_copy->m_grid, grid_copy, to_copy->width * to_copy->height);

    g_cpy->width = to_copy->width;
    g_cpy->height = to_copy->height;
    g_cpy->m_grid = grid_copy;

    return g_cpy;
}

void grid_destroy(grid* g) {
    free(g->m_grid);
    free(g);
}

#endif