#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;


void init_queue(QueueType *q) {
    q->front = q->rear = 0;
}


int is_empty(QueueType *q) {
    return (q->front == q->rear);
}


int is_full(QueueType *q) {
    
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}


void enqueue(QueueType *q, element item) {
    if (is_full(q)) {
        printf("큐가 포화 상태입니다.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}


element dequeue(QueueType *q) {
    if (is_empty(q)) {
        printf("큐가 공백 상태입니다.\n");
        return -1;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}


void print_queue(QueueType *q) {
    if (is_empty(q)) {
        printf("큐에 원소가 없습니다.\n");
        return;
    }
    int i = q->front;
    printf("큐 내용: ");
    do {
        i = (i + 1) % MAX_QUEUE_SIZE;
        printf("%d ", q->queue[i]);
        if (i == q->rear)
            break;
    } while (i != q->front);
    printf("\n");
}

int main() {
    QueueType q;
    init_queue(&q);
    int choice;
    element item;

    while (1) {
        printf("1.큐에 원소를 삽입.\n");
        printf("2:큐에서 원소를 삭제.\n");
        printf("3.큐에서 원소를 출력\n");
        printf("4.프로그램 종료.\n");
        printf("메뉴를 선택해 주세요.");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("삽입할 원소를 입력하세요: ");
                scanf("%d", &item);
                enqueue(&q, item);
                break;
            case 2:
                item = dequeue(&q);
                if (item != -1)
                    printf("삭제된 원소: %d\n", item);
                break;
            case 3:
                print_queue(&q);
                break;
            case 4:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 입력입니다. 다시 입력해주세요.\n");
        }
    }
    return 0;
}