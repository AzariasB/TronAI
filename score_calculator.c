/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "score_calculator.h"

void noop(void* data)
{
}


void print_all_lists(void* data)
{
	list* l = data;
	printf("\nglobal : \n");
	list_each(l, &graph_node_display);
}



score_calculator* score_calculator_create(grid* gr, list* players)
{
	score_calculator* sc = malloc(sizeof(score_calculator));
	sc->graph = graph_create(gr, players);
	sc->entries = list_create();
	sc->players_scores = malloc(players->size * sizeof(int));
	for (int i = 0; i < players->size; i++) {
		list* player_nodes = list_create();
		list_push(player_nodes, list_get(sc->graph->entries, i));
		list_push(sc->entries, player_nodes);
		sc->players_scores[i] = 0;
	}
	return sc;
}

void score_calculator_explore_next_step(score_calculator* sc)
{
	for (int i = 0; i < sc->entries->size; i++) {
		list* curr_ent = list_get(sc->entries, i);
		list* new_ent = list_create();
		for (int j = 0; j < curr_ent->size; j++) {
			graph_node* curr_entry = (graph_node*)list_pop(curr_ent);
			list* next = graph_node_get_neighbour(curr_entry);
			for (int k = 0; k < next->size; k++) {
				list_push(new_ent, list_get(next, k));
				((graph_node*)list_get(next,k))->color=2;
				graph_node_close_node(list_get(next,k));
			}
			sc->players_scores[i] += next->size;
			graph_node_remove(curr_entry);
		}
		list_destroy(curr_ent, &noop);
		list_get_node(sc->entries, i)->data = new_ent;
	}
}

int* score_calculator_compute(score_calculator* sc)
{
	while (score_calculator_number_of_entry_nodes(sc) > 0) {
		score_calculator_explore_next_step(sc);
	}
	graph_remove(sc->graph);
	return sc->players_scores;
}

int score_calculator_number_of_entry_nodes(score_calculator* sc)
{
	int ret = 0;
	for (int i = 0; i < sc->entries->size; i++) {
		ret += ((list*) list_get(sc->entries, i))->size;
	}
	return ret;
}
