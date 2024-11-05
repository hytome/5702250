#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 11  // 정점 번호가 1부터 10까지 사용됨

// 그래프 구조체 정의
// 그래프를 나타내는 구조체입니다.
// 정점의 개수와 가중치 행렬을 가집니다.
typedef struct GraphType {
    int n;  // 그래프의 정점 개수를 나타냅니다..
    int weight[MAX_VERTICES][MAX_VERTICES];  // 가중치 행렬을 저장하는 용도.
} GraphType;

// 그래프 초기화
// 그래프를 초기화합니다.
void graph_init(GraphType* g) {
    g->n = 10;  // 정점의 개수를 10으로 설정합니다.
    for (int i = 1; i <= g->n; i++) {
        for (int j = 1; j <= g->n; j++) {
            g->weight[i][j] = (i == j) ? 0 : INT_MAX;  // 자기 자신으로의 간선은 0, 나머지는 무한대로 초기화.
            //무한대로 초기화 하는 이유: 아직 간선이 없는 상태를 나타내기 위해서.
        }
    }
}

// 그래프에 간선 추가
// 그래프에 새로운 간선을 추가합니다.
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start][end] = weight;  // 시작 정점에서 끝 정점으로의 가중치를 설정합니다.
    g->weight[end][start] = weight;  // 무방향 그래프이므로 반대 방향도 동일한 가중치를 설정합니다.
}

// 과제 이미지에 맞는 간선을 추가합니다.
void GenerateGraph(GraphType* g) {
    // 과제 이미지에 맞는 간선을 추가합니다.
    insert_edge(g, 1, 2, 3);   // 가중치 3
    insert_edge(g, 1, 7, 12);  // 가중치 12
    insert_edge(g, 1, 6, 11);  // 가중치 11
    insert_edge(g, 2, 5, 1);   // 가중치 1
    insert_edge(g, 2, 6, 7);   // 가중치 7
    insert_edge(g, 2, 4, 4);   // 가중치 4
    insert_edge(g, 2, 3, 8);   // 가중치 8
    insert_edge(g, 3, 4, 2);   // 가중치 2
    insert_edge(g, 3, 7, 6);   // 가중치 6
    insert_edge(g, 3, 8, 5);   // 가중치 5
    insert_edge(g, 4, 8, 14);  // 가중치 14
    insert_edge(g, 4, 10, 16); // 가중치 16
    insert_edge(g, 5, 6, 9);   // 가중치 9
    insert_edge(g, 5, 9, 18);  // 가중치 18
    insert_edge(g, 7, 8, 13);  // 가중치 13
    insert_edge(g, 8, 10, 15); // 가중치 15
    insert_edge(g, 9, 10, 10); // 가중치 10
}

// Prim 알고리즘을 사용하여 최소 신장 트리를 찾습니다.
// kruskal 알고리즘은 전체 간선의 가중치에서 작은것을 하나씩 선택하여(집합을 하는) 방식이라면 
// prim 알고리즘은 시작 정점 에서 출발해 트리를 확장. 현재 트리에 포함된 정점들과 인접한 간선들 중 가장 작은 가중치를 가진 간선을 선택하는 방식.
//따라서 kruskal 알고리즘은 간선을 기준으로 하는 반면 prim 알고리즘은 정점을 기준으로 합니다.
void FindPrimMST(GraphType* g) {
    printf("Prim MST Algorithm\n");  // 알고리즘 시작을 알립니다.
    int selected[MAX_VERTICES] = {0};  // 선택된 정점을 추적합니다.
    int min_edge[MAX_VERTICES];  // 각 정점에 대한 최소 가중치를 저장합니다.
    int parent[MAX_VERTICES];  // 각 정점의 부모를 저장합니다.

    // 초기화: 모든 정점의 최소 가중치를 무한대로 설정하고 부모를 -1로 설정합니다.
    for (int i = 1; i <= g->n; i++) {
        min_edge[i] = INT_MAX;
        parent[i] = -1;
    }

    // 정점 1을 시작점으로 설정
    min_edge[1] = 0;  // 시작 정점의 최소 가중치를 0으로 설정합니다.

    // 모든 정점을 순회하며 MST를 구성합니다.
    for (int i = 1; i <= g->n; i++) {
        int u = -1, min_weight = INT_MAX;

        // 선택되지 않은 정점 중 최소 가중치 간선 찾기
        for (int v = 1; v <= g->n; v++) {
            if (!selected[v] && min_edge[v] < min_weight) {
                u = v;  // 최소 가중치 정점을 선택합니다.
                min_weight = min_edge[v];
            }
        }

        selected[u] = 1;  // 정점 u를 MST에 추가
        printf("정점 %d 추가\n", u);  // 정점 추가 출력

        // u에 연결된 모든 정점의 가중치 갱신
        for (int v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INT_MAX && !selected[v] && g->weight[u][v] < min_edge[v]) {
                min_edge[v] = g->weight[u][v];  // 최소 가중치를 갱신합니다.
                parent[v] = u;  // 부모를 갱신합니다.
            }
        }
    }
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));  // 그래프를 위한 동적 메모리 할당
    graph_init(g);  // 그래프 초기화
    GenerateGraph(g);  // 그래프 생성
    FindPrimMST(g);  // Prim 알고리즘 실행
    free(g);  // 할당된 메모리 해제
    return 0;  // 프로그램 종료
}