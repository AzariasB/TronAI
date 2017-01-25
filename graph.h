/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.h
 * Author: user
 *
 * Created on 20 janvier 2017, 16:48
 */
// create all nodes -> create neibourgs
#ifndef GRAPH_H
#define GRAPH_H
#include "list.h"
#include "grid.h"


typedef struct graph_link graph_link;

typedef struct graph_node {
    int id;
    int color;
    list* neighbours;
}graph_node;

struct graph_link {
    sfBool valid;
    graph_node* node;
    graph_link* next_node_link;
};

typedef struct graph{
    list* entries;
    graph_node** nodes;
    graph_link** links;
    int number_of_nodes;
} graph;


graph* graph_create(grid* g, list* players);
void graph_display(graph* g);
void graph_free(graph*);

graph_node* graph_node_create(int id);
void graph_node_display(void* data);
void graph_node_free(graph_node* g);
void graph_node_remove(void* data);
list* graph_node_get_neighbour(graph_node* g);
void graph_node_close_node(graph_node* g);

graph_link* graph_link_create(graph_node* g1);
void graph_link_free(void* l);
void graph_link_display(graph_link* g);
#endif