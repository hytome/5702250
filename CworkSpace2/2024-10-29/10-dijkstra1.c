#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 11

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head[MAX_VERTICES];
    int n;
} GraphType;

typedef struct {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct {
    MinHeapNode* nodes[MAX_VERTICES];
    int size;
} MinHeap;

// 그래프 초기화
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++)
        g->head[i] = NULL;
}

// 간선 추가
void insert_edge(GraphType* g, int start, int end, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = end;
    newNode->weight = weight;
    newNode->next = g->head[start];
    g->head[start] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = start;
    newNode->weight = weight;
    newNode->next = g->head[end];
    g->head[end] = newNode;
}

// 최소 힙 초기화
MinHeap* create_min_heap() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    return minHeap;
}

// 힙에 노드 삽입
void insert_min_heap(MinHeap* minHeap, int vertex, int distance) {
    MinHeapNode* newNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    newNode->vertex = vertex;
    newNode->distance = distance;
    minHeap->nodes[minHeap->size] = newNode;
    minHeap->size++;
    // 힙 정렬 필요
}

// 힙에서 최소 노드 추출
MinHeapNode* extract_min(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;
    MinHeapNode* minNode = minHeap->nodes[0];
    minHeap->nodes[0] = minHeap->nodes[minHeap->size - 1];
    minHeap->size--;
    // 힙 정렬 필요
    return minNode;
}

// Dijkstra 알고리즘
void dijkstra(GraphType* g, int start) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    int found_order[MAX_VERTICES];
    int found_count = 0;
    MinHeap* minHeap = create_min_heap();

    for (int i = 1; i < g->n; i++)
        dist[i] = INT_MAX;
    dist[start] = 0;

    insert_min_heap(minHeap, start, 0);

    while (minHeap->size > 0) {
        MinHeapNode* minNode = extract_min(minHeap);
        int u = minNode->vertex;
        free(minNode);

        if (visited[u]) continue;
        visited[u] = 1;
        found_order[found_count++] = u;

        Node* current = g->head[u];
        while (current != NULL) {
            int v = current->vertex;
            int weight = current->weight;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                insert_min_heap(minHeap, v, dist[v]);
            }
            current = current->next;
        }

        // 거리 배열 출력
        printf("Distance: ");
        for (int k = 1; k < g->n; k++)
            if (dist[k] == INT_MAX)
                printf("* ");
            else
                printf("%d ", dist[k]);
        printf("\n");

        // 방문 배열 출력
        printf("Found: ");
        for (int k = 1; k < g->n; k++)
            printf("%d ", visited[k]);
        printf("\n\n");
    }

    // 방문 순서 출력
    printf("Found Order: ");
    for (int i = 0; i < found_count; i++)
        printf("%d ", found_order[i]);
    printf("\n");
}

int main() {
    GraphType g;
    init_graph(&g, MAX_VERTICES);
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

    dijkstra(&g, 1);
    return 0;
}