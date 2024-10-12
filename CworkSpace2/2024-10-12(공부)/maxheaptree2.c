#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} MaxHeap;

// 히프 초기화
void initHeap(MaxHeap* heap) {
    heap->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        heap->data[i] = 0;  // 배열을 0으로 초기화
    }
}

// 히프 상태 출력
void printHeapState(MaxHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// 히프에 값 추가
void insert(MaxHeap* heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }
    int i = heap->size++;
    printf("삽입 전 상태: ");
    printHeapState(heap);
    while (i > 0 && heap->data[(i - 1) / 2] < value) {
        heap->data[i] = heap->data[(i - 1) / 2];
        i = (i - 1) / 2;
        printf("노드 이동 중: ");
        printHeapState(heap);
    }
    heap->data[i] = value;
    printf("삽입 후 상태: ");
    printHeapState(heap);
    printf("노드가 이동된 횟수: %d\n", i);
}

// 히프에서 루트 삭제
void deleteRoot(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty!\n");
        return;
    }
    int lastValue = heap->data[--heap->size];
    int i = 0, child;
    printf("삭제 전 상태: ");
    printHeapState(heap);
    while (i * 2 + 1 < heap->size) {
        child = i * 2 + 1;
        if (child + 1 < heap->size && heap->data[child] < heap->data[child + 1]) {
            child++;
        }
        if (lastValue >= heap->data[child]) break;
        heap->data[i] = heap->data[child];
        i = child;
        printf("노드 이동 중: ");
        printHeapState(heap);
    }
    heap->data[i] = lastValue;
    printf("삭제 후 상태: ");
    printHeapState(heap);
    printf("노드가 이동된 횟수: %d\n", i);
}

// 히프 레벨별 출력
void printHeap(MaxHeap* heap) {
    int level = 0, count = 1;
    for (int i = 0; i < heap->size; i++) {
        if (i == count) {
            printf("\n");
            level++;
            count += 1 << level;
        }
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// 사용자 인터페이스 실행
void runUserInterface(MaxHeap* heap) {
    char command;
    int value;
    while (1) {
        printf("---------------------\n");
        printf("| i : 노드 추가     |\n");
        printf("| d : 노드 삭제     |\n");
        printf("| p : 레벨 출력     |\n");
        printf("| c : 프로그램 종료 |\n");
        printf("---------------------\n");
        printf("메뉴 입력: ");
        scanf(" %c", &command);
        switch (command) {
            case 'i':
                printf("추가할 값 입력: ");
                scanf("%d", &value);
                insert(heap, value);
                break;
            case 'd':
                deleteRoot(heap);
                break;
            case 'p':
                printHeap(heap);
                break;
            case 'c':
                return;
            default:
                printf("잘못된 입력입니다.\n");
        }
    }
}

int main() {
    MaxHeap heap;
    initHeap(&heap);
    runUserInterface(&heap);
    return 0;
}