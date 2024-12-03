#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SEARCH_COUNT 500

// ========================= AVL Tree =========================
// AVL 트리 노드 구조체 정의
typedef struct AVLNode {
    int key;  // 노드의 키 값
    struct AVLNode *left, *right;  // 왼쪽 및 오른쪽 자식 노드
    int height;  // 노드의 높이
} AVLNode;

// 새로운 AVL 노드 생성 함수
AVLNode* createAVLNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));  // 메모리 할당
    node->key = key;  // 키 값 설정
    node->left = node->right = NULL;  // 자식 노드 초기화
    node->height = 1;  // 초기 높이 설정
    return node;
}

// 노드의 높이 반환 함수
int getHeight(AVLNode* node) {
    return (node == NULL) ? 0 : node->height;  // 노드가 NULL이면 0, 아니면 높이 반환
}

// 오른쪽 회전 함수
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;  // 회전 축 노드
    AVLNode* T2 = x->right;  // 임시 저장 노드
    x->right = y;  // 회전 수행
    y->left = T2;  // 회전 후 자식 노드 재설정
    // 높이 갱신
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    return x;  // 새로운 루트 반환
}

// 왼쪽 회전 함수
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;  // 회전 축 노드
    AVLNode* T2 = y->left;  // 임시 저장 노드
    y->left = x;  // 회전 수행
    x->right = T2;  // 회전 후 자식 노드 재설정
    // 높이 갱신
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    return y;  // 새로운 루트 반환
}

// 노드의 균형 인수 반환 함수
int getBalance(AVLNode* node) {
    return (node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right);  // 왼쪽과 오른쪽 서브트리의 높이 차이
}

// AVL 트리에 노드 삽입 함수
AVLNode* insertAVL(AVLNode* node, int key, int* inserted) {
    if (node == NULL) {
        *inserted = 1;  // 삽입 성공 표시
        return createAVLNode(key);  // 새로운 노드 생성
    }

    if (key < node->key)
        node->left = insertAVL(node->left, key, inserted);  // 왼쪽 서브트리에 삽입
    else if (key > node->key)
        node->right = insertAVL(node->right, key, inserted);  // 오른쪽 서브트리에 삽입
    else {
        *inserted = 0;  // 중복 키로 삽입 실패
        return node;
    }

    // 노드 높이 갱신
    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    int balance = getBalance(node);  // 균형 인수 계산. 즉 노드의 균형이 맞는지.

    // LL 회전
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR 회전
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR 회전
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL 회전
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;  // 균형 잡힌 노드 반환
}

// 중위 순회 함수
void inOrderAVL(AVLNode* node, int* array, int* index) {
    if (node == NULL) return;
    inOrderAVL(node->left, array, index);  // 왼쪽 서브트리 순회
    array[(*index)++] = node->key;  // 현재 노드 키 저장
    inOrderAVL(node->right, array, index);  // 오른쪽 서브트리 순회
}

// AVL 트리에서 이진 탐색 함수
int binarySearchAVL(AVLNode* node, int key, int* compareCount) {
    while (node != NULL) {
        (*compareCount)++;  // 비교 횟수 증가
        if (key == node->key)
            return 1;  // 키 발견
        else if (key < node->key)
            node = node->left;  // 왼쪽 서브트리 탐색
        else
            node = node->right;  // 오른쪽 서브트리 탐색
    }
    return 0;  // 키 미발견
}

// AVL 트리 메모리 해제 함수
void freeAVL(AVLNode* node) {
    if (node == NULL) return;
    freeAVL(node->left);  // 왼쪽 서브트리 해제
    freeAVL(node->right);  // 오른쪽 서브트리 해제
    free(node);  // 현재 노드 해제
}

// ========================= 2-3 Tree =========================
// 2-3 트리 노드 구조체 정의
typedef struct TwoThreeNode {
    int keys[2];  // 노드의 키 배열
    struct TwoThreeNode *children[3];  // 자식 노드 배열
    int numKeys;  // 현재 키 개수
} TwoThreeNode;

// 새로운 2-3 노드 생성 함수
TwoThreeNode* createTwoThreeNode(int key) {
    TwoThreeNode* node = (TwoThreeNode*)malloc(sizeof(TwoThreeNode));  // 메모리 할당
    node->keys[0] = key;  // 첫 번째 키 설정
    node->numKeys = 1;  // 키 개수 초기화
    node->children[0] = node->children[1] = node->children[2] = NULL;  // 자식 노드 초기화
    return node;
}

// 2-3 트리에 노드 삽입 함수
void insertTwoThree(TwoThreeNode **root, int key) {
    if (*root == NULL) {
        *root = createTwoThreeNode(key);  // 루트가 없으면 새로운 노드 생성
        return;
    }

    TwoThreeNode *node = *root;

    if (node->children[0] == NULL) {  // 리프 노드인 경우
        if (node->numKeys == 1) {  // 키가 하나인 경우
            if (key < node->keys[0]) {
                node->keys[1] = node->keys[0];
                node->keys[0] = key;
            } else {
                node->keys[1] = key;
            }
            node->numKeys++;
        } else if (node->numKeys == 2) {  // 키가 두 개인 경우
            int tempKeys[3] = {node->keys[0], node->keys[1], key};
            //3개의 키 정렬  중간 키를 새로운 루트 노드로 설정하기 위해서 2-3 트리는 3개의 키를 정렬후 중간 값을 올리는 과정이니까. 
            if (tempKeys[0] > tempKeys[1]) { int tmp = tempKeys[0]; tempKeys[0] = tempKeys[1]; tempKeys[1] = tmp; }
            if (tempKeys[1] > tempKeys[2]) { int tmp = tempKeys[1]; tempKeys[1] = tempKeys[2]; tempKeys[2] = tmp; }
            if (tempKeys[0] > tempKeys[1]) { int tmp = tempKeys[0]; tempKeys[0] = tempKeys[1]; tempKeys[1] = tmp; }

            //중간값을 루트로 설정하고 나머지 두 값을 자식으로 설정. 
            *root = createTwoThreeNode(tempKeys[1]);
            (*root)->children[0] = createTwoThreeNode(tempKeys[0]);
            (*root)->children[1] = createTwoThreeNode(tempKeys[2]);
        }
        return;
    }
    //이제 늘 우리가 아는 루트노드보다 작은지 큰지 검사하고 삽입하는거 
    if (key < node->keys[0]) {
        insertTwoThree(&node->children[0], key);  // 왼쪽 자식에 삽입
    } else if (node->numKeys == 1 || key < node->keys[1]) {
        //현재 노드가 하나의 키만 가지고 있거나 두번째 키보다 작은경우. 
        insertTwoThree(&node->children[1], key);  // 중간 자식에 삽입
    } else {
        insertTwoThree(&node->children[2], key);  // 오른쪽 자식에 삽입
    }
}

// 중위 순회 함수
void inOrderTwoThree(TwoThreeNode* node, int* array, int* index) {
    if (node == NULL) return;
    if (node->numKeys == 1) {
        inOrderTwoThree(node->children[0], array, index);
        array[(*index)++] = node->keys[0];
        inOrderTwoThree(node->children[1], array, index);
    } else if (node->numKeys == 2) {
        inOrderTwoThree(node->children[0], array, index);
        array[(*index)++] = node->keys[0];
        inOrderTwoThree(node->children[1], array, index);
        array[(*index)++] = node->keys[1];
        inOrderTwoThree(node->children[2], array, index);
    }
}

// 2-3 트리에서 이진 탐색 함수
int binarySearchTwoThree(TwoThreeNode* node, int key, int* compareCount) {
    if (node == NULL) return 0;

    (*compareCount)++;
    if (key == node->keys[0] || (node->numKeys == 2 && key == node->keys[1]))
        return 1;

    if (key < node->keys[0]) {
        return binarySearchTwoThree(node->children[0], key, compareCount);
    } else if (node->numKeys == 1 || key < node->keys[1]) {
        return binarySearchTwoThree(node->children[1], key, compareCount);
    } else {
        return binarySearchTwoThree(node->children[2], key, compareCount);
    }
}

// 2-3 트리 메모리 해제 함수
void freeTwoThree(TwoThreeNode* node) {
    if (node == NULL) return;
    for (int i = 0; i <= node->numKeys; i++) {
        freeTwoThree(node->children[i]);
    }
    free(node);
}

// ========================= Utility Functions =========================
// 난수 배열 생성 함수
void generateRandomArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000;  // 0부터 9999까지의 난수 생성
    }
}

// 배열의 처음과 마지막 20개 요소 출력 함수
void printFirstAndLast20(int* array, int count) {
    printf("First 20 elements:\n");
    for (int i = 0; i < 20 && i < count; i++) {
        printf("%d ", array[i]);
    }
    printf("\nLast 20 elements:\n");
    for (int i = count - 20 < 0 ? 0 : count - 20; i < count; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// AVL 트리의 평균 비교 횟수 계산 함수
float calculateAverageComparisonAVL(AVLNode* root, int* array, int size, int searchCount) {
    int totalComparisons = 0;
    for (int i = 0; i < searchCount; i++) {
        int target = array[rand() % size]; //무작위 타겟 설정. 
        int compareCount = 0;
        binarySearchAVL(root, target, &compareCount); //타겟을 찾는데 걸리는 비교 횟수 계산. 
        totalComparisons += compareCount;
    }
    return (float)totalComparisons / searchCount;
}

// 2-3 트리의 평균 비교 횟수 계산 함수
float calculateAverageComparisonTwoThree(TwoThreeNode* root, int* array, int size, int searchCount) {
    int totalComparisons = 0;
    for (int i = 0; i < searchCount; i++) {
        int target = array[rand() % size]; //무작위 타겟 설정. 
        int compareCount = 0;
        binarySearchTwoThree(root, target, &compareCount); //타겟을 찾는데 걸리는 비교 횟수 계산. 
        totalComparisons += compareCount;
    }
    return (float)totalComparisons / searchCount;
}

// ========================= Main =========================
int main() {
    srand(time(NULL));  // 난수 생성기 시드 설정

    int array[SIZE];
    generateRandomArray(array, SIZE);  // 난수 배열 생성

    // AVL 트리 작업
    AVLNode* avlRoot = NULL;
    int insertCountAVL = 0;

    for (int i = 0; i < SIZE; i++) {
        int inserted = 0;
        avlRoot = insertAVL(avlRoot, array[i], &inserted);  // AVL 트리에 삽입
        if (inserted) insertCountAVL++;
    }

    int* sortedArrayAVL = malloc(insertCountAVL * sizeof(int));  // 정렬된 배열 메모리 할당
    int indexAVL = 0;
    inOrderAVL(avlRoot, sortedArrayAVL, &indexAVL);  // 중위 순회로 정렬된 배열 생성

    float avgComparisonAVL = calculateAverageComparisonAVL(avlRoot, array, SIZE, SEARCH_COUNT);  // 평균 비교 횟수 계산

    // 2-3 트리 작업
    TwoThreeNode* twoThreeRoot = NULL;
    int insertCountTwoThree = 0;

    for (int i = 0; i < SIZE; i++) {
        int compareCount = 0;
        if (!binarySearchTwoThree(twoThreeRoot, array[i], &compareCount)) {
            insertTwoThree(&twoThreeRoot, array[i]);  // 2-3 트리에 삽입
            insertCountTwoThree++;
        }
    }

    int* sortedArrayTwoThree = malloc(insertCountTwoThree * sizeof(int));  // 정렬된 배열 메모리 할당
    int indexTwoThree = 0;
    inOrderTwoThree(twoThreeRoot, sortedArrayTwoThree, &indexTwoThree);  // 중위 순회로 정렬된 배열 생성

    float avgComparisonTwoThree = calculateAverageComparisonTwoThree(twoThreeRoot, array, SIZE, SEARCH_COUNT);  // 평균 비교 횟수 계산

    // 출력
    printf("=== AVL Tree Results ===\n");
    printFirstAndLast20(sortedArrayAVL, insertCountAVL);  // AVL 트리 결과 출력
    printf("Average Comparison Count: %.2f\n", avgComparisonAVL);

    printf("\n=== 2-3 Tree Results ===\n");
    printFirstAndLast20(sortedArrayTwoThree, insertCountTwoThree);  // 2-3 트리 결과 출력
    printf("Average Comparison Count: %.2f\n", avgComparisonTwoThree);

    // 메모리 해제
    free(sortedArrayAVL);
    freeAVL(avlRoot);
    free(sortedArrayTwoThree);
    freeTwoThree(twoThreeRoot);

    return 0;
}
