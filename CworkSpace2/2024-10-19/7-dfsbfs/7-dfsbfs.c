#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11 // 최대 11개의 정점

// 노드 구조체 정의: 인접한 정점을 연결하는 연결 리스트의 요소입니다.
typedef struct Node {
    int vertex;  // 정점 번호를 저장합니다.
    struct Node* next;  // 다음 노드를 가리킵니다.
} Node;

// 그래프 구조체 정의: 인접 리스트와 방문 여부를 관리합니다.
typedef struct Graph {
    Node* adjList[MAX_VERTICES];  // 인접 리스트를 저장합니다.
    int visited[MAX_VERTICES];  // 방문 여부를 저장합니다.
} Graph;

// 새로운 노드를 생성하는 함수입니다.
Node* CreateNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // 동적으로 메모리 할당
    newNode->vertex = v; // 정점 번호 저장
    newNode->next = NULL; // 초기화 시 다음 노드는 NULL로 설정
    return newNode;
}

// 간선을 그래프에 추가하는 함수입니다.
void AddE(Graph* graph, int src, int dest) {
    // src에서 dest로 가는 간선을 추가합니다 (양방향 그래프이므로 양쪽에 추가).
    Node* newNode = CreateNode(dest); // dest를 가리키는 새로운 노드 생성
    newNode->next = graph->adjList[src]; // src의 인접 리스트 앞에 삽입
    graph->adjList[src] = newNode;

    // dest에서 src로 가는 간선도 추가합니다.
    newNode = CreateNode(src); // src를 가리키는 새로운 노드 생성
    newNode->next = graph->adjList[dest]; // dest의 인접 리스트 앞에 삽입
    graph->adjList[dest] = newNode;
}

// 그래프를 초기화하는 함수입니다.
void InitG(Graph* graph) {
    // 인접 리스트와 방문 여부 배열을 모두 NULL과 0으로 초기화합니다.
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
}

// 방문 여부 배열을 초기화하는 함수입니다.
void RstV(Graph* graph) {
    // 모든 정점의 방문 상태를 0으로 초기화합니다.
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = 0;
    }
}

// 스택 구조체 정의: DFS를 위해 사용할 스택입니다.
typedef struct Stack {
    int* array; // 스택에 저장될 요소들의 배열
    int top;    // 스택의 상단을 가리키는 인덱스
    int capacity; // 스택의 용량
} Stack;

// 주어진 용량의 스택을 생성하는 함수입니다.
Stack* CreateStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack)); // 동적 메모리 할당
    stack->capacity = capacity; // 초기 용량 설정
    stack->top = -1; // 스택의 초기 상태 (비어있음)
    stack->array = (int*)malloc(stack->capacity * sizeof(int)); // 요소 저장용 배열 생성
    return stack;
}

// 스택이 비어있는지 확인하는 함수입니다.
int IsStackEmpty(Stack* stack) {
    return stack->top == -1; // top이 -1이면 스택이 비어있음
}

// 스택에 요소를 추가하는 함수입니다.
void Push(Stack* stack, int item) {
    // 스택이 가득 찼다면 용량을 두 배로 늘립니다.
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->array = (int*)realloc(stack->array, stack->capacity * sizeof(int)); // 메모리 재할당
    }
    stack->array[++stack->top] = item; // top을 증가시키고 새로운 요소를 저장
}

// 스택에서 요소를 제거하고 반환하는 함수입니다.
int Pop(Stack* stack) {
    if (IsStackEmpty(stack)) // 스택이 비어있으면 -1을 반환
        return -1;
    return stack->array[stack->top--]; // top의 요소를 반환하고 top을 감소시킴
}

// 스택의 메모리를 해제하는 함수입니다.
void FreeStack(Stack* stack) {
    free(stack->array); // 배열 메모리 해제
    free(stack); // 스택 구조체 메모리 해제
}

// 깊이 우선 탐색 (DFS) 함수입니다.
void Dfs(Graph* graph, int startVertex, int target) {
    Stack* stack = CreateStack(MAX_VERTICES); // DFS에 사용할 스택을 생성
    int visitedCount = 0; // 방문한 노드 수를 셉니다.

    // 시작 정점을 스택에 추가하고 방문 표시
    Push(stack, startVertex);
    graph->visited[startVertex] = 1;
    printf("탐색 과정: %d ", startVertex); // 첫 번째 정점을 출력
    visitedCount++;

    while (!IsStackEmpty(stack)) { // 스택이 빌 때까지 반복
        int currentVertex = Pop(stack); // 스택에서 현재 정점을 꺼냅니다.

        // 백트래킹 상태를 확인합니다.
        if (graph->visited[currentVertex] == 1) {
            printf("(백트래킹: %d) ", currentVertex);
            //이미 방문된 노드를 방문하면 백트래킹으로 간주하여 출력
            //이러한 방식으로 저는 백트래킹을 출력했습니다.
        }

        // 현재 정점의 인접 정점들을 탐색합니다.
        Node* temp = graph->adjList[currentVertex];
        int neighbors[MAX_VERTICES]; // 인접한 정점들을 저장할 배열
        int count = 0;

        while (temp) { // 인접 리스트를 탐색
            int adjVertex = temp->vertex;

            // 방문하지 않은 인접 정점을 neighbors 배열에 저장합니다.
            if (graph->visited[adjVertex] == 0) {
                neighbors[count++] = adjVertex;
            }
            temp = temp->next;
        }

        // 오름차순으로 인접 정점을 정렬합니다.
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (neighbors[i] > neighbors[j]) {
                    //인접한 정점중 더 작은 정점을 출력하기 위해 정렬
                    int swap = neighbors[i];
                    //swap: 더 작은 정점을 더 큰 정점보다 앞으로 이동
                    neighbors[i] = neighbors[j];
                    neighbors[j] = swap;
                }
            }
        }

        // 스택에 정렬된 인접 정점들을 추가합니다.
        for (int i = 0; i < count; i++) {
            Push(stack, neighbors[i]);
            graph->visited[neighbors[i]] = 1;
            printf("%d ", neighbors[i]); // 방문한 정점을 출력
            visitedCount++;

            // 목표 정점을 찾으면 탐색을 종료합니다.
            if (neighbors[i] == target) {
                printf("\n탐색 성공: %d\n", target);
                printf("총 방문한 노드 수: %d\n", visitedCount);
                FreeStack(stack); // 스택 메모리 해제
                return;
            }
        }
    }

    // 목표 정점을 찾지 못했을 때 출력합니다.
    printf("\n탐색 실패: %d을(를) 찾을 수 없습니다.\n", target);
    printf("총 방문한 노드 수: %d\n", visitedCount);
    FreeStack(stack); // 스택 메모리 해제
}

// 큐 구조체 정의: BFS를 위해 사용할 큐입니다.
typedef struct Queue {
    int* array; // 큐에 저장될 요소들의 배열
    int front, rear, size; // 큐의 front, rear, 크기를 나타냅니다.
    int capacity; // 큐의 용량
} Queue;

// 주어진 용량의 큐를 생성하는 함수입니다.
Queue* CreateQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue)); // 동적 메모리 할당
    queue->capacity = capacity; // 초기 용량 설정
    queue->front = queue->size = 0; // 초기 상태는 비어있음
    queue->rear = capacity - 1; // rear는 마지막 요소의 위치
    queue->array = (int*)malloc(queue->capacity * sizeof(int)); // 요소 저장용 배열 생성
    return queue;
}

// 큐가 비어있는지 확인하는 함수입니다.
int IsQueueEmpty(Queue* queue) {
    return queue->size == 0; // size가 0이면 큐가 비어있음
}

// 큐에 요소를 추가하는 함수입니다.
void Enqueue(Queue* queue, int item) {
    // 큐가 가득 찼을 때 용량을 두 배로 늘립니다.
    if (queue->size == queue->capacity) {
        queue->capacity *= 2;
        queue->array = (int*)realloc(queue->array, queue->capacity * sizeof(int)); // 메모리 재할당
    }
    queue->rear = (queue->rear + 1) % queue->capacity; // rear를 증가시키고 순환시킴
    queue->array[queue->rear] = item; // 큐에 요소를 추가
    queue->size++; // 큐의 크기를 증가시킴
}

// 큐에서 요소를 제거하고 반환하는 함수입니다.
int Dequeue(Queue* queue) {
    if (IsQueueEmpty(queue)) // 큐가 비어있으면 -1을 반환
        return -1;
    int item = queue->array[queue->front]; // front의 요소를 저장
    queue->front = (queue->front + 1) % queue->capacity; // front를 증가시키고 순환시킴
    queue->size--; // 큐의 크기를 감소시킴
    return item;
}

// 큐의 메모리를 해제하는 함수입니다.
void FreeQueue(Queue* queue) {
    free(queue->array); // 배열 메모리 해제
    free(queue); // 큐 구조체 메모리 해제
}

// 너비 우선 탐색 (BFS) 함수입니다.
void Bfs(Graph* graph, int startVertex, int target) {
    Queue* queue = CreateQueue(MAX_VERTICES); // BFS에 사용할 큐를 생성
    int visitedCount = 0; // 방문한 노드 수를 셉니다.

    // 시작 정점을 큐에 추가하고 방문 표시
    Enqueue(queue, startVertex);
    graph->visited[startVertex] = 1;
    printf("탐색 과정: %d ", startVertex); // 첫 번째 정점을 출력
    visitedCount++;

    while (!IsQueueEmpty(queue)) { // 큐가 빌 때까지 반복
        int currentVertex = Dequeue(queue); // 큐에서 현재 정점을 꺼냅니다.

        // 현재 정점의 인접 정점들을 탐색합니다.
        Node* temp = graph->adjList[currentVertex];
        int neighbors[MAX_VERTICES]; // 인접한 정점들을 저장할 배열
        int count = 0;

        while (temp) { // 인접 리스트를 탐색
            int adjVertex = temp->vertex;

            // 방문하지 않은 인접 정점을 neighbors 배열에 저장합니다.
            if (graph->visited[adjVertex] == 0) {
                neighbors[count++] = adjVertex;
            }
            temp = temp->next;
        }

        // 오름차순으로 인접 정점들을 정렬합니다.
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (neighbors[i] > neighbors[j]) {
                    int swap = neighbors[i];//인접한 정점중 더 작은 정점을 출력하기 위해 정렬
                    neighbors[i] = neighbors[j];//swap: 더 작은 정점을 더 큰 정점보다 앞으로 이동
                    neighbors[j] = swap;
                }
            }
        }

        // 큐에 정렬된 인접 정점들을 추가합니다.
        for (int i = 0; i < count; i++) {
            Enqueue(queue, neighbors[i]);
            graph->visited[neighbors[i]] = 1;
            printf("%d ", neighbors[i]); // 방문한 정점을 출력
            visitedCount++;

            // 목표 정점을 찾으면 탐색을 종료합니다.
            if (neighbors[i] == target) {
                printf("\n탐색 성공: %d\n", target);
                printf("총 방문한 노드 수: %d\n", visitedCount);
                FreeQueue(queue); // 큐 메모리 해제
                return;
            }
        }
    }

    // 목표 정점을 찾지 못했을 때 출력합니다.
    printf("\n탐색 실패: %d을(를) 찾을 수 없습니다.\n", target);
    printf("총 방문한 노드 수: %d\n", visitedCount);
    FreeQueue(queue); // 큐 메모리 해제
}

int main() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));  // 그래프를 위한 메모리를 할당합니다.
    InitG(graph);  // 그래프를 초기화합니다.

    // 그래프 구조 추가
    AddE(graph, 0, 2);  
    AddE(graph, 0, 4);  
    AddE(graph, 0, 5);  
    AddE(graph, 0, 6);  
    AddE(graph, 0, 9);  
    AddE(graph, 1, 4);  
    AddE(graph, 1, 5);  
    AddE(graph, 1, 7);  
    AddE(graph, 1, 10); 
    AddE(graph, 2, 3);  
    AddE(graph, 2, 4);  
    AddE(graph, 3, 4);  
    AddE(graph, 3, 5);  
    AddE(graph, 4, 5);  
    AddE(graph, 4, 6);  
    AddE(graph, 4, 7);  
    AddE(graph, 6, 7);  
    AddE(graph, 6, 8);  
    AddE(graph, 6, 9);  
    AddE(graph, 7, 8);  
    AddE(graph, 7, 10);  
    AddE(graph, 8, 9);  

    int choice, start, target;  

    while (1) {  
        printf("--------------\n");
        printf("|1. 깊이 우선 탐색|\n");
        printf("|2. 너비 우선 탐색|\n");
        printf("|3. 프로그램 종료|\n");
        printf("--------------\n");
        printf("선택: ");
        scanf("%d", &choice);  

        if (choice == 3) {  
            printf("프로그램을 종료합니다.\n");
            break;  // 루프를 종료합니다.
        }

        printf("시작할 정점과 탐색할 번호를 입력해주세요: ");
        scanf("%d %d", &start, &target);  

        RstV(graph); // 방문 초기화.

        if (choice == 1) {  
            Dfs(graph, start, target);  // 깊이 우선 탐색 실행
        } else if (choice == 2) {  
            Bfs(graph, start, target);  // 너비 우선 탐색 실행
        } else {
            printf("잘못된 선택입니다. 다시 시도해주세요.\n");  // 유효하지 않은 선택
        }
    }

    free(graph);  // 그래프 메모리를 해제합니다.
    return 0;  
}
