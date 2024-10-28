#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20  // 최대 정점 수를 정의합니다.
#define INF 1000  // 무한대 값을 정의합니다. 간선이 없는 경우를 나타냅니다.
//즉 간선이 존재하지 않을때 무한대 값을 주어 다른 간선들과 구분합니다. 해당 경로를 선택하지 않기 위함.


//krusal 알고리즘:가장 가중치가 작은 간선부터 차례로 선택하여 트리에 추가하는 방식입니다.

// 간선 구조체 정의
// 그래프의 각 간선을 나타내는 구조체입니다.
// 각 간선은 시작 정점, 끝 정점, 가중치를 가집니다.
typedef struct {
    int start, end, weight;  // 간선의 시작 정점, 끝 정점, 가중치를 저장합니다.
} Edge;

// 그래프 구조체 정의
// 그래프를 나타내는 구조체입니다.
// 간선의 개수와 간선 리스트를 가집니다.
typedef struct {
    int n;  // 그래프의 간선 개수를 나타냅니다.
    Edge edges[2 * MAX_VERTICES];  // 간선 리스트를 저장합니다.
} GraphType;

// 최소 힙 구조체 정의
// 최소 힙을 나타내는 구조체입니다.
// 힙은 간선 배열과 크기를 가집니다.
typedef struct {
    Edge heap[2 * MAX_VERTICES];  // 간선 포인터 배열로 힙을 구현합니다.
    int size;  // 현재 힙의 크기를 나타냅니다.
} MinHeap;

// 부모 노드를 찾는 함수 (Union-Find 알고리즘)
// 주어진 정점의 부모 노드를 찾습니다.
int find(int parent[], int vertex) {
    if (parent[vertex] == vertex) return vertex;  // 정점이 자신의 부모인 경우 반환합니다.
    return parent[vertex] = find(parent, parent[vertex]);  // 경로 압축을 수행하며 부모를 찾습니다.
}

// 두 집합을 합치는 함수 (Union-Find 알고리즘)
// 이렇게 두 집합을 합치고 사이클을 방지합니다.
// 사이클을 방지하는 이유는,원래 정점으로 돌아오는것을 막기 위해서입니다. MST는 사이클이 없어야합니다.
// 두 정점이 속한 집합을 합칩니다. 
void unionSets(int parent[], int rank[], int u, int v) {
    u = find(parent, u);  // 정점 u의 부모를 찾습니다.
    v = find(parent, v);  // 정점 v의 부모를 찾습니다.
    if (rank[u] > rank[v]) parent[v] = u;  // u의 랭크가 더 크면 v를 u에 연결합니다.
    else parent[u] = v;  // 그렇지 않으면 u를 v에 연결합니다.
    if (rank[u] == rank[v]) rank[v]++;  // 랭크가 같으면 v의 랭크를 증가시킵니다.
}

// 간선을 가중치 순으로 정렬하는 함수 (Quick Sort)
// 간선을 가중치에 따라 정렬합니다.
int compare(const void *a, const void *b) {
    Edge *x = (Edge *)a;  // 첫 번째 간선을 가리킵니다.
    Edge *y = (Edge *)b;  // 두 번째 간선을 가리킵니다.
    return x->weight - y->weight;  // 가중치 차이를 반환하여 정렬합니다.
}

// 최소 힙 초기화
// 최소 힙을 초기화합니다.
void initMinHeap(MinHeap *h) {
    h->size = 0;  // 힙의 크기를 0으로 설정합니다.
}

// 최소 힙 삽입
// 새로운 간선을 최소 힙에 삽입합니다.
void insertMinHeap(MinHeap *h, Edge item) {
    int i = ++(h->size);  // 힙의 크기를 증가시키고 삽입 위치를 설정합니다.

    // 부모 노드와 비교하여 히프 속성을 만족할 때까지 위로 이동합니다.
    while (i != 1 && item.weight < h->heap[i / 2].weight) {
        h->heap[i] = h->heap[i / 2];  // 부모 노드를 아래로 이동합니다.
        i /= 2;  // 부모 노드의 인덱스로 이동합니다.
    }
    h->heap[i] = item;  // 최종 위치에 간선을 삽입합니다.
}

// 최소 힙 삭제 (최소 가중치 간선 추출)
// 힙의 루트 간선을 추출하고 힙 속성을 유지합니다.
Edge deleteMinHeap(MinHeap *h) {
    int parent = 1, child = 2;  // 부모와 자식 인덱스를 초기화합니다.
    Edge item = h->heap[1];  // 루트 간선을 임시 저장합니다.
    Edge temp = h->heap[(h->size)--];  // 마지막 간선을 임시 저장하고 힙 크기를 줄입니다.

    // 자식 노드가 존재하는 동안 반복합니다.
    while (child <= h->size) {
        // 오른쪽 자식이 존재하고, 오른쪽 자식의 가중치가 더 작으면 오른쪽 자식으로 이동합니다.
        if (child < h->size && h->heap[child].weight > h->heap[child + 1].weight) {
            child++;
        }
        // 임시 간선의 가중치가 자식의 가중치보다 작거나 같으면 종료합니다.
        if (temp.weight <= h->heap[child].weight) break;

        h->heap[parent] = h->heap[child];  // 자식을 부모로 이동합니다.
        parent = child;  // 부모 인덱스를 자식 인덱스로 이동합니다.
        child *= 2;  // 자식 인덱스를 왼쪽 자식으로 이동합니다.
    }
    h->heap[parent] = temp;  // 최종 위치에 임시 간선을 삽입합니다.
    return item;  // 추출된 간선을 반환합니다.
}

// 그래프 초기화
// 그래프를 초기화합니다.
void graph_init(GraphType *g) {
    g->n = 0;  // 간선의 개수를 0으로 설정합니다.
}

// 그래프에 간선 추가
// 그래프에 새로운 간선을 추가합니다.
void insert_edge(GraphType *g, int u, int v, int weight) {
    g->edges[g->n].start = u;  // 간선의 시작 정점을 설정합니다.
    g->edges[g->n].end = v;  // 간선의 끝 정점을 설정합니다.
    g->edges[g->n].weight = weight;  // 간선의 가중치를 설정합니다.
    g->n++;  // 간선의 개수를 증가시킵니다.
}

// Qsort 기반 Kruskal 알고리즘
// QuickSort를 사용하여 간선을 정렬하고 Kruskal 알고리즘을 수행합니다.
void QuickKruskal(GraphType *g) {
    int parent[MAX_VERTICES], rank[MAX_VERTICES];  // 부모와 랭크 배열을 선언합니다.
    int mst_weight = 0;  // MST의 총 가중치를 초기화합니다.

    // 각 정점을 자신의 부모로 초기화하고 랭크를 0으로 설정합니다.
    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    qsort(g->edges, g->n, sizeof(Edge), compare);  // 간선을 가중치 순으로 정렬합니다.

    printf("QuickSort 기반 Kruskal MST:\n");  // MST 시작을 알립니다.
    for (int i = 0, mst_edges = 0; mst_edges < g->n - 1 && i < g->n; i++) {
        int u = g->edges[i].start;  // 간선의 시작 정점을 가져옵니다.
        int v = g->edges[i].end;  // 간선의 끝 정점을 가져옵니다.
        int weight = g->edges[i].weight;  // 간선의 가중치를 가져옵니다.

        // 두 정점이 같은 집합에 속하지 않으면 간선을 MST에 추가합니다.
        if (find(parent, u) != find(parent, v)) {
            unionSets(parent, rank, u, v);  // 두 집합을 합칩니다.
            printf("Edge (%d, %d) - Weight: %d\n", u, v, weight);  // 간선을 출력합니다.
            mst_weight += weight;  // MST의 총 가중치를 증가시킵니다.
            mst_edges++;  // MST의 간선 개수를 증가시킵니다.
        }
    }
    printf("Total MST Weight (QuickSort): %d\n\n", mst_weight);  // MST의 총 가중치를 출력합니다.
    //mst의 전체 비용을 계산하기 위해서.(비용평가 용도.)
}

// MinHeap을 사용하는 Kruskal 알고리즘
// MinHeap을 사용하여 간선을 정렬하고 Kruskal 알고리즘을 수행합니다.
void MinHeapKruskal(GraphType *g) {
    int parent[MAX_VERTICES], rank[MAX_VERTICES];  // 부모와 랭크 배열을 선언합니다.
    int mst_weight = 0;  // MST의 총 가중치를 초기화합니다.
    MinHeap h;  // 최소 힙을 선언합니다.

    initMinHeap(&h);  // 최소 힙을 초기화합니다.

    // 각 정점을 자신의 부모로 초기화하고 랭크를 0으로 설정합니다.
    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // 모든 간선을 최소 힙에 삽입합니다.
    for (int i = 0; i < g->n; i++) {
        insertMinHeap(&h, g->edges[i]);  // 간선을 힙에 삽입합니다.
    }

    printf("MinHeap 기반 Kruskal MST:\n");  // MST 시작을 알립니다.
    int mst_edges = 0;  // MST의 간선 개수를 초기화합니다.
    while (mst_edges < g->n - 1 && h.size > 0) {
        Edge e = deleteMinHeap(&h);  // 최소 가중치 간선을 추출합니다.
        int u = e.start;  // 간선의 시작 정점을 가져옵니다.
        int v = e.end;  // 간선의 끝 정점을 가져옵니다.

        // 두 정점이 같은 집합에 속하지 않으면 간선을 MST에 추가합니다.
        if (find(parent, u) != find(parent, v)) {
            unionSets(parent, rank, u, v);  // 두 집합을 합칩니다.
            printf("Edge (%d, %d) - Weight: %d\n", u, v, e.weight);  // 간선을 출력합니다.
            mst_weight += e.weight;  // MST의 총 가중치를 증가시킵니다.
            mst_edges++;  // MST의 간선 개수를 증가시킵니다.
        }
    }
    printf("Total MST Weight (MinHeap): %d\n\n", mst_weight);  // MST의 총 가중치를 출력합니다.
    //mst의 전체 비용을 계산하기 위해서.(비용평가 용도.)
}

// 과제 이미지에 맞는 간선을 추가합니다.
void GenerateGraph(GraphType *g) {
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



int main(void) {
    GraphType *g;  // 그래프 포인터를 선언합니다.
    g = (GraphType *)malloc(sizeof(GraphType));  //동적 메모리 할당.
    graph_init(g);  

    GenerateGraph(g);  //생성된 그래프 함수를 가져온다.

    QuickKruskal(g);  // QuickSort 기반 Kruskal 알고리즘을 실행.
    MinHeapKruskal(g);  // MinHeap 기반 Kruskal 알고리즘을 실행.

    free(g);  //할당된 메모리를 해제합니다.
    return 0;  // 프로그램을 종료합니다.
}