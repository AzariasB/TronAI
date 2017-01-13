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
    g->m_grid = (int**)malloc(height * sizeof (int*));
    for (int i = 0; i < height; i++) {
        g->m_grid[i] = (int*)malloc(width * sizeof (int));
        for (int j = 0; j < width; j++) {
            g->m_grid[i][j] = 0;
        }
    }
    g->height = height;
    g->width = width;
    return g;
}

grid *grid_copy(const grid* to_copy) {
    grid *g_cpy = grid_create(to_copy->width, to_copy->height);
    for(int y = 0; y < to_copy->height; y++){
        for(int x = 0; x < to_copy->width; x++){
            g_cpy->m_grid[y][x] = to_copy->m_grid[y][x];
        }
    }

    return g_cpy;
}

void grid_destroy(grid* g) {
    for(int i = 0; i < g->height; i++){
        int *ptr = g->m_grid[i];
        free(ptr);
    }
    free(g);
}

sfBool grid_contains(const grid* g, sfVector2i pos)
{
    return pos.x >= 0 && pos.y >= 0 && pos.x < g->width && pos.y < g->height;
}

int grid_at(const grid* g, sfVector2i pos)
{
    return g->m_grid[pos.y][pos.x];
}

#endif