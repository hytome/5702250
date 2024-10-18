#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
// 그래프의 각 정점을 나타내는 구조체입니다.
// 각 노드는 정점 번호와 가중치, 다음 노드를 가리키는 포인터를 가집니다.
typedef struct Node {
    int vertex;  // 노드의 정점 번호를 저장합니다.
    int weight;  // 노드의 가중치를 저장합니다.
    struct Node* next;  // 다음 노드를 가리킵니다.
} Node;

// 그래프 구조체 정의
// 인접 리스트로 그래프를 나타내는 구조체입니다.
// 그래프는 정점의 수와 각 정점에 대한 인접 리스트 배열을 가집니다.
typedef struct Graph {
    int numVertices;  // 그래프의 정점 수를 나타냅니다.
    Node** adjLists;  // 각 정점에 대한 인접 리스트 배열입니다.
} Graph;

// 새로운 노드 생성
// 주어진 정점 번호와 가중치로 새로운 노드를 생성합니다.
Node* createNode(int v, int weight) {
    Node* newNode = malloc(sizeof(Node));  // 새로운 노드를 위한 메모리를 할당합니다.
    newNode->vertex = v;  // 노드의 정점 번호를 설정합니다.
    newNode->weight = weight;  // 노드의 가중치를 설정합니다.
    newNode->next = NULL;  // 초기에는 다음 노드가 없으므로 NULL로 설정합니다.
    return newNode;  // 생성된 노드를 반환합니다.
}

// 그래프 생성
// 주어진 정점 수로 그래프를 생성합니다.
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));  // 그래프 구조체를 위한 메모리를 할당합니다.
    graph->numVertices = vertices;  // 그래프의 정점 수를 설정합니다.
    graph->adjLists = malloc(vertices * sizeof(Node*));  // 각 정점에 대한 인접 리스트 배열을 위한 메모리를 할당합니다.

    // 각 정점의 인접 리스트를 초기화합니다.
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;  // 초기에는 모든 인접 리스트가 비어있습니다.
    }
    return graph;  // 생성된 그래프를 반환합니다.
}

// 간선 추가
// 주어진 출발 정점과 도착 정점, 가중치로 간선을 추가합니다.
void addEdge(Graph* graph, int src, int dest, int weight) {
    // 출발 정점의 인접 리스트에 도착 정점을 추가합니다.
    Node* newNode = createNode(dest, weight);  // 도착 정점과 가중치로 새로운 노드를 생성합니다.
    newNode->next = graph->adjLists[src];  // 새로운 노드를 출발 정점의 인접 리스트에 연결합니다.
    graph->adjLists[src] = newNode;  // 출발 정점의 인접 리스트를 갱신합니다.

    // 무방향 그래프이므로 도착 정점의 인접 리스트에도 출발 정점을 추가합니다.
    newNode = createNode(src, weight);  // 출발 정점과 가중치로 새로운 노드를 생성합니다.
    newNode->next = graph->adjLists[dest];  // 새로운 노드를 도착 정점의 인접 리스트에 연결합니다.
    graph->adjLists[dest] = newNode;  // 도착 정점의 인접 리스트를 갱신합니다.
}

// 그래프 출력
// 그래프의 각 정점에 연결된 정점들을 출력합니다.
void printGraph(Graph* graph) {
    // 각 정점에 대해 인접 리스트를 순회합니다.
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];  // 현재 정점의 인접 리스트를 가져옵니다.
        printf("\n 정점 %d에 연결된 정점들: ", v);  // 현재 정점 번호를 출력합니다.
        while (temp) {
            printf("%d(weight=%d) -> ", temp->vertex, temp->weight);  // 연결된 정점과 가중치를 출력합니다.
            temp = temp->next;  // 다음 노드로 이동합니다.
        }
        printf("NULL\n");  // 인접 리스트의 끝을 표시합니다.
    }
}

// 메인 함수
// 그래프를 생성하고 간선을 추가한 후 그래프를 출력합니다.
int main() {
    Graph* graph = createGraph(5);  // 5개의 정점을 가진 그래프를 생성합니다.
    addEdge(graph, 0, 1, 10);  // 간선을 추가합니다.
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 2, 4, 2);
    addEdge(graph, 3, 4, 7);

    printGraph(graph);  // 그래프를 출력합니다.

    return 0;  // 프로그램을 종료합니다.
}