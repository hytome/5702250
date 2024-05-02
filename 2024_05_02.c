#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 100

typedef struct {
    int id;
    int arrival_time;
    int service_time;
} Customer;

typedef struct {
    Customer data[QUEUE_SIZE];
    int front;
    int rear;
    int count;
} Queue;

void initializeQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

int isFull(Queue *q) {
    return q->count == QUEUE_SIZE;
}

int isEmpty(Queue *q) {
    return q->count == 0;
}

void enqueue(Queue *q, Customer customer) {
    if (!isFull(q)) {
        q->data[q->rear] = customer;
        q->rear = (q->rear + 1) % QUEUE_SIZE;
        q->count++;
    }
}

Customer dequeue(Queue *q) {
    Customer customer = {0, 0, 0};
    if (!isEmpty(q)) {
        customer = q->data[q->front];
        q->front = (q->front + 1) % QUEUE_SIZE;
        q->count--;
    }
    return customer;
}

int is_customer_arrived(float arrival_prob) {
    return ((float)rand() / (float)RAND_MAX) < arrival_prob;
}

int main() {
    srand(time(NULL));
    Queue queue;
    initializeQueue(&queue);
    int clock = 0;
    int current_service_time = 0;
    int total_wait_time = 0;
    int total_customers = 0;
    Customer current_customer = {0, 0, 0};

    while (clock < 10000) { // 시뮬레이션 시간 조정 가능
        clock++;
        
        if (is_customer_arrived(0.1)) { // 도착 확률 조정 가능
            if (!isFull(&queue)) {
                Customer new_customer = {total_customers++, clock, rand() % 10 + 1};
                enqueue(&queue, new_customer);
                printf("시각 %d: 고객 %d 도착, 서비스시간 %d\n", clock, new_customer.id, new_customer.service_time);
            }
        }

        if (current_service_time > 0) {
            current_service_time--;
            if (current_service_time == 0) {
                printf("시각 %d: 고객 %d 서비스 완료\n", clock, current_customer.id);
            }
        } else {
            if (!isEmpty(&queue)) {
                current_customer = dequeue(&queue);
                current_service_time = current_customer.service_time;
                total_wait_time += clock - current_customer.arrival_time;
                printf("시각 %d: 고객 %d 서비스 시작\n", clock, current_customer.id);
            }
        }
    }

    printf("평균 대기 시간: %.2f\n", (float)total_wait_time / total_customers);

    return 0;
}