#pragma once

#define MAX_VERTICES 100

typedef struct GraphMatType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

extern GraphMatType *create_mat_graph();
extern void destroy_mat_graph(GraphMatType *g);
extern void init_mat_graph(GraphMatType *g);
extern void insert_vertex_mat(GraphMatType *g, int v);
extern void insert_edge_mat(GraphMatType *g, int start, int end);
extern void print_adj_mat(GraphMatType *g);
