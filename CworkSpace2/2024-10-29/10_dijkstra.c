
#include <stdio.h>
#include <limits.h>
//Dijkstra 알고리즘은 힌 시작 노드에서 다른 모든 노드까지의 최단 경로를 구하는것이다. 
//최소 가중치의 합을 그냥 구했던 기존의 배웠던 알고리즘과의 차이가 바로 이것입니다.
#define MAX_VERTICES 11  // 노드 개수 설정 (0부터 10까지의 노드)

typedef struct {
    int weight[MAX_VERTICES][MAX_VERTICES]; //인접행렬을 사용했습니다.
    int n;  // 그래프의 노드 수
} GraphType;

// 그래프 초기화 함수
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g->weight[i][j] = (i == j) ? 0 : INT_MAX; // 자기 자신을 제외한 모든 거리를 무한대로 설정
            //이러한 방식으로 아직 해당 노드까지 최단 경로가 계산되지 않았음을 나타낸다.
}

// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start][end] = weight;
    g->weight[end][start] = weight;  // 무방향 그래프이므로 대칭적으로 추가
    //이 알고리즘은 무방향과 방향 그래프 모두 적용 가능하다.
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

    for (int v = 1; v < n; v++)  // 0번 노드 제외
    //이거 안하면 시작노드에서 0이라는 값까지 찾음. 
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Dijkstra 알고리즘
void dijkstra(GraphType* g, int start) {
    int dist[MAX_VERTICES];         
    int visited[MAX_VERTICES] = {0}; 
    int found_order[MAX_VERTICES];
    int found_count = 0;

    for (int i = 1; i < g->n; i++)  // 0번 노드 제외하고 초기화
        dist[i] = INT_MAX; //무한대로 하여 아직 해당 노드까지 최단 경로가 계산되지 않았음을 나타낸다.
    dist[start] = 0;

    for (int i = 1; i < g->n - 1; i++) {
        int u = min_distance(dist, visited, g->n);
        if (u == -1) break;  

        visited[u] = 1;
        found_order[found_count++] = u;

        for (int v = 1; v < g->n; v++)  // 0번 노드 제외
            if (!visited[v] && g->weight[u][v] != INT_MAX && dist[u] != INT_MAX
                && dist[u] + g->weight[u][v] < dist[v])
                dist[v] = dist[u] + g->weight[u][v];

        // 거리 배열 출력
        printf("Distance: ");
        for (int k = 1; k < g->n; k++)  // 0번 노드 제외
            if (dist[k] == INT_MAX)
                printf("* ");
            else
                printf("%d ", dist[k]);
        printf("\n");

        // 방문 배열 출력
        printf("Found: ");
        for (int k = 1; k < g->n; k++)  // 0번 노드 제외
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
    GenerateGraph(&g);

    dijkstra(&g, 1); // 노드 1에서 시작하여 최단 거리 계산
    return 0;
}
