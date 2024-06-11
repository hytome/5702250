#include<stdio.h>
#include<stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct{
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
}QueueType;

//오류 함수.
void error(char* message){
    fprintf(stderr,"%s\n",message);
    exit(1);
}

//큐 초기화 함수.
void init_queue(QueueType *q){
    q->front = -1;
    q->rear = -1;
}

//큐 출력 함수.
void queue_print(QueueType *q){
    for(int i=0; i<MAX_QUEUE_SIZE; i++){
        //큐의 크기 만큼 반복하여 큐의 각 위치를 검사합니다.
        if(i<=q->front || i>q->rear )
        //조건문:현재 인덱스가 큐의 처음 위치보다 작거나, 
          //현재 인덱스가 큐의 마지막 위치보다 크면 null을 출력합니다.
            printf(" null ");
        else
            printf("%d ",q->data[i]);
            //그렇지 않은경우 즉 인덱스가 front 와 rear 사이에 
            //있는 경우 해당 인덱스의 값을 출력합니다.
    }
    printf("\n");
}

//큐가 가득차있는지 확인하는 함수.
int is_full(QueueType *q){
    if(q->rear == MAX_QUEUE_SIZE-1)
        return 1;
    else
        return 0;
}

//큐가 비어있는지 확인하는 함수.
int is_empty(QueueType *q){
    if(q->front == q->rear)
        return 1;
    else
        return 0;
}

//큐에 원소를 삽입하는 함수.
void enqueue(QueueType *q, element item){
    if(is_full(q))
        error("큐가 포화 상태입니다..");
    q->data[++q->rear] = item;
}

//큐에서 원소를 삭제하는 함수.
element dequeue(QueueType *q){
    if(is_empty(q)){
        error("큐가 공백 상태입니다..");
        return -1;
    }
    int item = q->data[++q->front];
    return item;
}

int main(){
    int item = 0;
    QueueType q;
    init_queue(&q);
    enqueue(&q,10);
    queue_print(&q);
    enqueue(&q,20);
    queue_print(&q);
    enqueue(&q,30);
    queue_print(&q);
    
    item = dequeue(&q);
    printf("dequeue item : %d\n",item);
    item = dequeue(&q);
    printf("dequeue item : %d\n",item);
    item = dequeue(&q);
    printf("dequeue item : %d\n",item);
    return 0;
}
