#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11 // 최대 11개의 정점

// 노드 구조체 정의
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 그래프 구조체 정의
typedef struct Graph {
    Node* adjList[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

// 함수 프로토타입 선언
Node* CreateNode(int v);
void AddE(Graph* graph, int src, int dest);
void InitG(Graph* graph);
void RstV(Graph* graph);
typedef struct StackElement StackElement;
typedef struct Stack Stack;
StackElement CreateStackElement(int v, int processed);
Stack* CreateStack(int capacity);
int IsStackEmpty(Stack* stack);
void Push(Stack* stack, StackElement elem);
StackElement Pop(Stack* stack);
void FreeStack(Stack* stack);
typedef struct Queue Queue;
Queue* CreateQueue(int capacity);
int IsQueueEmptyFunc(Queue* queue);
void Enqueue(Queue* queue, int item);
int Dequeue(Queue* queue);
void FreeQueueFunc(Queue* queue);
void Dfs(Graph* graph, int startVertex, int target);
void Bfs(Graph* graph, int startVertex, int target);
void FreeGraph(Graph* graph);

// DFS를 위한 스택 요소 구조체 정의
struct StackElement {
    int vertex;
    int processed; // 0: 처리되지 않음, 1: 처리됨 (백트래킹 준비)
};

// DFS를 위한 스택 구조체 정의
struct Stack {
    StackElement* array;
    int top;
    int capacity;
};

// 새로운 노드를 생성하는 함수
Node* CreateNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) { // 메모리 할당 실패 처리
        fprintf(stderr, "메모리 할당 실패: CreateNode\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 간선을 그래프에 추가하는 함수
void AddE(Graph* graph, int src, int dest) {
    if (src < 0 || src >= MAX_VERTICES || dest < 0 || dest >= MAX_VERTICES) {
        fprintf(stderr, "잘못된 정점 번호: src=%d, dest=%d\n", src, dest);
        return;
    }

    // src에서 dest로 가는 간선을 추가
    Node* newNode = CreateNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // dest에서 src로 가는 간선도 추가 (양방향)
    newNode = CreateNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// 그래프를 초기화하는 함수
void InitG(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
}

// 방문 여부 배열을 초기화하는 함수
void RstV(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = 0;
    }
}

// 새로운 스택 요소를 생성하는 함수
StackElement CreateStackElement(int v, int processed) {
    StackElement elem;
    elem.vertex = v;
    elem.processed = processed;
    return elem;
}

// 주어진 용량의 스택을 생성하는 함수
Stack* CreateStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) { // 메모리 할당 실패 처리
        fprintf(stderr, "메모리 할당 실패: CreateStack\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (StackElement*)malloc(stack->capacity * sizeof(StackElement));
    if (stack->array == NULL) { // 메모리 할당 실패 처리
        fprintf(stderr, "메모리 할당 실패: Stack array\n");
        free(stack);
        exit(EXIT_FAILURE);
    }
    return stack;
}

// 스택이 비어있는지 확인하는 함수
int IsStackEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택에 요소를 추가하는 함수
void Push(Stack* stack, StackElement elem) {
    if (stack->top == stack->capacity - 1) {
        int newCapacity = stack->capacity * 2;
        StackElement* temp = (StackElement*)realloc(stack->array, newCapacity * sizeof(StackElement));
        if (temp == NULL) { // realloc 실패 처리
            fprintf(stderr, "메모리 재할당 실패: Push\n");
            FreeStack(stack);
            exit(EXIT_FAILURE);
        }
        stack->array = temp;
        stack->capacity = newCapacity;
    }
    stack->array[++stack->top] = elem;
}

// 스택에서 요소를 제거하고 반환하는 함수
StackElement Pop(Stack* stack) {
    if (IsStackEmpty(stack)) {
        StackElement empty = { -1, -1 };
        return empty;
    }
    return stack->array[stack->top--];
}

// 스택의 메모리를 해제하는 함수
void FreeStack(Stack* stack) {
    if (stack != NULL) {
        free(stack->array);
        free(stack);
    }
}

// 큐 구조체 정의: BFS를 위해 사용할 큐입니다.
struct Queue {
    int* array; // 큐에 저장될 요소들의 배열
    int front, rear, size; // 큐의 front, rear, 크기를 나타냅니다.
    int capacity; // 큐의 용량
};

// 주어진 용량의 큐를 생성하는 함수
Queue* CreateQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) { // 메모리 할당 실패 처리
        fprintf(stderr, "메모리 할당 실패: CreateQueue\n");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    if (queue->array == NULL) { // 메모리 할당 실패 처리
        fprintf(stderr, "메모리 할당 실패: Queue array\n");
        free(queue);
        exit(EXIT_FAILURE);
    }
    return queue;
}

// 큐가 비어있는지 확인하는 함수
int IsQueueEmptyFunc(Queue* queue) {
    return queue->size == 0;
}

// 큐에 요소를 추가하는 함수
void Enqueue(Queue* queue, int item) {
    if (queue->size == queue->capacity) {
        int newCapacity = queue->capacity * 2;
        int* temp = (int*)realloc(queue->array, newCapacity * sizeof(int));
        if (temp == NULL) { // realloc 실패 처리
            fprintf(stderr, "메모리 재할당 실패: Enqueue\n");
            FreeQueueFunc(queue);
            exit(EXIT_FAILURE);
        }
        queue->array = temp;
        queue->capacity = newCapacity;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

// 큐에서 요소를 제거하고 반환하는 함수
int Dequeue(Queue* queue) {
    if (IsQueueEmptyFunc(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// 큐의 메모리를 해제하는 함수
void FreeQueueFunc(Queue* queue) {
    if (queue != NULL) {
        free(queue->array);
        free(queue);
    }
}

// 깊이 우선 탐색 (DFS) 함수
void Dfs(Graph* graph, int startVertex, int target) {
    if (startVertex < 0 || startVertex >= MAX_VERTICES || target < 0 || target >= MAX_VERTICES) {
        fprintf(stderr, "잘못된 정점 번호: startVertex=%d, target=%d\n", startVertex, target);
        return;
    }

    Stack* stack = CreateStack(MAX_VERTICES);
    int visitedCount = 0;

    // 시작 정점을 스택에 추가 (처리되지 않은 상태)
    Push(stack, CreateStackElement(startVertex, 0));

    while (!IsStackEmpty(stack)) {
        StackElement currentElement = Pop(stack);
        int currentVertex = currentElement.vertex;

        if (currentElement.processed == 1) {
            // 백트래킹 단계
            printf("(백트래킹: %d) ", currentVertex);
            continue;
        }

        if (graph->visited[currentVertex]) {
            // 이미 방문한 정점이라면 백트래킹
            printf("(백트래킹: %d) ", currentVertex);
            continue;
        }

        // 현재 정점을 방문 처리
        graph->visited[currentVertex] = 1;
        printf("%d ", currentVertex);
        visitedCount++;

        // 목표 정점을 찾았을 경우 종료
        if (currentVertex == target) {
            printf("\n탐색 성공: %d\n", target);
            printf("총 방문한 노드 수: %d\n", visitedCount);
            FreeStack(stack);
            return;
        }

        // 현재 정점을 다시 스택에 추가하여 백트래킹을 위한 처리
        Push(stack, CreateStackElement(currentVertex, 1));

        // 인접 정점들을 탐색
        Node* temp = graph->adjList[currentVertex];
        int neighbors[MAX_VERTICES];
        int count = 0;

        while (temp) {
            int adjVertex = temp->vertex;
            if (graph->visited[adjVertex] == 0) {
                neighbors[count++] = adjVertex;
            }
            temp = temp->next;
        }

        // 오름차순으로 정렬한 후, 내림차순으로 스택에 푸시
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (neighbors[i] < neighbors[j]) { // 내림차순 정렬
                    int swap = neighbors[i];
                    neighbors[i] = neighbors[j];
                    neighbors[j] = swap;
                }
            }
        }

        // 정렬된 인접 정점들을 스택에 추가
        for (int i = 0; i < count; i++) {
            Push(stack, CreateStackElement(neighbors[i], 0));
        }
    }

    // 목표 정점을 찾지 못했을 때 출력
    printf("\n탐색 실패: %d을(를) 찾을 수 없습니다.\n", target);
    printf("총 방문한 노드 수: %d\n", visitedCount);
    FreeStack(stack);
}

// 너비 우선 탐색 (BFS) 함수입니다.
void Bfs(Graph* graph, int startVertex, int target) {
    if (startVertex < 0 || startVertex >= MAX_VERTICES || target < 0 || target >= MAX_VERTICES) {
        fprintf(stderr, "잘못된 정점 번호: startVertex=%d, target=%d\n", startVertex, target);
        return;
    }

    Queue* queue = CreateQueue(MAX_VERTICES);
    int visitedCount = 0;

    // 시작 정점을 큐에 추가하고 방문 표시
    Enqueue(queue, startVertex);
    graph->visited[startVertex] = 1;
    printf("탐색 과정: %d ", startVertex);
    visitedCount++;

    while (!IsQueueEmptyFunc(queue)) {
        int currentVertex = Dequeue(queue);

        // 현재 정점의 인접 정점들을 탐색합니다.
        Node* temp = graph->adjList[currentVertex];
        int neighbors[MAX_VERTICES];
        int count = 0;

        while (temp) {
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
                    int swap = neighbors[i]; // 인접한 정점 중 더 작은 정점을 앞으로 이동
                    neighbors[i] = neighbors[j];
                    neighbors[j] = swap;
                }
            }
        }

        // 큐에 정렬된 인접 정점들을 추가합니다.
        for (int i = 0; i < count; i++) {
            Enqueue(queue, neighbors[i]);
            graph->visited[neighbors[i]] = 1;
            printf("%d ", neighbors[i]);
            visitedCount++;

            // 목표 정점을 찾으면 탐색을 종료합니다.
            if (neighbors[i] == target) {
                printf("\n탐색 성공: %d\n", target);
                printf("총 방문한 노드 수: %d\n", visitedCount);
                FreeQueueFunc(queue);
                return;
            }
        }
    }

    // 목표 정점을 찾지 못했을 때 출력합니다.
    printf("\n탐색 실패: %d을(를) 찾을 수 없습니다.\n", target);
    printf("총 방문한 노드 수: %d\n", visitedCount);
    FreeQueueFunc(queue);
}

// 그래프의 모든 노드를 해제하는 함수
void FreeGraph(Graph* graph) {
    if (graph == NULL)
        return;

    for (int i = 0; i < MAX_VERTICES; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph);
}

int main() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));  // 그래프를 위한 메모리를 할당합니다.
    if (graph == NULL) { // 메모리 할당 실패 처리
        fprintf(stderr, "메모리 할당 실패: Graph\n");
        exit(EXIT_FAILURE);
    }
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
        if (scanf("%d", &choice) != 1) { // 입력 유효성 검사
            fprintf(stderr, "입력 오류: 정수를 입력해주세요.\n");
            // 입력 버퍼를 비웁니다.
            while (getchar() != '\n');
            continue;
        }

        if (choice == 3) {  
            printf("프로그램을 종료합니다.\n");
            break;  // 루프를 종료합니다.
        }

        printf("시작할 정점과 탐색할 번호를 입력해주세요: ");
        if (scanf("%d %d", &start, &target) != 2) { // 입력 유효성 검사
            fprintf(stderr, "입력 오류: 두 개의 정수를 입력해주세요.\n");
            // 입력 버퍼를 비웁니다.
            while (getchar() != '\n');
            continue;
        }

        // 정점 번호 유효성 검사
        if (start < 0 || start >= MAX_VERTICES || target < 0 || target >= MAX_VERTICES) {
            fprintf(stderr, "정점 번호는 0 이상 %d 이하이어야 합니다.\n", MAX_VERTICES - 1);
            continue;
        }

        RstV(graph); // 방문 초기화.

        if (choice == 1) {  
            Dfs(graph, start, target);  // 깊이 우선 탐색 실행
        } else if (choice == 2) {  
            Bfs(graph, start, target);  // 너비 우선 탐색 실행
        } else {
            printf("잘못된 선택입니다. 다시 시도해주세요.\n");  // 유효하지 않은 선택
        }
    }

    // 그래프의 모든 노드를 해제합니다.
    FreeGraph(graph);
    return 0;  
}
