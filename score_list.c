/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "score_list.h"
#include "score_calculator.h"



score_list* score_list_create(int number_of_players){
	score_list* sc = malloc(sizeof(score_list));
	sc->scores = list_create();
	sc->number_of_players=number_of_players;
	return sc;
}

void score_list_add_direction_score(score_list* sc, int* dir_score){
	list_push(sc->scores, dir_score);
}

void score_list_add_direction_fail(score_list* sc, int player_id){
	int* scores = malloc(sc->number_of_players*sizeof(int));
	for (int i=0;i<sc->number_of_players;i++){
		scores[i]=i==player_id?0:10;
	}
	list_push(sc->scores, scores);
}

void score_list_display(score_list* sc){
	for (int i=0;i<4;i++){
		printf("for dir : %d\n", i);
		int* score = list_get(sc->scores, i);
		for (int j=0;j<sc->number_of_players;j++){
			printf(" : %d", score[j]);
		}
	}
}

void score_list_free(score_list* s){
	list_destroy(s->scores, &free);
	free(s);
}

int score_list_get_best_move_for(score_list* sc, int player_id){
	int max_id = 0;
	int max_val = 0;
	for (int i= 0;i<4;i++){
		if (((int*)list_get(sc->scores, i))[player_id]>max_val){
			max_val = ((int*)list_get(sc->scores, i))[player_id];
			max_id = i;
		}
	}
	return max_id;
}
int * score_list_get_scores_for(score_list* sc, int player_id){
	int max_id = 0;
	int max_val = 0;
	for (int i= 0;i<4;i++){
		if (((int*)list_get(sc->scores, i))[player_id]>max_val){
			max_val = ((int*)list_get(sc->scores, i))[player_id];
			max_id = i;
		}
	}
	return list_get(sc->scores, max_id);
}