#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10  // 정점 수를 10으로 수정

// 노드 구조체 정의
// 인접 리스트의 노드를 나타내는 구조체입니다.
// 정점 번호, 가중치, 다음 노드를 가리키는 포인터를 가집니다.
typedef struct Node {
    int vertex;  // 정점 번호
    int weight;  // 간선의 가중치
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

// 그래프 구조체 정의
// 인접 리스트로 그래프를 나타내는 구조체입니다.
// 각 정점의 인접 리스트의 헤드 포인터 배열과 정점의 개수를 가집니다.
typedef struct {
    Node* head[MAX_VERTICES + 1];  // 인접 리스트의 헤드 포인터 배열 (1~10)
    int n;  // 그래프의 정점 개수
} GraphType;

// 최소 힙 노드 구조체 정의
// 최소 힙의 노드를 나타내는 구조체입니다.
// 정점 번호와 해당 정점까지의 거리를 가집니다.
typedef struct {
    int vertex;  // 정점 번호
    int distance;  // 해당 정점까지의 거리
} MinHeapNode;

// 최소 힙 구조 정의
// 최소 힙을 나타내는 구조체입니다.
// 힙 노드 배열과 힙의 크기를 가집니다.
typedef struct {
    MinHeapNode* nodes[MAX_VERTICES * 2 + 1];  // 힙 크기 확장
    int size;  // 힙의 현재 크기
} MinHeap;

// 그래프 초기화 함수
// 그래프를 초기화합니다.
void init_g(GraphType* g, int n) {
    g->n = n;  // 그래프의 정점 개수를 설정합니다.
    for (int i = 0; i <= n; i++)  // 모든 정점의 인접 리스트를 초기화합니다.
        g->head[i] = NULL;  // 인접 리스트의 헤드를 NULL로 초기화
}

// 그래프에 간선 추가 함수
// 그래프에 새로운 간선을 추가합니다.
void ins_e(GraphType* g, int start, int end, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 새로운 노드 생성
    newNode->vertex = end;  // 끝 정점 설정
    newNode->weight = weight;  // 가중치 설정
    newNode->next = g->head[start];  // 현재 시작 정점의 헤드를 다음 노드로 설정
    g->head[start] = newNode;  // 시작 정점의 헤드를 새로운 노드로 설정

    // 무방향 그래프이므로 반대 방향도 추가
    newNode = (Node*)malloc(sizeof(Node));  // 새로운 노드 생성
    newNode->vertex = start;  // 시작 정점 설정
    newNode->weight = weight;  // 가중치 설정
    newNode->next = g->head[end];  // 현재 끝 정점의 헤드를 다음 노드로 설정
    g->head[end] = newNode;  // 끝 정점의 헤드를 새로운 노드로 설정
}

// 최소 힙 생성 함수
// 새로운 최소 힙을 생성합니다.
MinHeap* crt_mh() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));  // 최소 힙을 위한 동적 메모리 할당
    minHeap->size = 0;  // 힙의 크기를 0으로 초기화
    return minHeap;  // 생성된 최소 힙 반환
}

// 힙의 위로 올리기 함수
// 힙의 속성을 유지하기 위해 삽입된 노드를 위로 올립니다.
void up_heapify(MinHeap* minHeap, int idx) {
    while (idx && minHeap->nodes[(idx - 1) / 2]->distance > minHeap->nodes[idx]->distance) {
        MinHeapNode* temp = minHeap->nodes[idx];  // 현재 노드와 부모 노드를 교환
        minHeap->nodes[idx] = minHeap->nodes[(idx - 1) / 2];
        minHeap->nodes[(idx - 1) / 2] = temp;
        idx = (idx - 1) / 2;  // 부모 인덱스로 이동
    }
}

// 힙에 노드 삽입 함수
// 최소 힙에 새로운 노드를 삽입합니다.
void ins_mh(MinHeap* minHeap, int vertex, int distance) {
    MinHeapNode* newNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));  // 새로운 힙 노드 생성
    newNode->vertex = vertex;  // 정점 번호 설정
    newNode->distance = distance;  // 거리 설정
    minHeap->nodes[minHeap->size] = newNode;  // 힙의 끝에 새로운 노드 추가
    minHeap->size++;  // 힙의 크기 증가
    
    up_heapify(minHeap, minHeap->size - 1);  // 힙 속성 유지
}

// 힙의 아래로 내리기 함수
// 힙의 속성을 유지하기 위해 루트 노드를 아래로 내립니다.
void down_heapify(MinHeap* minHeap, int idx) {
    int smallest = idx;  // 가장 작은 노드의 인덱스
    int left = 2 * idx + 1;  // 왼쪽 자식 인덱스
    int right = 2 * idx + 2;  // 오른쪽 자식 인덱스

    if (left < minHeap->size && minHeap->nodes[left]->distance < minHeap->nodes[smallest]->distance)
        smallest = left;  // 왼쪽 자식이 더 작으면 smallest 갱신

    if (right < minHeap->size && minHeap->nodes[right]->distance < minHeap->nodes[smallest]->distance)
        smallest = right;  // 오른쪽 자식이 더 작으면 smallest 갱신

    if (smallest != idx) {  // smallest가 변경되었으면 교환
        MinHeapNode* temp = minHeap->nodes[idx];
        minHeap->nodes[idx] = minHeap->nodes[smallest];
        minHeap->nodes[smallest] = temp;
        down_heapify(minHeap, smallest);  // 재귀적으로 아래로 내리기
    }
}

// 힙에서 최소 노드 추출 함수
// 최소 힙에서 최소 노드를 추출합니다.
MinHeapNode* ext_min(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;  // 힙이 비어있으면 NULL 반환
    MinHeapNode* minNode = minHeap->nodes[0];  // 루트 노드가 최소 노드
    minHeap->nodes[0] = minHeap->nodes[minHeap->size - 1];  // 마지막 노드를 루트로 이동
    minHeap->size--;  // 힙의 크기 감소
    down_heapify(minHeap, 0);  // 힙 속성 유지
    return minNode;  // 최소 노드 반환
}

// 그래프의 모든 노드를 해제하는 함수
// 그래프의 인접 리스트에 할당된 모든 노드를 해제합니다.
void free_graph(GraphType* g) {
    for (int i = 0; i <= g->n; i++) {
        Node* current = g->head[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);  // 노드 메모리 해제
        }
    }
}

// 최소 힙의 모든 노드를 해제하는 함수
// 최소 힙에 할당된 모든 노드를 해제합니다.
void free_min_heap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        free(minHeap->nodes[i]);  // 힙 노드 메모리 해제
    }
    free(minHeap);  // 힙 구조체 메모리 해제
}

// Dijkstra 알고리즘 함수
// Dijkstra 알고리즘을 사용하여 최단 경로를 찾습니다.
void dijk(GraphType* g, int start) {
    int dist[MAX_VERTICES + 1];  // 각 정점까지의 최단 거리를 저장하는 배열
    int visited[MAX_VERTICES + 1] = {0};  // 방문 여부를 추적하는 배열
    int found_order[MAX_VERTICES + 1];  // 방문 순서를 저장하는 배열
    int found_count = 0;  // 방문한 정점의 수
    MinHeap* minHeap = crt_mh();  // 최소 힙 생성

    for (int i = 1; i <= g->n; i++)
        dist[i] = INT_MAX;  // 모든 정점의 거리를 무한대로 초기화
    dist[start] = 0;  // 시작 정점의 거리를 0으로 설정

    ins_mh(minHeap, start, 0);  // 시작 정점을 힙에 삽입

    while (minHeap->size > 0) {  // 힙이 비어있지 않은 동안 반복
        MinHeapNode* minNode = ext_min(minHeap);  // 최소 노드 추출
        int u = minNode->vertex;  // 현재 정점
        free(minNode);  // 추출된 노드 메모리 해제

        if (visited[u]) continue;  // 이미 방문한 정점이면 건너뜀
        visited[u] = 1;  // 현재 정점을 방문으로 표시
        found_order[found_count++] = u;  // 방문 순서에 추가

        Node* current = g->head[u];  // 현재 정점의 인접 리스트 탐색
        while (current != NULL) {  // 인접 리스트의 끝까지 반복
            int v = current->vertex;  // 인접 정점
            int weight = current->weight;  // 간선의 가중치

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;  // 최단 거리 갱신
                ins_mh(minHeap, v, dist[v]);  // 갱신된 정점을 힙에 삽입
            }
            current = current->next;  // 다음 인접 노드로 이동
        }

        // 거리 배열 출력
        printf("Distance: ");
        for (int k = 1; k <= g->n; k++)
            if (dist[k] == INT_MAX)
                printf("* ");  // 무한대는 *로 표시
            else
                printf("%d ", dist[k]);  // 거리 출력
        printf("\n");

        // 방문 배열 출력
        printf("Found: ");
        for (int k = 1; k <= g->n; k++)
            printf("%d ", visited[k]);  // 방문 여부 출력
        printf("\n\n");
    }

    // 방문 순서 출력
    printf("Found Order: ");
    for (int i = 0; i < found_count; i++)
        printf("%d ", found_order[i]);  // 방문 순서 출력
    printf("\n");

    free_min_heap(minHeap);  // 최소 힙 메모리 해제
}

int main() {
    GraphType g;  // 그래프 구조체 선언
    init_g(&g, MAX_VERTICES);  // 그래프 초기화
    ins_e(&g, 1, 2, 3);  // 간선 추가
    ins_e(&g, 1, 7, 12);
    ins_e(&g, 1, 6, 11);
    ins_e(&g, 2, 5, 1);
    ins_e(&g, 2, 3, 5);
    ins_e(&g, 2, 4, 4);
    ins_e(&g, 2, 6, 7);
    ins_e(&g, 2, 7, 8);
    ins_e(&g, 3, 4, 2);
    ins_e(&g, 3, 7, 6);
    ins_e(&g, 3, 8, 5);
    ins_e(&g, 4, 8, 14);
    ins_e(&g, 4, 5, 13);
    ins_e(&g, 4, 10, 16);
    ins_e(&g, 5, 6, 9);
    ins_e(&g, 5, 10, 17); 
    ins_e(&g, 5, 9, 18);
    ins_e(&g, 7, 8, 13);
    ins_e(&g, 8, 10, 15);
    ins_e(&g, 9, 10, 10);

    dijk(&g, 1);  // Dijkstra 알고리즘 실행

    free_graph(&g);  // 그래프 메모리 해제
    return 0;  // 프로그램 종료
}