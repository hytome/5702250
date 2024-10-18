#include <stdio.h>
#include <stdlib.h>
#include "gra.h"

int main() {
    GraphMatType *g;
    g = create_mat_graph();
    init_mat_graph(g);
    for(int i = 0; i<5; i++) {
        insert_vertex_mat(g, i);
    }
    insert_edge_mat(g, 0, 1);
    insert_edge_mat(g, 0, 4);
    insert_edge_mat(g, 1, 2);
    insert_edge_mat(g, 2, 3);
    insert_edge_mat(g, 2, 4);
    insert_edge_mat(g, 3, 4);
    print_adj_mat(g);
    destroy_mat_graph(g);
    return 0;
}   