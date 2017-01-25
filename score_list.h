/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   score_list.h
 * Author: user
 *
 * Created on 23 janvier 2017, 13:05
 */

#ifndef SCORE_LIST_H
#define SCORE_LIST_H

#include "direction.h"
#include "list.h"

typedef struct score_list{
    list* scores;
    int number_of_players;
}score_list;



score_list* score_list_create(int number_of_players);
void score_list_add_direction_score(score_list* sc, int* dir_score);
void score_list_add_direction_fail(score_list* sc, int player_id);
void score_list_display(score_list* sc);
void score_list_free(score_list* s);
int score_list_get_best_move_for(score_list* sc, int player_id);
int * score_list_get_scores_for(score_list* sc, int player_id);

#endif /* SCORE_LIST_H */

