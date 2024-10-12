#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 히프트리: 완전 이진 트리의 일종으로 각 노드의 값이 특정한 규칙을 따르게 하는 자료구조이다.
// 종류는 2가지.
// 최대 히프: 부모 노드의 값이 자식노드의 값보다 큰 경우. - 따라서 루트 노드는 가장 큰 값이 위치한다!
// 최소 히프: 부모 노드의 값이 자식노드의 값보다 작은 경우. - 따라서 루트 노드는 가장 작은 값이 위치한다!

typedef struct {
    // 히프의 구조를 위한 배열과 크기를 위한 구조체.
    int* data;
    int size;
} MaxHeap;

// 히프 초기화를 위한 함수.
void initHeap(MaxHeap* heap) {
    heap->size = 0;  // 히프의 크기를 0으로 설정합니다.
    heap->data = (int*)malloc(MAX_SIZE * sizeof(int));  
    //메모리 누수를 방지하기 위한 동적 메모리 할당.
    if (heap->data == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        heap->data[i] = 0;  // 배열을 0으로 초기화하여 깨끗한 상태로 만듭니다.
    }
}

// 히프 상태 출력
void printHeapState(MaxHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);  // 현재 히프의 모든 노드를 출력합니다.
    }
    printf("\n");
}

// 히프에 값 추가 기능을 위한 함수.
// 부모 노드 인덱스: (i - 1) / 2
// 왼쪽 자식 노드 인덱스: 2 * i + 1
// 오른쪽 자식 노드 인덱스: 2 * i + 2
void insert(MaxHeap* heap, int value, int showState) {
    if (heap->size >= MAX_SIZE) {
        // 히프가 가득 찬 경우.
        printf("히프가 가득 찼습니다.\n");  // 히프가 가득 찼을 때 경고 메시지를 출력합니다.
        return;
    }
    int i = heap->size++;  // 새로운 노드를 추가할 위치를 설정하고 히프 크기를 증가시킵니다.
    int moveCount = 0;  // 노드 이동 횟수를 추적합니다.
    if (showState) {
        printf("삽입 전 상태: ");
        printHeapState(heap);  // 삽입 전 히프 상태를 출력합니다.
    }
    // 부모 노드와 비교하여 최대 히프 조건을 만족할 때까지 위로 이동합니다.
    while (i > 0 && heap->data[(i - 1) / 2] < value) {
        heap->data[i] = heap->data[(i - 1) / 2];  // 부모 노드를 아래로 이동합니다.
        i = (i - 1) / 2;  // 부모 노드의 인덱스로 이동합니다.
        moveCount++;
        heap->data[i] = value;  // 이동 중에도 value를 설정합니다.
        if (showState) {
            printf("노드 이동 중: ");
            printHeapState(heap);  // 노드 이동 과정을 출력합니다.
        }
    }
    heap->data[i] = value;  // 최종 위치에 값을 설정합니다.
    if (showState) {
        printf("삽입 후 상태: ");
        printHeapState(heap);  // 삽입 후 히프 상태를 출력합니다.
        printf("노드가 이동된 횟수: %d\n", moveCount);  // 이동 횟수를 출력합니다.
    }
}

// 히프에서 루트 삭제
void deleteRoot(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("히프가 텅 비었습니다.\n");  // 히프가 비어 있을 때 경고 메시지를 출력합니다.
        return;
    }
    int lastValue = heap->data[--heap->size];  // 마지막 노드를 가져오고 히프 크기를 줄입니다.
    int i = 0, child;
    int moveCount = 0;  // 노드 이동 횟수를 추적합니다.
    printf("삭제 전 상태: ");
    printHeapState(heap);  // 삭제 전 히프 상태를 출력합니다.
    // 자식 노드와 비교하여 최대 히프 조건을 만족할 때까지 아래로 이동합니다.
    // 즉 가장 큰 값을 찾아서 아래로 이동하는 과정입니다.
    while (i * 2 + 1 < heap->size) {
        child = i * 2 + 1;  // 왼쪽 자식 노드의 인덱스를 설정합니다.
        if (child + 1 < heap->size && heap->data[child] < heap->data[child + 1]) {
            child++;  // 오른쪽 자식 노드가 더 크면 오른쪽 자식으로 이동합니다.
        }
        if (lastValue >= heap->data[child]) break;  // 최대 히프 조건을 만족하면 종료합니다.
        heap->data[i] = heap->data[child];  // 자식 노드를 위로 이동합니다.
        i = child;  // 자식 노드의 인덱스로 이동합니다.
        moveCount++;
        printf("노드 이동 중: ");
        printHeapState(heap);  // 노드 이동 과정을 출력합니다.
    }
    heap->data[i] = lastValue;  // 최종 위치에 마지막 노드를 설정합니다.
    printf("삭제 후 상태: ");
    printHeapState(heap);  // 삭제 후 히프 상태를 출력합니다.
    printf("노드가 이동된 횟수: %d\n", moveCount);  // 이동 횟수를 출력합니다.
}

// 히프 레벨별 출력 기능을 위한 함수.
// 즉 레벨 순회를 위한 함수.
void printHeap(MaxHeap* heap) {
    int level = 0, count = 1;
    // 레벨과 카운트를 선언하고 초기화 합니다.
    for (int i = 0; i < heap->size; i++) {
        // 히프의 크기만큼 반복합니다.
        if (i == count) {
            printf("\n");  // 새로운 레벨로 이동할 때 줄바꿈을 합니다.
            level++;
            count += 1 << level;  // 다음 레벨의 노드 수를 계산합니다.
        }
        printf("%d ", heap->data[i]);  // 현재 노드를 출력합니다.
    }
    printf("\n");
}

// 각 기능을 담당하여 보여주는 함수 기능.
// 즉 사용자 인터페이스를 위한 함수기능.
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
        scanf(" %c", &command);  // 사용자로부터 명령어를 입력받습니다.
        switch (command) {
            case 'i':
                printf("추가할 값 입력: ");
                scanf("%d", &value);  // 추가할 값을 입력받습니다.
                insert(heap, value, 1);  // 히프에 값을 삽입합니다.
                break;
            case 'd':
                deleteRoot(heap);  // 히프의 루트 노드를 삭제합니다.
                break;
            case 'p':
                printHeap(heap);  // 히프를 레벨별로 출력합니다.
                break;
            case 'c':
                return;  // 프로그램을 종료합니다.
            default:
                printf("잘못된 입력입니다.\n");  // 잘못된 명령어에 대한 경고 메시지를 출력합니다.
        }
    }
}

int main() {
    MaxHeap heap;
    initHeap(&heap);

    // 과제에 적힌 초기 트리 삽입.
    int initialData[] = {90, 89, 70, 36, 75, 63, 13, 21, 18, 5};
    // 이미지에 적힌 초기 트리.
    int size = sizeof(initialData) / sizeof(initialData[0]);
    for (int i = 0; i < size; i++) {
        insert(&heap, initialData[i], 0);  // 프로그램을 실행할 때 초기 데이터까지 이동 구조를 보여주기 때문에 추가한 기능입니다.
        // 이렇게 showState를 0으로 설정하면 초기 데이터의 이동 과정을 보여주지 않습니다.
    }

    runUserInterface(&heap);

    free(heap.data);  // 동적 메모리 해제
    return 0;
}