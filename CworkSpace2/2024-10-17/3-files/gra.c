#include <stdio.h>
#include <stdlib.h>
#include "gra.h"

GraphMatType *create_mat_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

void destroy_mat_graph(GraphMatType *g) {
    free(g);
}

void init_mat_graph(GraphMatType *g) {
    g->n = 0;
    for(int r = 0; r<MAX_VERTICES; r++) {
        for(int c = 0; c<MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}

void insert_vertex_mat(GraphMatType *g, int v) {
    if(((g->n) + 1) > MAX_VERTICES) {
        printf("그래프 정점의 개수 초과");
        return;
    }
    g->n++;
}

void insert_edge_mat(GraphMatType *g, int start, int end) {
    if(start >= g->n || end >= g->n) {
        //간선의 개수가 정점의 개수를 초과하는 경우
        printf("그래프 정점의 개수 초과");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void print_adj_mat(GraphMatType *g) {
    for(int i = 0; i<g->n; i++) {
        printf("정점 %d의 인접 정점: ", i);
        for(int j = 0; j<g->n; j++) {
            printf("%02d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

