#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>   

#define MAX_QUEUE_SIZE 100

typedef struct {
    int *data;
    int front, rear;
} CircularQueue;

// 원형 큐 초기화
void initQueue(CircularQueue *q) {
    q->data = (int *)malloc(MAX_QUEUE_SIZE * sizeof(int));
    q->front = 0;
    q->rear = 0;
}

// 원형 큐가 비어있는지 확인
bool isEmpty(CircularQueue *q) {
    return q->front == q->rear;
}

// 원형 큐가 가득 찼는지 확인
bool isFull(CircularQueue *q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE) == q->front;
}

// 원형 큐에 요소 추가
void enqueue(CircularQueue *q, int element) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = element;
}

// 원형 큐에서 요소 제거
int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 원형 큐 해제
void freeQueue(CircularQueue *q) {
    free(q->data);
}


int main() {
    CircularQueue q;
    initQueue(&q);
    int currentTime = 0, arrivalTime = 0, serviceTime = 0;
    int totalWaitTime = 0, customerCount = 0;

    srand(time(NULL)); // 난수 초기화

    for (int i = 0; i < 100; i++) { // 100명의 고객을 시뮬레이션
        arrivalTime += rand() % 5 + 1; // 1~5분 사이에 고객 도착
        serviceTime = rand() % 10 + 1; // 1~10분의 서비스 시간

        while (currentTime < arrivalTime && !isEmpty(&q)) {
            currentTime += dequeue(&q);
            totalWaitTime += currentTime - arrivalTime;
        }

        if (!isFull(&q)) {
            enqueue(&q, serviceTime);
        }
    }

    printf("평균 대기 시간: %.2f분\n", (float)totalWaitTime / customerCount);

    freeQueue(&q);
    return 0;
}