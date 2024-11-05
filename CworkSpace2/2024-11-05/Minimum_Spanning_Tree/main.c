#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "MST.h"
#include "shortest-path.h"

main()
{
	GraphListType* h;
	GraphListType* mst;

	h = create_list_graph();
	init_list_graph(h);

	insert_vertex_list_graph(h, 0); 
	insert_vertex_list_graph(h, 1); 
	insert_vertex_list_graph(h, 2); 
	insert_vertex_list_graph(h, 3); 
	insert_vertex_list_graph(h, 4); 
	insert_vertex_list_graph(h, 5);
	insert_vertex_list_graph(h, 6); 

	insert_edge_list_graph(h, 0, 1, 29); 
	insert_edge_list_graph(h, 1, 2, 16); 
	insert_edge_list_graph(h, 2, 3, 12); 
	insert_edge_list_graph(h, 3, 4, 22); 
	insert_edge_list_graph(h, 4, 5, 27); 
	insert_edge_list_graph(h, 5, 0, 10); 
	insert_edge_list_graph(h, 1, 6, 15); 
	insert_edge_list_graph(h, 3, 6, 18); 
	insert_edge_list_graph(h, 4, 6, 25);


	printf("----- Original Graph ----------\n");
	print_adj_list(h);
	mst = kruskal_mst(h);
	printf("\n----- Kruskal's MST ----------------------\n");
	print_adj_list(mst);
	destroy_list_graph(mst);

	printf("\n----- Prim's MST ----------------------\n");
	mst = prim_mst(h, 0);
	print_adj_list(mst);
	destroy_list_graph(mst);

	printf("\n---- Dijkstra Shortest Path -------------\n");
	mst = dijkstra_sp(h, 0);
	print_adj_list(mst);
	print_sp(0, 3);

	destroy_list_graph(h);
	destroy_list_graph(mst);

/*
	delete_edge_list_graph(h, 3, 4); print_adj_list(h); printf("After deleting edge 3 - 4 \n");
	delete_edge_list_graph(h, 2, 3); print_adj_list(h); printf("After deleting edge 2 - 3 \n");

	delete_vertex_list_graph(h, 3); print_adj_list(h); printf("After deleting vertex 3 \n");

	delete_edge_list_graph(h, 0, 1);
	delete_edge_list_graph(h, 0, 4);
	delete_edge_list_graph(h, 1, 2);
	delete_edge_list_graph(h, 2, 4);
	delete_vertex_list_graph(h, 0);
	delete_vertex_list_graph(h, 1);
	delete_vertex_list_graph(h, 2);
	delete_vertex_list_graph(h, 4);

	print_adj_list(h); printf("Before destroying graph \n");
	*/

}