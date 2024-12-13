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

// AVL 트리 함수 선언
Node* insertAVL(Node* node, int key);       // AVL 트리에 키 삽입
Node* deleteAVLNode(Node* root, int key);   // AVL 트리에서 키 삭제
Node* searchAVL(Node* root, int key);       // AVL 트리에서 키 검색
int getHeight(Node* node);                   // 노드의 높이를 반환
int getBalance(Node* node);                  // 노드의 균형 인수를 계산
Node* rightRotate(Node* y);                  // 오른쪽 회전 함수
Node* leftRotate(Node* x);                   // 왼쪽 회전 함수

// BST 함수 선언
Node* insertBST(Node* node, int key);        // BST에 키 삽입
Node* deleteBSTNode(Node* root, int key);    // BST에서 키 삭제
Node* searchBST(Node* root, int key);        // BST에서 키 검색

// 트리 해제 함수
void freeTree(Node* root);                    // 트리의 모든 노드를 해제

// 배치 작업 함수
void doAVLBatch(Node** root);                 // AVL 트리에 대한 일괄 작업 수행
void doBinaryBatch(Node** root);              // BST에 대한 일괄 작업 수행

// 중위 순회 (디버깅용)
void inorderTraversal(Node* root);            // 트리를 중위 순회하며 출력

// 메인 함수
int main(int argc, char *argv[]) {
    Node *root = NULL;           // 트리의 루트 노드 초기화
    srand(time(NULL));           // 난수 생성 시드 초기화
    float allCount = 0.0;        // 평균 비교 횟수를 저장할 변수

    // AVL 트리에 대한 2000회 배치 작업 수행
    doAVLBatch(&root);
    // 평균 비교 횟수 계산: 전체 비교 횟수 / 전체 탐색 횟수
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);
    // 트리를 후위 순회하며 메모리 해제
    freeTree(root);
    root = NULL;
    // 비교 및 탐색 카운트 초기화
    compareCount = searchCount = 0;

    // BST에 대한 2000회 배치 작업 수행
    doBinaryBatch(&root);
    // 평균 비교 횟수 계산
    allCount = (float)compareCount / searchCount;
    printf("average Bin  compare count: %.2f\n", allCount);
    // 트리 메모리 해제
    freeTree(root);
    root = NULL;

    return 0; // 프로그램 종료
}

// ============================ AVL 트리 구현 ============================

// 노드의 높이를 반환하는 함수
int getHeight(Node* node) {
    if (node == NULL)
        return 0; // NULL 노드의 높이는 0
    return node->height; // 노드의 높이 반환
}

// 균형 인수를 계산하는 함수
int getBalance(Node* node) {
    if (node == NULL)
        return 0; // NULL 노드의 균형 인수는 0
    return getHeight(node->left) - getHeight(node->right); // 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
}

// 오른쪽 회전 함수
Node* rightRotate(Node* y) {
    Node* x = y->left;      // y의 왼쪽 자식을 x로 설정
    Node* T2 = x->right;    // x의 오른쪽 자식을 T2로 저장

    // 회전 수행
    x->right = y;            // x의 오른쪽 자식으로 y를 설정
    y->left = T2;            // y의 왼쪽 자식으로 T2를 설정

    // 회전 후 노드들의 높이 업데이트
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1; // y의 새로운 높이
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1; // x의 새로운 높이

    return x; // 새로운 루트인 x를 반환
}

// 왼쪽 회전 함수
Node* leftRotate(Node* x) {
    Node* y = x->right;     // x의 오른쪽 자식을 y로 설정
    Node* T2 = y->left;     // y의 왼쪽 자식을 T2로 저장

    // 회전 수행
    y->left = x;             // y의 왼쪽 자식으로 x를 설정
    x->right = T2;           // x의 오른쪽 자식으로 T2를 설정

    // 회전 후 노드들의 높이 업데이트
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1; // x의 새로운 높이
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1; // y의 새로운 높이

    return y; // 새로운 루트인 y를 반환
}

// AVL 트리 삽입 함수
Node* insertAVL(Node* node, int key) {
    // 일반적인 BST 삽입 로직
    if (node == NULL) {
        // 삽입할 위치를 찾음
        Node* newNode = (Node*)malloc(sizeof(Node)); // 새 노드 할당
        newNode->key = key;                          // 키 설정
        newNode->left = newNode->right = NULL;        // 자식 노드 초기화
        newNode->height = 1;                          // 새 노드의 높이는 1
        return newNode;                               // 새 노드를 반환
    }

    if (key < node->key)
        node->left = insertAVL(node->left, key); // 왼쪽 서브트리에 삽입
    else if (key > node->key)
        node->right = insertAVL(node->right, key); // 오른쪽 서브트리에 삽입
    else
        return node; // 중복 키는 무시하고 현재 노드를 반환

    // 현재 노드의 높이 업데이트
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 현재 노드의 균형 인수 계산
    int balance = getBalance(node);

    // 불균형이 발생한 경우 4가지 경우에 따라 회전 수행

    // LL Case: 왼쪽 서브트리의 왼쪽 서브트리에 삽입
    if (balance > 1 && key < node->left->key)
        return rightRotate(node); // 오른쪽 회전

    // RR Case: 오른쪽 서브트리의 오른쪽 서브트리에 삽입
    if (balance < -1 && key > node->right->key)
        return leftRotate(node); // 왼쪽 회전

    // LR Case: 왼쪽 서브트리의 오른쪽 서브트리에 삽입
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left); // 왼쪽 회전
        return rightRotate(node);            // 오른쪽 회전
    }

    // RL Case: 오른쪽 서브트리의 왼쪽 서브트리에 삽입
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right); // 오른쪽 회전
        return leftRotate(node);                  // 왼쪽 회전
    }

    // 균형이 맞춰진 경우 현재 노드를 반환
    return node;
}

// AVL 트리에서 노드 찾기 함수
Node* searchAVL(Node* root, int key) {
    Node* current = root; // 탐색 시작 노드

    while (current != NULL) {
        compareCount++; // 비교 횟수 증가
        if (key == current->key) {
            searchCount++; // 탐색 성공 시 탐색 횟수 증가
            return current; // 노드 찾음
        }
        else if (key < current->key)
            current = current->left; // 왼쪽 서브트리로 이동
        else
            current = current->right; // 오른쪽 서브트리로 이동
    }
    searchCount++; // 탐색 실패 시에도 탐색 횟수 증가
    return NULL; // 노드 찾지 못함
}

// 최소값 노드 찾기 함수 (AVL과 BST 공용)
Node* minValueNode(Node* node) {
    Node* current = node;
    // 가장 왼쪽에 있는 노드를 찾을 때까지 이동
    while (current->left != NULL)
        current = current->left;
    return current; // 최소값 노드 반환
}

// AVL 트리 삭제 함수
Node* deleteAVLNode(Node* root, int key) {
    // 일반적인 BST 삭제 로직
    if (root == NULL)
        return root; // 키가 존재하지 않으면 NULL 반환

    if (key < root->key)
        root->left = deleteAVLNode(root->left, key); // 왼쪽 서브트리에서 삭제
    else if (key > root->key)
        root->right = deleteAVLNode(root->right, key); // 오른쪽 서브트리에서 삭제
    else {
        // 삭제할 노드를 찾음
        // 노드가 자식이 하나이거나 없는 경우
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right; // 자식 노드 중 하나를 선택

            if (temp == NULL) {
                // 자식이 없는 경우
                temp = root;
                root = NULL; // 루트를 NULL로 설정
            }
            else {
                // 자식이 하나 있는 경우
                *root = *temp; // 자식 노드의 값을 현재 노드에 복사
            }

            free(temp); // 삭제할 노드 메모리 해제
        }
        else {
            // 노드가 두 개의 자식을 가진 경우
            // 중위 후속자(오른쪽 서브트리에서 가장 작은 노드) 찾기
            Node* temp = minValueNode(root->right);
            root->key = temp->key; // 중위 후속자의 키를 현재 노드에 복사
            root->right = deleteAVLNode(root->right, temp->key); // 중위 후속자를 삭제
        }
    }

    // 삭제 후 트리가 비어있다면 반환
    if (root == NULL)
        return root;

    // 현재 노드의 높이 업데이트
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 현재 노드의 균형 인수 계산
    int balance = getBalance(root);

    // 불균형이 발생한 경우 4가지 경우에 따라 회전 수행

    // LL Case: 왼쪽 서브트리의 균형이 깨짐
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root); // 오른쪽 회전

    // LR Case: 왼쪽 서브트리의 오른쪽 서브트리가 높음
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left); // 왼쪽 회전
        return rightRotate(root);            // 오른쪽 회전
    }

    // RR Case: 오른쪽 서브트리의 균형이 깨짐
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root); // 왼쪽 회전

    // RL Case: 오른쪽 서브트리의 왼쪽 서브트리가 높음
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right); // 오른쪽 회전
        return leftRotate(root);                  // 왼쪽 회전
    }

    return root; // 균형이 맞춰진 노드를 반환
}

// ============================ 이진 탐색 트리(BST) 구현 ============================

// BST 삽입 함수
Node* insertBST(Node* node, int key) {
    if (node == NULL) {
        // 삽입할 위치를 찾음
        Node* newNode = (Node*)malloc(sizeof(Node)); // 새 노드 할당
        newNode->key = key;                          // 키 설정
        newNode->left = newNode->right = NULL;        // 자식 노드 초기화
        newNode->height = 0;                           // height는 사용하지 않음
        return newNode;                               // 새 노드를 반환
    }

    if (key < node->key)
        node->left = insertBST(node->left, key); // 왼쪽 서브트리에 삽입
    else if (key > node->key)
        node->right = insertBST(node->right, key); // 오른쪽 서브트리에 삽입
    // 중복 키는 무시하고 현재 노드를 반환

    return node; // 균형을 맞출 필요가 없는 BST의 경우 현재 노드를 반환
}

// BST 탐색 함수
Node* searchBST(Node* root, int key) {
    Node* current = root; // 탐색 시작 노드

    while (current != NULL) {
        compareCount++; // 비교 횟수 증가
        if (key == current->key) {
            searchCount++; // 탐색 성공 시 탐색 횟수 증가
            return current; // 노드 찾음
        }
        else if (key < current->key)
            current = current->left; // 왼쪽 서브트리로 이동
        else
            current = current->right; // 오른쪽 서브트리로 이동
    }
    searchCount++; // 탐색 실패 시에도 탐색 횟수 증가
    return NULL; // 노드 찾지 못함
}

// BST 삭제 함수
Node* deleteBSTNode(Node* root, int key) {
    if (root == NULL)
        return root; // 키가 존재하지 않으면 NULL 반환

    if (key < root->key)
        root->left = deleteBSTNode(root->left, key); // 왼쪽 서브트리에서 삭제
    else if (key > root->key)
        root->right = deleteBSTNode(root->right, key); // 오른쪽 서브트리에서 삭제
    else {
        // 삭제할 노드를 찾음
        // 노드가 자식이 하나이거나 없는 경우
        if (root->left == NULL) {
            Node* temp = root->right; // 오른쪽 자식 노드 저장
            free(root);                // 현재 노드 메모리 해제
            return temp;               // 오른쪽 자식 반환
        }
        else if (root->right == NULL) {
            Node* temp = root->left; // 왼쪽 자식 노드 저장
            free(root);              // 현재 노드 메모리 해제
            return temp;             // 왼쪽 자식 반환
        }

        // 노드가 두 개의 자식을 가진 경우
        // 중위 후속자(오른쪽 서브트리에서 가장 작은 노드) 찾기
        Node* temp = minValueNode(root->right);
        root->key = temp->key; // 중위 후속자의 키를 현재 노드에 복사
        root->right = deleteBSTNode(root->right, temp->key); // 중위 후속자를 삭제
    }

    return root; // 삭제 후 루트를 반환
}

// ============================ 트리 해제 함수 ============================

// 트리의 모든 노드를 해제하는 함수 (후위 순회 방식)
void freeTree(Node* root) {
    if (root == NULL)
        return; // NULL 노드는 해제할 필요 없음
    freeTree(root->left);   // 왼쪽 서브트리 해제
    freeTree(root->right);  // 오른쪽 서브트리 해제
    free(root);             // 현재 노드 메모리 해제
}

// ============================ 배치 작업 함수 ============================

// AVL 트리에 대한 배치 작업 수행 함수
void doAVLBatch(Node** root) {
    for (int i = 0; i < 2000; i++) { // 2000번 반복
        int A = rand() % 3;    // 0~2 중 하나의 랜덤 값 선택
        int B = rand() % 1000; // 0~999 중 하나의 랜덤 값 선택

        if (A == 0) {
            // 삽입 작업
            *root = insertAVL(*root, B);
        }
        else if (A == 1) {
            // 삭제 작업
            *root = deleteAVLNode(*root, B);
        }
        else if (A == 2) {
            // 탐색 작업
            searchAVL(*root, B);
        }
    }
}

// BST에 대한 배치 작업 수행 함수
void doBinaryBatch(Node** root) {
    for (int i = 0; i < 2000; i++) { // 2000번 반복
        int A = rand() % 3;    // 0~2 중 하나의 랜덤 값 선택
        int B = rand() % 1000; // 0~999 중 하나의 랜덤 값 선택

        if (A == 0) {
            // 삽입 작업
            *root = insertBST(*root, B);
        }
        else if (A == 1) {
            // 삭제 작업
            *root = deleteBSTNode(*root, B);
        }
        else if (A == 2) {
            // 탐색 작업
            searchBST(*root, B);
        }
    }
}

// ============================ 중위 순회 (디버깅용) ============================

// 트리를 중위 순회하며 노드의 키 값을 출력하는 함수
void inorderTraversal(Node* root) {
    if (root == NULL)
        return; // NULL 노드는 탐색할 필요 없음
    inorderTraversal(root->left);          // 왼쪽 서브트리 순회
    printf("%d ", root->key);              // 현재 노드의 키 출력
    inorderTraversal(root->right);         // 오른쪽 서브트리 순회
}
