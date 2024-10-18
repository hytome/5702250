#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 5  // 그래프의 최대 정점 수를 정의합니다.

// 방문한 정점을 기록하는 배열
// 각 정점이 방문되었는지를 나타내는 불리언 배열입니다.
//불리언 배열은 참 거짓 두가지 값을 가질수 있는 자료형을 가진 배열.
//따라서 각 정점이 방문되었는지 참 거짓으로 표현.
bool visited[MAX_VERTICES] = {false};

// 스택을 사용한 깊이 우선 탐색(DFS) 함수
// 주어진 그래프와 시작 정점에서 DFS를 수행합니다.
void dfs_stack(int graph[MAX_VERTICES][MAX_VERTICES], int start_vertex) {
    int stack[MAX_VERTICES];  // DFS를 위한 스택을 정의합니다.
    int top = -1;  // 스택의 최상단을 나타내는 인덱스를 초기화합니다.

    // 스택에 시작 정점을 추가
    stack[++top] = start_vertex;  // 시작 정점을 스택에 푸시합니다.

    // 스택이 비어있지 않은 동안 반복합니다.
    while (top != -1) {
        int vertex = stack[top--];  // 스택에서 정점을 꺼냅니다.

        // 현재 정점이 방문되지 않았다면
        if (!visited[vertex]) {
            visited[vertex] = true;  // 정점을 방문으로 표시합니다.
            printf("정점 %d 방문\n", vertex);  // 방문한 정점을 출력합니다.

            // 현재 정점과 연결된 모든 정점을 스택에 추가
            // 인접한 정점을 역순으로 스택에 추가하여 올바른 순서로 탐색합니다.
            for (int i = MAX_VERTICES - 1; i >= 0; i--) {
                // 인접 정점이 존재하고 방문되지 않았다면
                if (graph[vertex][i] == 1 && !visited[i]) {
                    stack[++top] = i;  // 인접 정점을 스택에 푸시합니다.
                }
            }
        }
    }
}

int main() {
    // 그래프의 인접 행렬 표현
    // 간선이 있는 곳은 1, 없는 곳은 0으로 표시합니다.
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0},  // 정점 0과 연결된 정점들
        {1, 0, 0, 1, 0},  // 정점 1과 연결된 정점들
        {1, 0, 0, 1, 1},  // 정점 2와 연결된 정점들
        {0, 1, 1, 0, 1},  // 정점 3과 연결된 정점들
        {0, 0, 1, 1, 0}   // 정점 4와 연결된 정점들
    };

    dfs_stack(graph, 0);  // 정점 0부터 DFS를 시작합니다.

    return 0;  // 프로그램을 종료합니다.
}