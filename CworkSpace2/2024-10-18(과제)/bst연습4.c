#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11

// 그래프의 노드를 나타내는 구조체
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 스택 프레임 구조체
typedef struct StackFrame {
    int vertex;
    struct Node* nextEdge;
    int visited[MAX_VERTICES];
} StackFrame;

// 스택 구조체 (동적 할당으로 구현)
typedef struct Stack {
    StackFrame* frames;
    int top;
    int capacity;
} Stack;

// 스택 초기화
Stack* initStack(int initialCapacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s) {
        printf("메모리 할당 실패!\n");
        exit(1);
    }
    s->frames = (StackFrame*)malloc(initialCapacity * sizeof(StackFrame));
    s->top = -1;
    s->capacity = initialCapacity;
    return s;
}

// 스택 크기 늘리기
void resizeStack(Stack* s) {
    s->capacity *= 2;
    s->frames = (StackFrame*)realloc(s->frames, s->capacity * sizeof(StackFrame));
    if (!s->frames) {
        printf("메모리 재할당 실패!\n");
        exit(1);
    }
}

// 스택에 프레임 추가
void push(Stack* s, StackFrame frame) {
    if (s->top == s->capacity - 1) {
        resizeStack(s);
    }
    s->frames[++(s->top)] = frame;
}

// 스택에서 프레임 꺼내기
StackFrame pop(Stack* s) {
    if (s->top == -1) {
        printf("스택 언더플로우 발생!\n");
        exit(1);
    }
    return s->frames[(s->top)--];
}

// 스택이 비었는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택 메모리 해제
void freeStack(Stack* s) {
    free(s->frames);
    free(s);
}

// 그래프 노드 생성
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("메모리 할당 실패!\n");
        exit(1);
    }
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 인접 노드들을 정렬된 순서로 삽입
void sortedInsert(Node** head, int vertex) {
    Node* newNode = createNode(vertex);
    if (*head == NULL || (*head)->vertex > vertex) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL && current->next->vertex < vertex) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

// 간선 추가 함수
void addEdge(Node* adjList[], int src, int dest) {
    sortedInsert(&adjList[src], dest);
    sortedInsert(&adjList[dest], src);
}

// DFS 탐색 함수 (명시적 스택 사용)
void dfs(Node* adjList[], int startVertex, int targetVertex) {
    int visitCount = 0;
    int found = 0;

    Stack* stack = initStack(100);

    // 초기 스택 프레임 생성
    StackFrame initialFrame;
    initialFrame.vertex = startVertex;
    initialFrame.nextEdge = adjList[startVertex];
    for (int i = 0; i < MAX_VERTICES; i++)
        initialFrame.visited[i] = 0;
    initialFrame.visited[startVertex] = 1;

    push(stack, initialFrame);

    while (!isEmpty(stack)) {
        StackFrame* currentFrame = &stack->frames[stack->top];

        if (currentFrame->nextEdge != NULL) {
            int nextVertex = currentFrame->nextEdge->vertex;
            currentFrame->nextEdge = currentFrame->nextEdge->next;

            if (!currentFrame->visited[nextVertex]) {
                // 방문 횟수 증가 및 노드 출력
                visitCount++;
                printf("%d ", nextVertex);

                // 목표 정점을 찾으면 종료
                if (nextVertex == targetVertex) {
                    printf("\n목표 정점 %d을(를) 찾았습니다.\n", targetVertex);
                    printf("방문한 노드의 횟수: %d\n", visitCount);
                    freeStack(stack);
                    return;
                }

                // 새로운 스택 프레임 생성
                StackFrame newFrame;
                newFrame.vertex = nextVertex;
                newFrame.nextEdge = adjList[nextVertex];
                // 현재 경로의 방문 정보 복사
                for (int i = 0; i < MAX_VERTICES; i++)
                    newFrame.visited[i] = currentFrame->visited[i];
                newFrame.visited[nextVertex] = 1;

                push(stack, newFrame);
            }
        } else {
            // 백트래킹 시 노드 출력 및 방문 횟수 증가
            visitCount++;
            printf("%d ", currentFrame->vertex);
            pop(stack);
        }
    }

    printf("\n목표 정점 %d을(를) 찾을 수 없습니다.\n", targetVertex);
    printf("방문한 노드의 횟수: %d\n", visitCount);
    freeStack(stack);
}

// 메모리 해제 함수
void freeGraph(Node* adjList[]) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        Node* temp = adjList[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
}

int main() {
    Node* adjList[MAX_VERTICES] = {NULL};

    // 그래프 간선 추가 (조교님의 그래프 구조에 맞춤)
    addEdge(adjList, 0, 2);
    addEdge(adjList, 0, 4);
    addEdge(adjList, 0, 5);
    addEdge(adjList, 0, 6);
    addEdge(adjList, 0, 9);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 1, 5);
    addEdge(adjList, 1, 7);
    addEdge(adjList, 1, 10);
    addEdge(adjList, 2, 3);
    addEdge(adjList, 2, 4);
    addEdge(adjList, 3, 4);
    addEdge(adjList, 3, 5);
    addEdge(adjList, 4, 5);
    addEdge(adjList, 4, 6);
    addEdge(adjList, 4, 7);
    addEdge(adjList, 6, 7);
    addEdge(adjList, 6, 8);
    addEdge(adjList, 6, 9);
    addEdge(adjList, 7, 8);
    addEdge(adjList, 7, 10);
    addEdge(adjList, 8, 9);

    int startVertex, targetVertex;

    // 시작 정점과 목표 정점 입력
    printf("시작 정점을 입력하세요 (0 ~ 10): ");
    scanf("%d", &startVertex);
    printf("목표 정점을 입력하세요 (0 ~ 10): ");
    scanf("%d", &targetVertex);

    // 시작 정점 출력 및 방문 횟수 증가
    printf("DFS 탐색 순서: ");
    printf("%d ", startVertex);

    // DFS 탐색 시작
    dfs(adjList, startVertex, targetVertex);

    // 메모리 해제
    freeGraph(adjList);

    return 0;
}
