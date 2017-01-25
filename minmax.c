/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <SFML/System/Vector2.h>

#include "minmax.h"
#include "list.h"
#include "utils.h"
#include "player.h"
#include "grid.h"
#include "score_calculator.h"

int graphs = 0;
direction final_desti = DIR_UP;
int ai_get_best_direction(list* players, grid* g, int level, int player_id){
	minmax_compute(players, g,  level,  player_id);
	printf("graphs : %d\n", graphs);
	return final_desti;
}

int* minmax_compute(list* players, grid* g, int level, int player_id){
	if (level==3){
		graphs++;
		int* ret = min_max_calc_score(g, players);
		return ret;
	}
	
	if (player_id>=players->size){
		player_id=0;
	}
	player* p = list_get(players, player_id);
	score_list* scores = score_list_create(players->size);
	for (direction d = 0;d<4;d++){
		sfVector2i nouv_pos = utils_update_pos(p->position, d);
		sfVector2i old_pos= {p->position.x, p->position.y};
		if (minmax_can_go_there(players, g, nouv_pos)){
			p->position = nouv_pos;
			grid_set(g, nouv_pos, 2);
			score_list_add_direction_score(scores, minmax_compute(players, g,level+1, player_id+1));
			p->position = old_pos;
			grid_set(g, nouv_pos, 0);
			grid_set(g, old_pos, 2);
		}
		else{
			score_list_add_direction_fail(scores, player_id);
		}
	}
	if (level==0){
		final_desti = score_list_get_best_move_for(scores, player_id);
	}
	return score_list_get_scores_for(scores, player_id);
}



int* min_max_calc_score(grid* g, list* players){
	score_calculator* sc = score_calculator_create(g, players);
	return score_calculator_compute(sc);
}

void grid_normalized(grid* g){
	for (int i=0;i<g->height;i++){
		for (int j=0;j<g->width;j++){
			sfVector2i pos = {j,i};
			grid_set(g, pos, grid_at(g, pos)+1);
		}
	}
}

sfBool minmax_can_go_there(list* players, grid* g, sfVector2i nouv_pos){
	if (!(grid_contains(g, nouv_pos) && grid_equals(g, nouv_pos, 0))){
		return sfFalse;
	}
	for (int i=0;i<players->size;i++){
		player* p = list_get(players, i);
		sfVector2i pos = p->position;
		if (pos.x==nouv_pos.x && pos.y==nouv_pos.y){
			return sfFalse;
		}
	}
	return sfTrue;
	
}
