#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11

// 그래프의 노드를 나타내는 구조체
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 스택 구조체 (동적 할당으로 구현)
typedef struct Stack {
    int* items;
    int top;
    int capacity;
} Stack;

// 스택 초기화 (동적 할당)
Stack* initStack(int initialCapacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s) {
        printf("메모리 할당 실패!\n");
        exit(1);
    }
    s->items = (int*)malloc(initialCapacity * sizeof(int));
    s->top = -1;
    s->capacity = initialCapacity;
    return s;
}

// 스택이 비었는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택 크기 늘리기
void resizeStack(Stack* s) {
    s->capacity *= 2;
    s->items = (int*)realloc(s->items, s->capacity * sizeof(int));
    if (!s->items) {
        printf("메모리 재할당 실패!\n");
        exit(1);
    }
}

// 스택에 값 넣기 (동적 할당)
void push(Stack* s, int value) {
    if (s->top == s->capacity - 1) {
        resizeStack(s);
    }
    s->items[++(s->top)] = value;
}

// 스택에서 값 꺼내기
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("스택 언더플로우 발생!\n");
        return -1;
    }
    return s->items[(s->top)--];
}

// 스택 메모리 해제
void freeStack(Stack* s) {
    free(s->items);
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

// DFS 탐색 함수
void dfs(Node* adjList[], int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Stack* s = initStack(10);

    push(s, startVertex);  // 시작 정점 스택에 추가

    while (!isEmpty(s)) {
        int currentVertex = pop(s);

        // 방문되지 않은 경우, 방문 처리 및 출력
        if (!visited[currentVertex]) {
            visited[currentVertex] = 1;
            printf("%d ", currentVertex);  // 방문한 노드 출력
        }

        // 인접 노드를 역순으로 스택에 넣기
        Node* temp = adjList[currentVertex];
        int tempStack[MAX_VERTICES];  // 임시 배열
        int tempTop = -1;

        // 인접 노드를 역순으로 스택에 추가하기 위해 임시 배열 사용
        while (temp) {
            if (!visited[temp->vertex]) {  // 미방문 노드만 스택에 추가
                tempStack[++tempTop] = temp->vertex;
            }
            temp = temp->next;
        }

        // 작은 값이 나중에 들어가게 역순으로 스택에 추가
        while (tempTop != -1) {
            push(s, tempStack[tempTop--]);
        }
    }

    freeStack(s);  // 스택 메모리 해제
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

    printf("DFS 탐색 순서: ");
    dfs(adjList, 1);  // DFS 탐색 시작 (시작 정점: 1)
    
    printf("\n");

    // 메모리 해제
    freeGraph(adjList);

    return 0;
}
