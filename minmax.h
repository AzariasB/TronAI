/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   minmax.h
 * Author: user
 *
 * Created on 23 janvier 2017, 12:22
 */

#ifndef MINMAX_H
#define MINMAX_H
#include "score_list.h"
#include "score_calculator.h"
int ai_get_best_direction(list* players, grid* g, int level, int player_id);
int* minmax_compute(list* players, grid* g, int level, int player_id);
sfBool minmax_can_go_there(list* players, grid* g, sfVector2i nouv_pos);
void grid_normalized(grid* g);
list* min_max_get_max(list* scores);
int* min_max_calc_score(grid* g, list* players);
#endif /* MINMAX_H */

