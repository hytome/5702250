#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct {
    int vertices[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} GraphType;

void graph_init(GraphType *g) {
    g->num_vertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->vertices[i][j] = 0;
}

void GenerateGraph(GraphType *g) {
    g->num_vertices = 10; // 정점의 수

    // 간선과 가중치 설정
    g->vertices[0][1] = 11;
    g->vertices[0][6] = 7;
    g->vertices[0][7] = 12;
    g->vertices[1][2] = 3;
    g->vertices[1][5] = 1;
    g->vertices[2][3] = 5;
    g->vertices[2][6] = 7;
    g->vertices[3][4] = 2;
    g->vertices[3][7] = 6;
    g->vertices[4][5] = 4;
    g->vertices[4][9] = 10;
    g->vertices[5][9] = 18;
    g->vertices[6][7] = 8;
    g->vertices[7][8] = 5;
    g->vertices[8][9] = 15;

    // 대칭 간선 설정
    for (int i = 0; i < g->num_vertices; i++) {
        for (int j = 0; j < g->num_vertices; j++) {
            if (g->vertices[i][j] != 0) {
                g->vertices[j][i] = g->vertices[i][j];
            }
        }
    }
}

int minKey(int key[], int mstSet[], int vertices) {
    int min = INF, min_index;
    for (int v = 0; v < vertices; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void FindPrimMST(GraphType *g) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int mstSet[MAX_VERTICES];

    for (int i = 0; i < g->num_vertices; i++)
        key[i] = INF, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < g->num_vertices - 1; count++) {
        int u = minKey(key, mstSet, g->num_vertices);
        mstSet[u] = 1;

        printf("정점 %d 추가\n", u + 1);

        for (int v = 0; v < g->num_vertices; v++)
            if (g->vertices[u][v] && mstSet[v] == 0 && g->vertices[u][v] < key[v])
                parent[v] = u, key[v] = g->vertices[u][v];
    }
}

int main(void) {
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);
    FindPrimMST(g);

    free(g);
    return 0;
}
