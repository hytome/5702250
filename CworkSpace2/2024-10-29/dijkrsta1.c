#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 11  // 노드 개수 설정 (0부터 10까지의 노드)

typedef struct {
    int weight[MAX_VERTICES][MAX_VERTICES];
    int n;  // 그래프의 노드 수
} GraphType;

// 그래프 초기화 함수
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g->weight[i][j] = (i == j) ? 0 : INT_MAX; // 자기 자신을 제외한 모든 거리를 무한대로 설정
}

// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start][end] = weight;
    g->weight[end][start] = weight;  // 무방향 그래프이므로 대칭적으로 추가
}

// 그래프 구성 함수
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 3, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
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

    // 모든 노드의 거리 초기화
    for (int i = 0; i < g->n; i++)
        dist[i] = INT_MAX;
    dist[start] = 0;

    // 모든 노드에 대해 최단 경로 계산
    for (int i = 0; i < g->n - 1; i++) {
        int u = min_distance(dist, visited, g->n);
        if (u == -1) break;  // 더 이상 연결된 노드가 없으면 종료

        visited[u] = 1;

        // 인접한 노드들의 거리 업데이트
        for (int v = 0; v < g->n; v++)
            if (!visited[v] && g->weight[u][v] != INT_MAX && dist[u] != INT_MAX
                && dist[u] + g->weight[u][v] < dist[v])
                dist[v] = dist[u] + g->weight[u][v];
    }

    // 결과 출력
    printf("-노드 %d에서 시작한 최단 거리-\n", start);
    for (int i = 1; i < g->n; i++)
        printf("노드 %d까지의 거리: %d\n", i, dist[i] == INT_MAX ? -1 : dist[i]);
}

int main() {
    GraphType g;
    init_graph(&g, MAX_VERTICES);
    GenerateGraph(&g);

    dijkstra(&g, 1); // 노드 1에서 시작하여 최단 거리 계산
    return 0;
}
