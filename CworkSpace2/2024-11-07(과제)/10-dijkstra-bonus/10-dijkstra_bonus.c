#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 11  // 최대 정점 수를 정의합니다.

// 노드 구조체 정의
// 그래프의 인접 리스트를 구성하는 노드입니다.
typedef struct Node {
    int vertex;  // 연결된 정점 번호
    int weight;  // 간선의 가중치
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

// 그래프 구조체 정의
// 인접 리스트로 표현된 그래프입니다.
typedef struct {
    Node* head[MAX_VERTICES];  // 각 정점의 인접 리스트의 헤드 포인터 배열
    int n;  // 그래프의 정점 개수
} GraphType;

// 최소 힙 노드 구조체 정의
// 최소 힙에 저장될 노드입니다.
typedef struct {
    int vertex;  // 정점 번호
    int distance;  // 시작 정점으로부터의 거리
} MinHeapNode;

// 최소 힙 구조체 정의
// 최소 힙을 구현하기 위한 구조체입니다.
typedef struct {
    MinHeapNode* nodes[MAX_VERTICES];  // 힙에 저장된 노드 배열
    int size;  // 힙의 현재 크기
} MinHeap;

// 그래프 초기화 함수
// 그래프의 정점 개수를 설정하고 인접 리스트를 초기화합니다.
void init_g(GraphType* g, int n) {
    g->n = n;  // 정점 개수 설정
    for (int i = 0; i < n; i++)
        g->head[i] = NULL;  // 모든 정점의 인접 리스트를 NULL로 초기화
}

// 그래프에 간선 추가 함수
// 주어진 시작 정점과 끝 정점 사이에 가중치가 있는 간선을 추가합니다.
void ins_e(GraphType* g, int start, int end, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 새로운 노드 생성
    newNode->vertex = end;  // 끝 정점 설정
    newNode->weight = weight;  // 가중치 설정
    newNode->next = g->head[start];  // 인접 리스트에 추가
    g->head[start] = newNode;  // 시작 정점의 리스트 헤드 갱신

    newNode = (Node*)malloc(sizeof(Node));  // 무방향 그래프이므로 반대 방향도 추가
    newNode->vertex = start;
    newNode->weight = weight;
    newNode->next = g->head[end];
    g->head[end] = newNode;
}

// 최소 힙 생성 함수
// 새로운 최소 힙을 생성하고 초기화합니다.
MinHeap* crt_mh() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));  // 힙 메모리 할당
    minHeap->size = 0;  // 힙 크기 초기화
    return minHeap;  // 힙 반환
}

// 힙에 노드 삽입 함수
// 주어진 정점과 거리를 가진 노드를 힙에 삽입합니다.
void ins_mh(MinHeap* minHeap, int vertex, int distance) {
    MinHeapNode* newNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));  // 새로운 힙 노드 생성
    newNode->vertex = vertex;  // 정점 설정
    newNode->distance = distance;  // 거리 설정
    minHeap->nodes[minHeap->size] = newNode;  // 힙에 노드 추가
    minHeap->size++;  // 힙 크기 증가
    // 힙 정렬 필요
}

// 힙에서 최소 노드 추출 함수
// 힙에서 가장 작은 거리의 노드를 추출합니다.
MinHeapNode* ext_min(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;  // 힙이 비어있으면 NULL 반환
    MinHeapNode* minNode = minHeap->nodes[0];  // 최소 노드 저장
    minHeap->nodes[0] = minHeap->nodes[minHeap->size - 1];  // 마지막 노드를 루트로 이동
    minHeap->size--;  // 힙 크기 감소
    // 힙 정렬 필요
    return minNode;  // 최소 노드 반환
}

// Dijkstra 알고리즘 함수
// 주어진 시작 정점에서 모든 정점까지의 최단 경로를 찾습니다.
void dijk(GraphType* g, int start) {
    int dist[MAX_VERTICES];  // 시작 정점으로부터의 거리 배열
    int visited[MAX_VERTICES] = {0};  // 방문 여부 배열
    int found_order[MAX_VERTICES];  // 방문 순서 배열
    int found_count = 0;  // 방문한 정점 수
    MinHeap* minHeap = crt_mh();  // 최소 힙 생성

    for (int i = 0; i < g->n; i++)  // 모든 정점의 거리를 무한대로 초기화
        dist[i] = INT_MAX;
    dist[start] = 0;  // 시작 정점의 거리를 0으로 설정

    ins_mh(minHeap, start, 0);  // 시작 정점을 힙에 삽입

    while (minHeap->size > 0) {  // 힙이 비어있지 않은 동안 반복
        MinHeapNode* minNode = ext_min(minHeap);  // 최소 노드 추출
        int u = minNode->vertex;  // 현재 정점
        free(minNode);  // 추출한 노드 메모리 해제

        if (visited[u]) continue;  // 이미 방문한 정점이면 건너뜀
        visited[u] = 1;  // 정점 방문 표시
        found_order[found_count++] = u;  // 방문 순서 기록

        Node* current = g->head[u];  // 현재 정점의 인접 리스트 탐색
        while (current != NULL) {
            int v = current->vertex;  // 인접 정점
            int weight = current->weight;  // 간선 가중치

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;  // 거리 갱신
                ins_mh(minHeap, v, dist[v]);  // 갱신된 거리로 힙에 삽입
            }
            current = current->next;  // 다음 인접 노드로 이동
        }

        // 거리 배열 출력
        printf("Distance: ");
        for (int k = 0; k < g->n; k++)  // 모든 정점의 거리 출력
            if (dist[k] == INT_MAX)
                printf("* ");
            else
                printf("%d ", dist[k]);
        printf("\n");

        // 방문 배열 출력
        printf("Found: ");
        for (int k = 0; k < g->n; k++)  // 모든 정점의 방문 여부 출력
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
    GraphType g;  // 그래프 구조체 선언
    init_g(&g, MAX_VERTICES);  // 그래프 초기화
    ins_e(&g, 0, 1, 3);  // 0번 정점과 연결된 간선 추가
    ins_e(&g, 1, 2, 3);
    ins_e(&g, 1, 7, 12);
    ins_e(&g, 1, 6, 11);
    ins_e(&g, 2, 5, 1);
    ins_e(&g, 2, 6, 7);
    ins_e(&g, 2, 4, 4);
    ins_e(&g, 2, 3, 8);
    ins_e(&g, 3, 4, 2);
    ins_e(&g, 3, 7, 6);
    ins_e(&g, 3, 8, 5);
    ins_e(&g, 4, 8, 14);
    ins_e(&g, 4, 10, 16);
    ins_e(&g, 5, 6, 9);
    ins_e(&g, 5, 9, 18);
    ins_e(&g, 7, 8, 13);
    ins_e(&g, 8, 10, 15);
    ins_e(&g, 9, 10, 10);

    dijk(&g, 0);  // 시작 정점을 0으로 설정하여 Dijkstra 알고리즘 실행
    return 0;  // 프로그램 종료
}