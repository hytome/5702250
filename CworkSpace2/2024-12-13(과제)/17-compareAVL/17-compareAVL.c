#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 전역 변수: 탐색 시 비교 횟수와 탐색 연산 횟수를 추적
long long compareCount = 0; // 전체 비교 횟수를 저장하는 변수
long long searchCount = 0;  // 전체 탐색 연산 횟수를 저장하는 변수

// 노드 구조체 정의 (AVL 트리용 height 포함)
typedef struct Node {
    int key;            // 노드의 키 값
    struct Node *left;  // 왼쪽 자식 노드 포인터
    struct Node *right; // 오른쪽 자식 노드 포인터
    int height;         // AVL 트리에서 노드의 높이 (균형을 맞추기 위해 필요)
} Node;

// 유틸리티 함수: 두 정수 중 최대값을 반환
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 노드의 높이를 반환하는 함수
int getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// 균형 인수를 계산하는 함수
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 오른쪽 회전 함수
Node* rightRotate(Node* y) {
    Node* x = y->left;    // y의 왼쪽 자식을 x로 설정
    Node* T2 = x->right;  // x의 오른쪽 서브트리를 T2로 저장

    // 회전 수행
    x->right = y;
    y->left = T2;

    // 높이 업데이트
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // 새로운 루트 반환
    return x;
}

// 왼쪽 회전 함수
Node* leftRotate(Node* x) {
    Node* y = x->right;    // x의 오른쪽 자식을 y로 설정
    Node* T2 = y->left;    // y의 왼쪽 서브트리를 T2로 저장

    // 회전 수행
    y->left = x;
    x->right = T2;

    // 높이 업데이트
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // 새로운 루트 반환
    return y;
}

// AVL 트리 삽입 함수
Node* insertAVL(Node* node, int key) {
    // 일반적인 BST 삽입 수행
    if (node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node)); // 새 노드 메모리 할당
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1; // 새 노드는 처음에 리프 노드로 추가됨
        return newNode;
    }

    // 키 값을 기준으로 왼쪽 또는 오른쪽 서브트리에 삽입
    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else // 중복 키는 허용하지 않음
        return node;

    // 현재 노드의 높이 업데이트
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 균형 인수 계산
    int balance = getBalance(node);

    // 균형이 깨진 경우, 네 가지 경우에 따라 회전 수행

    // LL Case: 왼쪽 서브트리의 왼쪽 서브트리에 삽입된 경우
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case: 오른쪽 서브트리의 오른쪽 서브트리에 삽입된 경우
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case: 왼쪽 서브트리의 오른쪽 서브트리에 삽입된 경우
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left); // 먼저 왼쪽 회전
        return rightRotate(node);            // 그 다음 오른쪽 회전
    }

    // RL Case: 오른쪽 서브트리의 왼쪽 서브트리에 삽입된 경우
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right); // 먼저 오른쪽 회전
        return leftRotate(node);                 // 그 다음 왼쪽 회전
    }

    // 균형이 유지된 경우 현재 노드 반환
    return node;
}

// 최소값 노드 찾기 함수
Node* minValueNode(Node* node) {
    Node* current = node;

    // 가장 왼쪽 노드를 찾아 최소값 노드 찾기
    while (current->left != NULL)
        current = current->left;

    return current;
}

// AVL 트리 삭제 함수
Node* deleteAVLNode(Node* root, int key) {
    // 일반적인 BST 삭제 수행
    if (root == NULL)
        return root;

    // 삭제할 키가 현재 노드의 키보다 작으면 왼쪽 서브트리에서 삭제
    if (key < root->key)
        root->left = deleteAVLNode(root->left, key);
    // 삭제할 키가 현재 노드의 키보다 크면 오른쪽 서브트리에서 삭제
    else if (key > root->key)
        root->right = deleteAVLNode(root->right, key);
    // 현재 노드가 삭제할 키를 가지고 있는 경우
    else {
        // 한 개 이하의 자식을 가진 노드인 경우
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            // 자식이 없는 경우
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // 자식이 한 개 있는 경우
                *root = *temp; // 자식의 내용을 현재 노드로 복사

            free(temp); // 삭제된 노드의 메모리 해제
        }
        else {
            // 두 개의 자식을 가진 노드인 경우: 오른쪽 서브트리의 최소값 노드를 찾음
            Node* temp = minValueNode(root->right);

            // 오른쪽 서브트리의 최소값 노드의 키 값을 현재 노드로 복사
            root->key = temp->key;

            // 오른쪽 서브트리에서 최소값 노드를 삭제
            root->right = deleteAVLNode(root->right, temp->key);
        }
    }

    // 삭제 후 트리가 비어있다면 반환
    if (root == NULL)
        return root;

    // 현재 노드의 높이 업데이트
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 균형 인수 계산
    int balance = getBalance(root);

    // 균형이 깨진 경우, 네 가지 경우에 따라 회전 수행

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left); // 먼저 왼쪽 회전
        return rightRotate(root);            // 그 다음 오른쪽 회전
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right); // 먼저 오른쪽 회전
        return leftRotate(root);                 // 그 다음 왼쪽 회전
    }

    // 균형이 유지된 경우 현재 노드 반환
    return root;
}

// AVL 트리에서 노드 찾기 함수
Node* searchAVL(Node* root, int key) {
    Node* current = root;
    int localCompare = 0; // 현재 검색에서의 비교 횟수

    // 트리를 순회하며 키를 검색
    while (current != NULL) {
        localCompare++; // 비교 횟수 증가
        if (key == current->key) {
            compareCount += localCompare; // 전체 비교 횟수에 추가
            searchCount++;                // 탐색 연산 횟수 증가
            return current;               // 노드 발견
        }
        else if (key < current->key)
            current = current->left; // 왼쪽 서브트리로 이동
        else
            current = current->right; // 오른쪽 서브트리로 이동
    }
    compareCount += localCompare; // 키를 찾지 못한 경우에도 비교 횟수 추가
    searchCount++;                // 탐색 연산 횟수 증가
    return NULL;                  // 키를 찾지 못함
}

// BST 삽입 함수
Node* insertBST(Node* node, int key) {
    if (node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node)); // 새 노드 메모리 할당
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 0; // BST에서는 height가 필요 없지만 구조체를 재사용
        return newNode;
    }

    // 키 값을 기준으로 왼쪽 또는 오른쪽 서브트리에 삽입
    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);

    // 균형 조정이 필요 없으므로 현재 노드 반환
    return node;
}

// BST 삭제 함수
Node* deleteBSTNode(Node* root, int key) {
    if (root == NULL)
        return root;

    // 삭제할 키가 현재 노드의 키보다 작으면 왼쪽 서브트리에서 삭제
    if (key < root->key)
        root->left = deleteBSTNode(root->left, key);
    // 삭제할 키가 현재 노드의 키보다 크면 오른쪽 서브트리에서 삭제
    else if (key > root->key)
        root->right = deleteBSTNode(root->right, key);
    // 현재 노드가 삭제할 키를 가지고 있는 경우
    else {
        // 자식이 없는 경우
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) { // 한 개의 자식만 있는 경우
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // 두 개의 자식을 가진 노드인 경우: 오른쪽 서브트리의 최소값 노드를 찾음
        Node* temp = minValueNode(root->right);

        // 오른쪽 서브트리의 최소값 노드의 키 값을 현재 노드로 복사
        root->key = temp->key;

        // 오른쪽 서브트리에서 최소값 노드를 삭제
        root->right = deleteBSTNode(root->right, temp->key);
    }
    return root;
}

// BST 탐색 함수
Node* searchBST(Node* root, int key) {
    Node* current = root;
    int localCompare = 0; // 현재 검색에서의 비교 횟수

    // 트리를 순회하며 키를 검색
    while (current != NULL) {
        localCompare++; // 비교 횟수 증가
        if (key == current->key) {
            compareCount += localCompare; // 전체 비교 횟수에 추가
            searchCount++;                // 탐색 연산 횟수 증가
            return current;               // 노드 발견
        }
        else if (key < current->key)
            current = current->left; // 왼쪽 서브트리로 이동
        else
            current = current->right; // 오른쪽 서브트리로 이동
    }
    compareCount += localCompare; // 키를 찾지 못한 경우에도 비교 횟수 추가
    searchCount++;                // 탐색 연산 횟수 증가
    return NULL;                  // 키를 찾지 못함
}

// 트리 해제 함수
void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);  // 왼쪽 서브트리 해제
    freeTree(root->right); // 오른쪽 서브트리 해제
    free(root);            // 현재 노드 메모리 해제
}

// AVL 트리에 대한 배치 작업 수행 함수
void doAVLBatch(Node* root) {
    static Node* currentRoot = NULL; // 현재 AVL 트리의 루트
    searchCount = 0;  // 각 배치 작업 시작 시 탐색 횟수 초기화
    compareCount = 0; // 각 배치 작업 시작 시 비교 횟수 초기화

    // 먼저 트리를 일정량 채워놓는 이유:
    // 트리를 미리 일정 크기로 만들어 두면 실제 작업 수행 시 트리의 균형 상태를 어느 정도 유지할 수 있고,
    // 검색, 삽입, 삭제 연산이 보다 현실적인 조건에서 수행되도록 하기 위함입니다.
    for (int i = 0; i < 500; i++) {
        currentRoot = insertAVL(currentRoot, rand() % 1000); // 무작위 키 삽입
    }

    // 이후 실제 작업 수행: 2000번의 랜덤 연산 (삽입, 삭제, 검색)
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;    // 연산 종류를 랜덤으로 선택 (0: 삽입, 1: 삭제, 2: 검색)
        int B = rand() % 1000; // 키 값을 0 ~ 999 사이에서 랜덤으로 선택

        if (A == 0) {
            currentRoot = insertAVL(currentRoot, B); // AVL 트리에 키 삽입
        }
        else if (A == 1) {
            currentRoot = deleteAVLNode(currentRoot, B); // AVL 트리에서 키 삭제
        }
        else if (A == 2) {
            searchAVL(currentRoot, B); // AVL 트리에서 키 검색
        }
    }
}

// Binary Search Tree (BST)에 대한 배치 작업 수행 함수
void doBinaryBatch(Node* root) {
    static Node* currentRoot = NULL; // 현재 BST 트리의 루트
    searchCount = 0;  // 각 배치 작업 시작 시 탐색 횟수 초기화
    compareCount = 0; // 각 배치 작업 시작 시 비교 횟수 초기화

    // 먼저 트리를 일정량 채워놓는 이유:
    // 트리를 미리 일정 크기로 만들어 두면 실제 작업 수행 시 트리의 균형 상태를 일정하지 않게 만들 수 있어,
    // BST의 최악의 경우(편향된 트리)와 평균적인 경우를 비교할 수 있습니다.
    for (int i = 0; i < 500; i++) {
        currentRoot = insertBST(currentRoot, rand() % 1000); // 무작위 키 삽입
    }

    // 이후 실제 작업 수행: 2000번의 랜덤 연산 (삽입, 삭제, 검색)
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;    // 연산 종류를 랜덤으로 선택 (0: 삽입, 1: 삭제, 2: 검색)
        int B = rand() % 1000; // 키 값을 0 ~ 999 사이에서 랜덤으로 선택

        if (A == 0) {
            currentRoot = insertBST(currentRoot, B); // BST 트리에 키 삽입
        }
        else if (A == 1) {
            currentRoot = deleteBSTNode(currentRoot, B); // BST 트리에서 키 삭제
        }
        else if (A == 2) {
            searchBST(currentRoot, B); // BST 트리에서 키 검색
        }
    }
}

int main(int argc, char *argv[]) {
    Node *root = NULL; // 트리의 루트 초기화
    srand(time(NULL)); // 랜덤 시드 초기화
    float allCount = 0.0;

    // AVL 트리에 대한 배치 작업 수행
    doAVLBatch(root);
    // 평균 비교 횟수 계산: 전체 비교 횟수를 탐색 횟수로 나눔
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);
    // AVL 트리를 해제 (메모리 누수 방지)
    freeTree(root);
    root = NULL; // 루트 포인터 초기화
    compareCount = allCount = 0; // 비교 횟수 및 평균 초기화

    // Binary Search Tree (BST)에 대한 배치 작업 수행
    doBinaryBatch(root);
    // 평균 비교 횟수 계산
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);
    // BST 트리를 해제
    freeTree(root);

    return 0; // 프로그램 종료
}
