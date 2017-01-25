/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "graph.h"
#include "minmax.h"

int allocated_nodes=0;

graph_node* graph_node_create(int id){
	allocated_nodes++;
    graph_node* g = malloc(sizeof(graph_node));
    g->id = id;
    g->color = 0;
    g->neighbours = list_create();
    return g;
}



void graph_node_display(void* data){
    graph_node* g = data;
    printf("addr : %p id : %d, color : %d \n",g, g->id, g->color );
    printf("neighbours : \n");
    for (int i =0; i<g->neighbours->size;i++){
        graph_link* l = list_get(g->neighbours, i);
        if (l->valid){
            printf("---- points to  : %d\n", l->next_node_link->node->id);
        }
    }
}

void graph_node_free(graph_node* g){
	if (g==0){
		return;
	}
	allocated_nodes--;
    free(g);
    g=0;
}

void graph_node_remove(void* data){
    graph_node* g = (graph_node*)data;
	if (g->neighbours!=0){
		for (int i =0; i<g->neighbours->size;i++){
		    graph_link* l = list_get(g->neighbours, i);
		    if (l!=0){
			    if (l->valid){
				l->next_node_link->valid = sfFalse;
			    }
			    graph_link_free(l);
		    }
		}
	}
    graph_node_free(g);
    g=0;
}

void graph_node_connect(graph_node* g1, graph_node* g2){
    graph_link* l1 = malloc(sizeof(graph_link));
    graph_link* l2 = malloc(sizeof(graph_link));
    l1->node = g1;
    l1->next_node_link = l2;
    l2->next_node_link = l1;
    l2->node = g2;
    list_push(g1->neighbours, l1);
    list_push(g2->neighbours, l2);
    l1->valid = sfTrue;
    l2->valid = sfTrue;
}

void graph_node_close_node(graph_node* g){
    for (int i =0; i<g->neighbours->size;i++){
        graph_link* l = list_get(g->neighbours, i);
        if (l->valid){
            if (l->next_node_link->node->color!=0){
		    l->next_node_link->valid=sfFalse;
		    l->valid = sfFalse;
	    }
        }
    }
}

list* graph_node_get_neighbour(graph_node* g){
    list* to_ret = list_create();
    for (int i =0; i<g->neighbours->size;i++){
        graph_link* l = list_get(g->neighbours, i);
        if (l->valid){
            list_push(to_ret, l->next_node_link->node);
        }
    }
    return to_ret;
}


void graph_link_free(void* data){
	graph_link* l = data;
	/*if (l->next_node_link!=0){
		l->next_node_link->valid=sfFalse;
	}*/
    free(l);
    l=0;
}
void graph_link_display(graph_link* l){
    printf("link beetween : %d, and %d\n", l->node->id, l->next_node_link->node->id);
}


void graph_create_nodes(graph* g, grid* gr, list* players){
    list* nodes_to_remove = list_create();
    for (int i =0; i<gr->height; i++){
        for (int j = 0; j<gr->width;j++){
            graph_node* node_to_add = graph_node_create(i*gr->width+j);
            if (i>0){    
                graph_node_connect(node_to_add, g->nodes[(i-1)*gr->width+j]);
            }
            if (j>0){
                graph_node_connect(node_to_add, g->nodes[i*gr->width+j-1]);
            }
            if (gr->m_grid[j][i]!=0){
                list_push(nodes_to_remove, node_to_add);
            }
            g->nodes[i*gr->width+j]=node_to_add;
        }
    }
    list_destroy(nodes_to_remove, &graph_node_remove);
    for (int i=0;i<players->size;i++){
        sfVector2i p =((player*)list_get(players, i))->position;
        list_push(g->entries, g->nodes[(p.x)*gr->width+p.y]);
	g->nodes[(p.x)*gr->width+p.y]->color=2;
    }
    for (int i=0;i<players->size;i++){
        sfVector2i p =((player*)list_get(players, i))->position;
	graph_node_close_node(g->nodes[(p.x)*gr->width+p.y]);
    }
}


graph* graph_create(grid* gr, list* players){
    graph* g = malloc(sizeof(graph));
    g->nodes = malloc(gr->height*gr->width*sizeof(graph_node*));
    g->entries = list_create();
    for (int i=0;i<players->size;i++){
        sfVector2i p =((player*)list_get(players, i))->position;
        grid_set(gr,p,0);
    }
    graph_create_nodes(g, gr, players);
    g->number_of_nodes=gr->height*gr->width;
    return g;
}

void graph_remove(graph* g){
    for (int i=0;i<g->number_of_nodes;i++){
        if (g->nodes[i]!=0 && g->nodes[i]->id ==i){
            graph_node_remove(g->nodes[i]);
        }
    }
    printf("and finally\n");
    printf("%p\n", g);
    //free(g);
    g=0;
}

void graph_display(graph* g){
	for (int i = 0 ; i<g->number_of_nodes;i++){
		printf("id : %d\n", g->nodes[i]->id);
		if (g->nodes[i]!=0 && g->nodes[i]->id==i){
			graph_node_display(g->nodes[i]);
		}
	}
}