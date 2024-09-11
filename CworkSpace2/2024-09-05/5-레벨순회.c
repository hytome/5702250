#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

//레벨 순회:각 노드를 레벨 순으로 검사하는 순회방법.
//지금 까지의 순회 법이 스택을 이용하여 순화하는 방법이라면.
//레벨 순회는 큐를 이용하여 순회 하는 방법이다.

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;

}TreeNode;

#define MAX_QUEUE_SIZE 100
typedef TreeNode *element;

typedef struct{
    //큐타입.
    //큐는 선입선출 방식.
    element queue[MAX_QUEUE_SIZE];
    //element 타입의 배열. 
    //MAX_QUEUE_SIZE 만큼의 크기를 가진 배열.
    int front, rear;
    //front는 큐의 맨 앞을 가리키는 인덱스.
    //rear는 큐의 맨 뒤를 가리키는 인덱스.
}QueueType;

//오류 함수 
void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType *q){
    q->front = q->rear = 0; 
    //큐를 초기화 하는 함수.
    //front와 rear 을 0으로 초기화.
}
int is_empty(QueueType *q){
    return q->front == q->rear;
    //큐가 비어있는지 확인하는 함수.
}
//포화상태 검출 함수.
int is_full(QueueType *q){  
    return ((q->rear+1) % MAX_QUEUE_SIZE == q->front);
}


    