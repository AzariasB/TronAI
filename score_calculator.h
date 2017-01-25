/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   score_calculator.h
 * Author: user
 *
 * Created on 23 janvier 2017, 07:03
 */

#ifndef SCORE_CALCULATOR_H
#define SCORE_CALCULATOR_H
#include"graph.h"
typedef struct score_calculator{
    graph* graph;
    list* entries;
    int* players_scores;
} score_calculator;

score_calculator* score_calculator_create(grid* gr, list* players);
void score_calculator_explore_next_step(score_calculator* sc);

int* score_calculator_compute(score_calculator* sc);
int score_calculator_number_of_entry_nodes(score_calculator* sc);
#endif /* SCORE_CALCULATOR_H */