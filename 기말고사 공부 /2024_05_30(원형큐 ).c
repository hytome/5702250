#include<stdio.h>
#include<stdlib.h>
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct{
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

void error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//초기화 함수
void init_queue(QueueType *q){
    q->front = q->rear = 0;
}

