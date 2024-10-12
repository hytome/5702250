#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 히프트리: 완전 이진 트리의 일종으로 각 노드의 값이 특정한 규칙을 따르게 하는 자료구조이다.
// 종류는 2가지.
// 최대 히프: 부모 노드의 값이 자식노드의 값보다 큰 경우. - 따라서 루트 노드는 가장 큰 값이 위치한다!
// 최소 히프: 부모 노드의 값이 자식노드의 값보다 작은 경우. - 따라서 루트 노드는 가장 작은 값이 위치한다!

typedef struct {
    // 히프의 구조를 위한 배열과 크기를 위한 구조체.
    // 히프트리는 기존의 left, right 노드가 아닌 배열로 구현되었을 때 강점이 유지된다.
    int* data;
    int size;
} TreeNode;

// 히프 초기화를 위한 함수.
void initHeap(TreeNode* root) {
    root->size = 0;  // 히프의 크기를 0으로 설정합니다.
    root->data = (int*)malloc(MAX_SIZE * sizeof(int));  
    // 메모리 누수를 방지하기 위한 동적 메모리 할당.
    if (root->data == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        root->data[i] = 0;  // 배열을 0으로 초기화하여 깨끗한 상태로 만듭니다.
    }
}

// 히프 상태 출력
void printHeapState(TreeNode* root) {
    for (int i = 0; i < root->size; i++) {
        printf("%d ", root->data[i]);  // 현재 히프의 모든 노드를 출력합니다.
    }
    printf("\n");
}

// 히프에 값 추가 기능을 위한 함수.
// 부모 노드 인덱스: (i - 1) / 2
// 왼쪽 자식 노드 인덱스: 2 * i + 1
// 오른쪽 자식 노드 인덱스: 2 * i + 2
void insert(TreeNode* root, int value, int showState) {
    if (root->size >= MAX_SIZE) {
        // 히프가 가득 찬 경우.
        printf("히프가 가득 찼습니다.\n");  // 히프가 가득 찼을 때 경고 메시지를 출력합니다.
        return;
    }
    int i = root->size++;  // 새로운 노드를 추가할 위치를 설정하고 히프 크기를 증가시킵니다.
    int moveCount = 0;  // 노드 이동 횟수를 추적합니다.
    if (showState) {
        printf("삽입 전 상태: ");
        printHeapState(root);  // 삽입 전 히프 상태를 출력합니다.
    }
    // 부모 노드와 비교하여 최대 히프 조건을 만족할 때까지 위로 이동합니다.
    while (i > 0 && root->data[(i - 1) / 2] < value) {
        root->data[i] = root->data[(i - 1) / 2];  // 부모 노드를 아래로 이동합니다.
        i = (i - 1) / 2;  // 부모 노드의 인덱스로 이동합니다.
        moveCount++;
        root->data[i] = value;  // 이동 중에도 value를 설정합니다.
        if (showState) {
            printf("노드 이동 중: ");
            printHeapState(root);  // 노드 이동 과정을 출력합니다.
        }
    }
    root->data[i] = value;  // 최종 위치에 값을 설정합니다.
    if (showState) {
        printf("삽입 후 상태: ");
        printHeapState(root);  // 삽입 후 히프 상태를 출력합니다.
        printf("노드가 이동된 횟수: %d\n", moveCount);  // 이동 횟수를 출력합니다.
    }
}

// 히프에서 루트 삭제
void deleteRoot(TreeNode* root) {
    if (root->size <= 0) {
        printf("히프가 텅 비었습니다.\n");  // 히프가 비어 있을 때 경고 메시지를 출력합니다.
        return;
    }
    int lastValue = root->data[--root->size];  // 마지막 노드를 가져오고 히프 크기를 줄입니다.
    int i = 0, child;
    int moveCount = 0;  // 노드 이동 횟수를 추적합니다.
    printf("삭제 전 상태: ");
    printHeapState(root);  // 삭제 전 히프 상태를 출력합니다.
    // 자식 노드와 비교하여 최대 히프 조건을 만족할 때까지 아래로 이동합니다.
    // 즉 가장 큰 값을 찾아서 아래로 이동하는 과정입니다.
    while (i * 2 + 1 < root->size) {
        child = i * 2 + 1;  // 왼쪽 자식 노드의 인덱스를 설정합니다.
        if (child + 1 < root->size && root->data[child] < root->data[child + 1]) {
            child++;  // 오른쪽 자식 노드가 더 크면 오른쪽 자식으로 이동합니다.
        }
        if (lastValue >= root->data[child]) break;  // 최대 히프 조건을 만족하면 종료합니다.
        root->data[i] = root->data[child];  // 자식 노드를 위로 이동합니다.
        i = child;  // 자식 노드의 인덱스로 이동합니다.
        moveCount++;
        printf("노드 이동 중: ");
        printHeapState(root);  // 노드 이동 과정을 출력합니다.
    }
    root->data[i] = lastValue;  // 최종 위치에 마지막 노드를 설정합니다.
    printf("삭제 후 상태: ");
    printHeapState(root);  // 삭제 후 히프 상태를 출력합니다.
    printf("노드가 이동된 횟수: %d\n", moveCount);  // 이동 횟수를 출력합니다.
}

// 히프 레벨별 출력 기능을 위한 함수.
// 즉 레벨 순회를 위한 함수.
void printHeap(TreeNode* root) {
    int level = 0, count = 1;
    // 레벨과 카운트를 선언하고 초기화 합니다.
    for (int i = 0; i < root->size; i++) {
        // 히프의 크기만큼 반복합니다.
        if (i == count) {
            printf("\n");  // 새로운 레벨로 이동할 때 줄바꿈을 합니다.
            level++;
            count += 1 << level;  // 다음 레벨의 노드 수를 계산합니다.
        }
        printf("%d ", root->data[i]);  // 현재 노드를 출력합니다.
    }
    printf("\n");
}

// 최대 히프 트리를 생성하는 함수.
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    //히프트리를 위한 노드를 동적으로 할당하고 초기화 합니다.
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    initHeap(root);
    //히프를 초기화 하여 크기를 0으로 설정하고 메모리를 할당합니다. 
    //이렇게 하면 메모리 누수를 방지할 수 있습니다.
    //입력된 데이터를 히프에 삽입합니다.
    for (int i = 0; i < size; i++) {
        insert(root, inputData[i], 0);
        //각 데이터를 히프에 삽입하여 최대 히프 조건을 만족하도록 합니다.
    }
    return root; //생성된 최대 히프 트리를 반환합니다.
}

// 각 기능을 담당하여 보여주는 함수 기능.
// 즉 사용자 인터페이스를 위한 함수기능.
void runUserInterface(TreeNode* root) {
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
                insert(root, value, 1);  // 히프에 값을 삽입합니다.
                break;
            case 'd':
                deleteRoot(root);  // 히프의 루트 노드를 삭제합니다.
                break;
            case 'p':
                printHeap(root);  // 히프를 레벨별로 출력합니다.
                break;
            case 'c':
                return;  // 프로그램을 종료합니다.
            default:
                printf("잘못된 입력입니다.\n");  // 잘못된 명령어에 대한 경고 메시지를 출력합니다.
        }
    }
}

int main() {
    int inputData[] = {90, 89, 70, 36, 75, 63, 13, 21, 18, 5};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 트리 생성, *root에 트리를 생성해 반환
    TreeNode* root = generateMaxHeapTree(inputData, size);

    runUserInterface(root);

    free(root->data);
    free(root);
    return 0;
}