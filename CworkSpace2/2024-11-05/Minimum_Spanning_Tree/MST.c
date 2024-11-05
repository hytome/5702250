#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "graph.h"
#include "Heap.h"

int parent[MAX_VERTICES];
void set_init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr) {
	if (parent[curr] == -1) return curr;
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

void  set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2) parent[root1] = root2;
}

GraphListType* kruskal_mst(GraphListType* g) {

	HeapType* edge_min_heap = create_heap();
	int num_of_edge = 0;
	heap_element edge;
	GraphListType* mst;
	int u, v;

	printf("..... start kruskal MST ....\n");
	init_heap(edge_min_heap);

	for (int i = 0; i < MAX_VERTICES; i++) {  // make min heap for edge list
		if (g->adj_list[i].vertex.number >= 0) {
			DListNode* nptr = g->adj_list[i].rlink;
			while (nptr != &(g->adj_list[i])) {
				if (nptr->vertex.number > i) {
					insert_min_heap(edge_min_heap, (heap_element) { nptr->vertex.weight, i, nptr->vertex.number });
					printf(" Insert edge (%d,%d[%d]) into heap \n", i, nptr->vertex.number, nptr->vertex.weight);
				}
				nptr = nptr->rlink;
			}
		}
	}

	print_heap(edge_min_heap);

	mst = create_list_graph();
	init_list_graph(mst);

	num_of_edge = 0;
	set_init(7);
	while (num_of_edge < (g->num_of_vertex - 1)) {
		edge = delete_min_heap(edge_min_heap);
		printf("Considering Edge (%d,%d[%d]).....", edge.start, edge.end, edge.key);
		u = set_find(edge.start);
		v = set_find(edge.end);
		if (u != v) {
			printf(" (u=%d,v=%d) No cicle... ",u,v);
			if (!is_vertex_in_graph(mst, edge.start)) {
				insert_vertex_list_graph(mst, edge.start);
				printf("Insert vertext %d to MST.....", edge.start);
			}
			if (!is_vertex_in_graph(mst, edge.end)) {
				insert_vertex_list_graph(mst, edge.end);
				printf("Insert vertext %d to MST.....", edge.end);
			}
			insert_edge_list_graph(mst, edge.start, edge.end, edge.key);
			printf("Insert edge (%d,%d[%d])\n", edge.start, edge.end, edge.key);
			set_union(u, v);
			num_of_edge++;
		}
		else {
			printf(" (u=%d,v=%d) Cicle..... do not insert to MST\n",u,v);
		}
	}
	destroy_heap(edge_min_heap);
	printf("..... complete kruskal MST ....\n");
	return mst;
}


GraphListType* prim_mst(GraphListType* g, int s) {
	int* visit;
	GraphListType* mst;
	HeapType* edge_min_heap = create_heap();

	init_heap(edge_min_heap);

	mst = create_list_graph();
	init_list_graph(mst);

	visit = (int*)malloc(g->num_of_vertex * sizeof(int));
	for (int i = 0; i < g->num_of_vertex; i++) visit[i] = 0;

	insert_min_heap(edge_min_heap, (heap_element) { 0, s, s});
	printf("-- Insert start node %d in heap  ****\n",s);
	// print_heap(edge_min_heap);

	heap_element min_edge;
	int mst_edge_number = 0;
	while( mst_edge_number < g->num_of_vertex) {
		min_edge = delete_min_heap(edge_min_heap);
		printf(" Considering [w=%02d](s=%d,e=%d) ***** ", min_edge.key, min_edge.start, min_edge.end);
		if (visit[min_edge.end]) {
			printf("vertex %d is already visited...\n", min_edge.end);
			continue;
		}

		visit[min_edge.end] = 1; // mark visit
		mst_edge_number++;
		insert_vertex_list_graph(mst, min_edge.end);
		if (min_edge.start != min_edge.end) insert_edge_list_graph(mst, min_edge.start, min_edge.end, min_edge.key);
		printf(" Visit vertex %d....", min_edge.end);

		for (DListNode* s = g->adj_list[min_edge.end].rlink; s != &(g->adj_list[min_edge.end]); s = s->rlink) {
			if (visit[s->vertex.number] == 1) continue;
			insert_min_heap(edge_min_heap, (heap_element) { s->vertex.weight, min_edge.end, s->vertex.number });
			printf("Insert node [%d(%d,%d)] in heap ****", s->vertex.weight, min_edge.end, s->vertex.number);
			// print_heap(edge_min_heap);
		}
		printf("\n");
	}

	destroy_heap(edge_min_heap);

	return mst;
}