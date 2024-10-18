#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 5  // 그래프의 최대 정점 수를 정의합니다.

// BFS 함수 정의
// 주어진 그래프와 시작 정점으로 너비 우선 탐색을 수행합니다.
void bfs(int graph[MAX_VERTICES][MAX_VERTICES], int startVertex) {
    bool visited[MAX_VERTICES] = {false};  // 각 정점의 방문 여부를 저장하는 배열을 초기화합니다.
    int queue[MAX_VERTICES];  // BFS를 위한 큐 배열을 선언합니다.
    int front = 0, rear = 0;  // 큐의 앞과 뒤를 나타내는 인덱스를 초기화합니다.

    // 시작 정점을 방문하고 큐에 삽입합니다.
    visited[startVertex] = true;  // 시작 정점을 방문했다고 표시합니다.
    queue[rear++] = startVertex;  // 시작 정점을 큐에 삽입하고 rear를 증가시킵니다.

    // 큐가 비어있지 않은 동안 반복합니다.
    while (front < rear) {
        int currentVertex = queue[front++];  // 큐의 앞에서 정점을 꺼내고 front를 증가시킵니다.
        printf("정점 %d 방문\n", currentVertex);  // 현재 방문한 정점을 출력합니다.

        // 현재 정점과 연결된 모든 정점을 확인합니다.
        for (int i = 0; i < MAX_VERTICES; i++) {
            // 간선이 존재하고 해당 정점을 방문하지 않았다면
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                queue[rear++] = i;  // 해당 정점을 큐에 추가하고 rear를 증가시킵니다.
                visited[i] = true;  // 해당 정점을 방문했다고 표시합니다.
            }
        }
    }
}

int main() {
    // 그래프의 인접 행렬을 정의합니다.
    // 간선이 있는 곳은 1, 없는 곳은 0으로 표시합니다.
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0},  // 정점 0과 연결된 정점들
        {1, 0, 0, 1, 0},  // 정점 1과 연결된 정점들
        {1, 0, 0, 1, 1},  // 정점 2와 연결된 정점들
        {0, 1, 1, 0, 1},  // 정점 3과 연결된 정점들
        {0, 0, 1, 1, 0}   // 정점 4와 연결된 정점들
    };

    bfs(graph, 0);  // 정점 0부터 BFS를 시작합니다.

    return 0;  // 프로그램을 종료합니다.
}