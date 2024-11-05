#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "graph.h"
#include "Heap.h"

int dist[MAX_VERTICES], prev[MAX_VERTICES];

GraphListType* dijkstra_sp(GraphListType* g, int start) {
	GraphListType* sp;
	HeapType* h;
	DListNode* nptr;


	h = create_heap();
	init_heap(h);

	for (int i = 0; i < g->num_of_vertex; i++) {
		dist[i] = 100; prev[i] = -1;
	}
	dist[start] = 0;

	nptr = g->adj_list[start].rlink;
	while (start != nptr->vertex.number) {
		dist[nptr->vertex.number] = nptr->vertex.weight;
		insert_min_heap(h, (heap_element) { nptr->vertex.weight , start, nptr->vertex.number});
		nptr = nptr->rlink;
	}
	// printf("Initial heap \n");
	// print_heap(h);

	sp = create_list_graph();
	init_list_graph(sp);
	insert_vertex_list_graph(sp,start);

	for (int i = 0; i < g->num_of_vertex - 1; i++) {
		heap_element min_edge = delete_min_heap(h);
		if (prev[min_edge.end] != -1) continue;
		printf("***** Add (%d,%d[%d]) to shortest path\n", min_edge.start, min_edge.end, min_edge.key);
		prev[min_edge.end] = min_edge.start;
		insert_vertex_list_graph(sp, min_edge.end);
		insert_edge_list_graph(sp, min_edge.start, min_edge.end, min_edge.key);

		nptr = g->adj_list[min_edge.end].rlink;
		while (min_edge.end != nptr->vertex.number) {
			if (dist[nptr->vertex.number] > dist[min_edge.end] + nptr->vertex.weight) {
				dist[nptr->vertex.number] = dist[min_edge.end] + nptr->vertex.weight;
				insert_min_heap(h, (heap_element) { dist[nptr->vertex.number], min_edge.end, nptr->vertex.number });
				printf("Upate distance (node %d: dist:%d) and insert edge into the heap\n", nptr->vertex.number, dist[nptr->vertex.number]);
				// print_heap(h);
			}
			nptr = nptr->rlink;
		} 

	}
	return sp;
}

void print_sp(int start, int end) {
	printf("\n Shortest reverse path from %d to %d\n", start, end);
	printf("%d", end);
	for (int i = prev[end]; i != start; i = prev[i]) {
		printf("<--- %d", i);
	}
	printf("<---- %d\n", start);
}