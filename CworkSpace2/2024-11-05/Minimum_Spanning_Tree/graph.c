#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "list.h"


GraphListType* create_list_graph() {
	return (GraphListType*)malloc(sizeof(GraphListType));
}
void destroy_list_graph(GraphListType* g) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (g->adj_list[i].vertex.number != -1) {
			DListNode* head, * next;
			head = &(g->adj_list[i]);
			next = head->rlink;
			while (head != next) {
				delete_Dlist(head, next);
				next = head->rlink;
			}
		}
		g->adj_list[i].vertex.number = -1;
	}
	free(g);
}

void init_list_graph(GraphListType* g) {

	for (int i = 0; i < MAX_VERTICES; i++) {
		init_Dlist(&(g->adj_list[i]));
		g->adj_list[i].vertex.number = -1;
	}
	g->num_of_edge = g->num_of_vertex = 0;
}
void insert_vertex_list_graph(GraphListType* g, int v) {
	if (g->adj_list[v].vertex.number == -1) {
		g->adj_list[v].vertex.number = v;
		(g->num_of_vertex)++;
	}
	else {
		fprintf(stderr, "vertex %d already exist in graph\n", v);
	}
}

void insert_edge_list_graph(GraphListType* g, int s, int e, int w) {
	if (search_Dlist(&(g->adj_list[s]), (element) { e, w }) == NULL) {
		insert_Dlist(&(g->adj_list[s]), (element) { e, w });
		insert_Dlist(&(g->adj_list[e]), (element) { s, w });
		(g->num_of_edge)++;
	}
	else {
		fprintf(stderr, "edge (%d,%d) already exist in graph\n", s,e);
	}
}

void delete_vertex_list_graph(GraphListType* g, int v) {
	if (g->adj_list[v].rlink != &(g->adj_list[v])) {
		fprintf(stderr, " vertex delete fail: %d has edge\n", v);
		return;
	}
	g->adj_list[v].vertex.number = -1;
	(g->num_of_vertex)--;
}

void delete_edge_list_graph(GraphListType* g, int s, int e) {
	DListNode* v, * w;

	v = search_Dlist(&(g->adj_list[s]), (element) { e, 0 });
	w = search_Dlist(&(g->adj_list[e]), (element) { s, 0 });
	if (v != NULL && w != NULL) {
		delete_Dlist(&(g->adj_list[s]), v);
		delete_Dlist(&(g->adj_list[e]), w);
		(g->num_of_edge)--;
	}
	else {
		fprintf(stderr, "Delete edge: edge (%d,%d) does not exist in graph\n", s, e);
	}
}

int is_vertex_in_graph(GraphListType* g, int v) {
	return (g->adj_list[v].vertex.number == v);
}



void print_adj_list(GraphListType* g) {
	printf("\n입접 리스트 출력\n");
	for (int i = 0; i <= MAX_VERTICES; i++) {
		if (g->adj_list[i].vertex.number >= 0 ) {
			printf(" Vertex %d ", i);
			print_Dlist(&(g->adj_list[i]));
		}
	}
}