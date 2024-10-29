#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 11  // 노드 개수 설정

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* adjList[MAX_VERTICES];  // 각 정점의 인접 리스트
    int n;
} GraphType;

// 그래프 초기화 함수
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++)
        g->adjList[i] = NULL;
}

// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = end;
    node->weight = weight;
    node->next = g->adjList[start];
    g->adjList[start] = node;

    // 무방향 그래프이므로 반대 방향도 추가
    node = (Node*)malloc(sizeof(Node));
    node->vertex = start;
    node->weight = weight;
    node->next = g->adjList[end];
    g->adjList[end] = node;
}

// 최단 거리 배열에서 최소 거리를 가진 인덱스를 찾는 함수
int min_distance(int dist[], int visited[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

// Dijkstra 알고리즘
void dijkstra(GraphType* g, int start) {
    int dist[MAX_VERTICES];         // 최단 거리를 저장할 배열
    int visited[MAX_VERTICES] = {0}; // 방문 여부 확인 배열

    for (int i = 0; i < g->n; i++)
        dist[i] = INT_MAX;
    dist[start] = 0;

    for (int i = 0; i < g->n - 1; i++) {
        int u = min_distance(dist, visited, g->n);
        if (u == -1) break;

        visited[u] = 1;

        Node* curr = g->adjList[u];
        while (curr != NULL) {
            int v = curr->vertex;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + curr->weight < dist[v])
                dist[v] = dist[u] + curr->weight;
            curr = curr->next;
        }
    }

    // 결과 출력
    printf("-노드 %d에서 시작한 최단 거리-\n", start);
    for (int i = 1; i < g->n; i++)
        printf("노드 %d까지의 거리: %d\n", i, dist[i] == INT_MAX ? -1 : dist[i]);
}

// 메모리 해제 함수
void free_graph(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        Node* curr = g->adjList[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}

int main() {
    GraphType g;
    init_graph(&g, MAX_VERTICES);

    // 간선 추가 예시
    insert_edge(&g, 1, 2, 3);
    insert_edge(&g, 1, 7, 12);
    insert_edge(&g, 1, 6, 11);
    insert_edge(&g, 2, 5, 1);
    insert_edge(&g, 2, 6, 7);
    insert_edge(&g, 2, 4, 4);
    insert_edge(&g, 2, 3, 8);
    insert_edge(&g, 3, 4, 2);
    insert_edge(&g, 3, 7, 6);
    insert_edge(&g, 3, 8, 5);
    insert_edge(&g, 4, 8, 14);
    insert_edge(&g, 4, 10, 16);
    insert_edge(&g, 5, 6, 9);
    insert_edge(&g, 5, 9, 18);
    insert_edge(&g, 7, 8, 13);
    insert_edge(&g, 8, 10, 15);
    insert_edge(&g, 9, 10, 10);

    dijkstra(&g, 1); // 노드 1에서 시작하여 최단 거리 계산

    free_graph(&g); // 메모리 해제
    return 0;
}
