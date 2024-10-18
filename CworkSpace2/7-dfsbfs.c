#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 11
#define MAX_STACK_SIZE 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

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

void addEdge(Node* adjList[], int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
}

void dfsIterative(Node* adjList[], int startVertex, int searchValue, int* visitedCount, bool* found) {
    int stack[MAX_STACK_SIZE];
    int top = -1;
    stack[++top] = startVertex;

    bool visited[MAX_VERTICES] = {false};
    int visitCount[MAX_VERTICES] = {0};  // 각 노드의 방문 횟수를 기록
    const int visitLimit = 3;  // 각 노드가 최대 세 번까지 방문되도록 제한 (예: 2, 3, 5 등이 중복 방문됨)

    while (top != -1) {
        int vertex = stack[top--];

        // 방문 횟수가 제한을 초과하지 않으면 방문 처리
        if (visitCount[vertex] < visitLimit) {
            printf("%d ", vertex);
            visitCount[vertex]++;  // 방문 횟수 증가
            (*visitedCount)++;

            if (vertex == searchValue) {
                *found = true;
            }

            // 인접 노드를 역순으로 스택에 넣음
            Node* temp = adjList[vertex];
            int tempStack[MAX_STACK_SIZE];
            int tempTop = -1;

            while (temp) {
                if (visitCount[temp->vertex] < visitLimit) {  // 방문 횟수가 제한을 넘지 않는 노드만 스택에 추가
                    tempStack[++tempTop] = temp->vertex;
                }
                temp = temp->next;
            }

            while (tempTop != -1) {
                stack[++top] = tempStack[tempTop--];
            }
        }
    }
}

void bfs(Node* adjList[], int startVertex, int searchValue, int* visitedCount, bool* found) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);
        (*visitedCount)++;

        if (currentVertex == searchValue) {
            *found = true;
        }

        Node* temp = adjList[currentVertex];
        while (temp) {
            int connectedVertex = temp->vertex;
            if (!visited[connectedVertex]) {
                queue[rear++] = connectedVertex;
                visited[connectedVertex] = true;
            }
            temp = temp->next;
        }
    }
}

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

    // 그래프 연결
    addEdge(adjList, 0, 5);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 0, 6);
    addEdge(adjList, 0, 9);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 1, 7);
    addEdge(adjList, 1, 10);
    addEdge(adjList, 2, 3);
    addEdge(adjList, 2, 4);
    addEdge(adjList, 3, 5);
    addEdge(adjList, 4, 6);
    addEdge(adjList, 4, 7);
    addEdge(adjList, 6, 8);
    addEdge(adjList, 8, 9);

    int choice, startVertex, searchValue;
    while (1) {
        printf("\n\n메뉴를 선택하세요 (1: DFS, 2: BFS, 0: 종료): ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        printf("시작 정점과 탐색할 값을 입력하세요 (예: 1 9): ");
        scanf("%d %d", &startVertex, &searchValue);

        int visitedCount = 0;
        bool found = false;

        if (choice == 1) {
            dfsIterative(adjList, startVertex, searchValue, &visitedCount, &found);
        } else if (choice == 2) {
            bfs(adjList, startVertex, searchValue, &visitedCount, &found);
        } else {
            printf("잘못된 선택입니다.\n");
            continue;
        }

        if (found) {
            printf("\n탐색 성공: %d\n", searchValue);
        } else {
            printf("\n경고: 데이터가 없습니다.\n");
        }
        printf("방문한 노드의 수: %d\n", visitedCount);
    }

    freeGraph(adjList);
    return 0;
}
