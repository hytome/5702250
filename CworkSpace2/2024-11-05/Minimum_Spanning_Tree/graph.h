#pragma once

#define MAX_VERTICES 100

#include "list.h"

typedef struct {
	int num_of_vertex;
	int num_of_edge;
	DListNode adj_list[MAX_VERTICES];
}GraphListType;

extern GraphListType* create_list_graph();
extern void destroy_list_graph(GraphListType* g);
extern void init_list_graph(GraphListType* g);
extern void insert_vertex_list_graph(GraphListType* g, int v);
extern void insert_edge_list_graph(GraphListType* g, int s, int e, int w);
extern void delete_vertex_list_graph(GraphListType* g, int v);
extern void delete_edge_list_graph(GraphListType* g, int s, int e);
extern int is_vertex_in_graph(GraphListType* g, int v);
extern void print_adj_list(GraphListType* g);