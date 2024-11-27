#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20    // 정렬할 난수의 개수
#define DIGITS 10 // 최대 자릿수 (0~9)

// 노드 구조체 정의 (큐에서 사용)
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 큐 구조체 정의
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// 큐 초기화
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// 큐가 비어 있는지 확인
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// 큐에 데이터 삽입
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// 큐에서 데이터 제거
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다!\n");
        exit(1);
    }
    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}

// 기수 정렬 함수 (큐를 이용)
void radixSort(int arr[], int n) {
    Queue queues[DIGITS]; // 0~9 버킷(큐) 생성
    for (int i = 0; i < DIGITS; i++) {
        initQueue(&queues[i]);
    }

    // 배열의 최대값 찾기 (자릿수 계산)
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }

    int maxDigits = 0;
    while (max > 0) {
        maxDigits++;
        max /= 10;
    }

    // 각 자릿수별로 정렬 수행
    int exp = 1; // 자릿수 (1의 자리부터 시작)
    for (int d = 0; d < maxDigits; d++) {
        // 배열의 각 값을 해당 자릿수 큐에 삽입
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            enqueue(&queues[digit], arr[i]);
        }

        // 큐에서 데이터를 꺼내 배열에 재배치
        int index = 0;
        for (int i = 0; i < DIGITS; i++) {
            while (!isEmpty(&queues[i])) {
                arr[index++] = dequeue(&queues[i]);
            }
        }
        exp *= 10; // 다음 자릿수로 이동
    }
}

int main() {
    int arr[MAX];
    srand(time(NULL));

    // 난수 생성 (0 ~ 999)
    for (int i = 0; i < MAX; i++) {
        arr[i] = rand() % 1000; // 최대 세 자릿수
    }

    // 정렬 전 배열 출력
    printf("정렬 전 배열: ");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 기수 정렬 수행
    radixSort(arr, MAX);

    // 정렬 후 배열 출력
    printf("정렬 후 배열: ");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
