#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 100
//고객 정보
typedef struct
{
    int id; 
    int arrival_time; 
    int service_time; 
} element;
// 원형 큐
/*=================================================================================*/
typedef struct
{
    element data[MAX_QUEUE_SIZE]; //element 타입으로 배열선언
    int front,rear; 
} QueueType;
//에러 출력
void error(char *message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}
//front, rear 초기화
void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}
//비어있는지 확인
int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}
//가득차있는 확인
int is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//삽입 큐
void enqueue(QueueType *q,element item)
{
    if (is_full(q))
    {
        error("포화상태입니다.\n");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}
//삭제 큐
element dequeue(QueueType *q)
{
    if (is_empty(q))
    {
        error("공백상태입니다.\n");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front]; 
}
/*=================================================================================*/
int main(void)
{
    int minutes = 60; //60분을 담기 위한 변수
    int total_wait = 0; //총 대기시간을 담기 위한 변수
    int total_customers = 0; //고객번호를 담기 위한 변수
    int a_service_time = 0, 
        b_service_time = 0; //a창구, b창구 손님 서비스 시간을 담기 위한 변수
    int a_service_customer, //a창구 손님 고객번호를 담기 위한 변수
        b_service_customer; //b창구 손님 고객번호를 담기 위한 변수
    bool aCounter = true; //a창구 서비스 여부
    bool bCounter = true; //b창구 서비스 여부
    QueueType q;
    init_queue(&q); 
    srand(time(NULL)); //rand()를 초기화해주는 역할
    for (int clock = 0; clock < minutes; clock++)
    {
        
        printf("\n====================================현재시각=%d분======================================\n",clock);
        printf("<현재> A창고 출입여부 %d, B창고 출입여부 %d (0: 닫힘, 1: 열림)\n",aCounter,bCounter);
        if ((rand() % 10) < 3)
        {
            element customer;
            customer.id = total_customers++; //고객을 숫자로 지칭함. ex) 고객 1, 고객 2
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;  //업무시간을 랜덤으로  조정
            enqueue(&q,customer);
            printf("고객 %d이 %d분에 들어옵니다. 고객 업무처리시간=%d\n",customer.id,customer.arrival_time,customer.service_time);
        }
 
        if (a_service_time > 0) //a창구 고객의 서비스 시간이 0보다 클 경우
        {
            printf("고객 %d이 A창구에서 업무처리중입니다.\n",a_service_customer);
            a_service_time--;
            
            if (a_service_time == 0)
            {
                printf("(A창구가 %d분부터 열립니다.)\n",clock+1);
                aCounter = true;
            }
        }
        else if(aCounter) //a창구 서비스가 열려있을 경우
        {
            if (!is_empty(&q))
            {
                element customer = dequeue(&q); 
                a_service_customer = customer.id;
                a_service_time = customer.service_time; 
                
                printf("고객 %d이 %d분에 A창구에서 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",customer.id,clock,clock - customer.arrival_time);  
                aCounter = false;                                                                                
                total_wait += clock - customer.arrival_time;
            }
        }
 
        if (b_service_time > 0) //b창구 고객의 서비스 시간이 0보다 클 경우
        {
            printf("고객 %d이 B창구에서 업무처리중입니다.\n",b_service_customer);
            b_service_time--;
            
            if (b_service_time == 0)
            {
                printf("(B창구가 %d분부터 열립니다.)\n",clock + 1);
                bCounter = true;
            }
        }
        else if (bCounter) //b창구 서비스가 열려있을 경우
        {
            if (!is_empty(&q))
            {
                element customer = dequeue(&q); 
                b_service_customer = customer.id;
                b_service_time = customer.service_time;  
                printf("고객 %d이 %d분에 B창구에서 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",customer.id,clock,clock - customer.arrival_time);  
                bCounter = false;                                                                                                                
                total_wait += clock - customer.arrival_time;
            }
        }
        
    }
    printf("전체 대기 시간 = %d분 \n",total_wait);
    return 0;
}