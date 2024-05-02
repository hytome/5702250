#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 5


typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;

typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

//오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//큐 초기화 함수
void init_queue(QueueType *q)
{
    q->rear = 0;
    q->front = 0;
}



// 큐 포화 확인 함수
int is_full(QueueType *q){
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 큐 공백 확인 함수
int is_empty(QueueType *q)
{
    return (q->rear == q->front);
}

// 큐 삽입 함수
void enqueue(QueueType *q, element item)
{
    if(is_full(q)){
        error("큐가 포화상태입니다.");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 큐 삭제 함수
element dequeue(QueueType *q)
{
    if(is_empty(q)){
        error("큐가 공백상태입니다.");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek(QueueType *q){
    if(is_empty(q))
        error("큐가 공백상태입니다.");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
//큐 상태 출력 함수
void queue_print(QueueType *q){
    
    if(!is_empty(q)){
        int i = q->front;
        do{
            i = (i+1) % MAX_QUEUE_SIZE;
            
            if(i == q->rear)
                break;
        } while (i != q->front);
        printf("\n");
    }
}
int main(void){
    int minutes = 60;
    int total_wait = 0;
    int total_customer = 0;
    int service_time = 0;
    int service_customer = 0;
    QueueType queue;
    init_queue(&queue);

    srand(time(NULL));
    for(int clock = 0; clock < minutes; clock++) {
        printf("현재시각 = %d\n", clock);
        if(rand() % 10 < 3) {
            //늘리고 싶으면 10<3 을 계속 수정.
            element customer;
            customer.id = total_customer++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;
            enqueue(&queue, customer);
            printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n", customer.id, customer.arrival_time, customer.service_time);
        }
        if(service_time > 0) {
            printf("고객 %d 업무처리중입니다. \n", service_customer);
            service_time--;
        }
        else {
            if(!is_empty(&queue)) {
                element customer = dequeue(&queue);
                service_customer = customer.id;
                service_time = customer.service_time - 1;
                total_wait += clock - customer.arrival_time;
                printf("고객 %d 업무 시작합니다. 대기시간 = %d분\n", customer.id, clock - customer.arrival_time);
            }
        }
        queue_print(&queue);
    }
    printf("총 고객 수 = %d명, 총 대기 시간 = %d분\n", total_customer, total_wait);
    if (total_customer > 0) {
        double average_wait = (double)total_wait / total_customer;
        printf("고객들의 평균 대기시간 = %.2f분\n", average_wait);
    }
    return 0;
}