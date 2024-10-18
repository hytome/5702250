#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 50 // 최대 정점의 수를 50으로 정의한다.
typedef struct GraphType{
    int n; // 정점의 갯수.
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬 선언.
}GraphType;

//그래프 초기화.
void init(GraphType* g){
    int r,c; // 반복문을 위한 변수 선언.
    g->n = 0; // 정점의 갯수를 0으로 초기화.
    for(r = 0; r<MAX_VERTICES; r++) { // 행을 반복하면서
        for(c = 0; c<MAX_VERTICES; c++) { // 열을 반복하면서
            g->adj_mat[r][c] = 0; // 인접 행렬의 모든 요소를 0으로 초기화.
        }
    }
}
void insert_vertex(GraphType*g, int v){
    if((g->n+1)>MAX_VERTICES){ // 정점의 갯수가 최대 정점의 수를 초과하는 경우
        fprintf(stderr, "그래프: 정점의 갯수 초과"); // 오류 메시지 출력.
        return; // 함수 종료.
    }
    g->n++; // 정점의 갯수를 1 증가.
}

void insert_edge(GraphType*g, int start, int end){
    if(start>=g->n || end>=g->n){ // 정점의 갯수를 초과하는 경우
        fprintf(stderr, "그래프: 정점의 갯수 초과"); // 오류 메시지 출력.
        return; // 함수 종료.
    }
    g->adj_mat[start][end] = 1; // 인접 행렬의 해당 요소를 1로 설정.
    g->adj_mat[end][start] = 1; // 무방향 그래프이므로 대칭.
}

void print_adj_mat(GraphType*g){ // 인접 행렬 출력. 
    for(int i = 0; i<g->n; i++){ // 행을 반복하면서
        printf("정점 %d의 인접 정점: ", i);
        for(int j = 0; j<g->n; j++){ // 열을 반복하면서
            printf("%02d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

int main(){
    GraphType *g; // 그래프 포인터 선언.
    g = (GraphType*)malloc(sizeof(GraphType)); // 그래프 메모리 할당.
    init(g); // 그래프 초기화.
    for(int i = 0; i<4; i++) // 4개의 정점을 추가.
        insert_vertex(g, i); // 정점 추가.
    insert_edge(g, 0, 1); // 0과 1을 연결.
    insert_edge(g, 0, 2); // 0과 2를 연결.
    insert_edge(g, 0, 3); // 0과 3을 연결.
    insert_edge(g, 1, 2); // 1과 2를 연결.
    insert_edge(g, 2, 3); // 2와 3을 연결.
    print_adj_mat(g); // 인접 행렬 출력.
    free(g); // 그래프 메모리 해제.
    return 0; // 프로그램 종료. 
}