/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#include <string.h>
#include <stdio.h>

#include "grid.h"

#ifdef GRID_H

grid* grid_create(int width, int height)
{
	grid* g = utils_safe_malloc(sizeof(grid), "Creating grid");
	g->m_grid = (int**) utils_safe_malloc(height * sizeof(int*), "Creating grids 2d array");
	for (int i = 0; i < height; i++) {
		g->m_grid[i] = (int*) utils_safe_malloc(width * sizeof(int), "Creating line of 2d array");
		for (int j = 0; j < width; j++) {
			g->m_grid[i][j] = -1;
		}
	}
	g->height = height;
	g->width = width;
	return g;
}

grid *grid_copy(const grid* to_copy)
{
	grid *g_cpy = grid_create(to_copy->width, to_copy->height);
	for (int y = 0; y < to_copy->height; y++) {
		for (int x = 0; x < to_copy->width; x++) {
			g_cpy->m_grid[y][x] = to_copy->m_grid[y][x];
		}
	}

	return g_cpy;
}

void grid_destroy(grid* g)
{
	for (int i = 0; i < g->height; i++) {
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
	if (!grid_contains(g, pos)) {
		fprintf(stderr, "Tried to access x=%d - y=%d of the grid (not available)\n", pos.x, pos.y);
		return 0;
	}
	return g->m_grid[pos.y][pos.x];
}

void grid_set(grid* g, sfVector2i pos, int value)
{
	if (!grid_contains(g, pos)) {
		fprintf(stderr, "Tried to set at : x=%d, y=%d in the grid (not available)\n", pos.x, pos.y);
		return;
	}
	g->m_grid[pos.y][pos.x] = value;
}

#endif