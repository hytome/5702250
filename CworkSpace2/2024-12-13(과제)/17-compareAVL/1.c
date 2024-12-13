#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 전역 변수: 탐색 시 비교 횟수와 탐색 연산 횟수를 추적
long long compareCount = 0; // 전체 비교 횟수를 저장하는 변수
long long searchCount = 0;  // 전체 탐색 연산 횟수를 저장하는 변수

// 전역 변수로 트리의 루트를 선언
typedef struct Node {
    int key;            // 노드의 키 값
    struct Node *left;  // 왼쪽 자식 노드 포인터
    struct Node *right; // 오른쪽 자식 노드 포인터
    int height;         // AVL 트리에서 노드의 높이 (균형을 맞추기 위해 필요)
} Node;

Node *root = NULL;

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
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// 왼쪽 회전 함수
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// AVL 트리 삽입 함수
Node* insertAVL(Node* node, int key) {
    if (node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if(newNode == NULL){
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node; // 중복 키는 무시

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// 최소값 노드 찾기 함수
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// AVL 트리 삭제 함수
Node* deleteAVLNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteAVLNode(root->left, key);
    else if (key > root->key)
        root->right = deleteAVLNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVLNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// AVL 트리에서 노드 찾기 함수
Node* searchAVL(Node* root, int key) {
    Node* current = root;
    int localCompare = 0;

    while (current != NULL) {
        localCompare++;
        if (key == current->key) {
            compareCount += localCompare;
            searchCount++;
            return current;
        }
        else if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    compareCount += localCompare;
    searchCount++;
    return NULL;
}

// BST 삽입 함수
Node* insertBST(Node* node, int key) {
    if (node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if(newNode == NULL){
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 0; // height is not used in BST
        return newNode;
    }

    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);
    else
        return node; // 중복 키는 무시

    return node;
}

// BST 삭제 함수
Node* deleteBSTNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteBSTNode(root->left, key);
    else if (key > root->key)
        root->right = deleteBSTNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteBSTNode(root->right, temp->key);
    }
    return root;
}

// BST 탐색 함수
Node* searchBST(Node* root, int key) {
    Node* current = root;
    int localCompare = 0;

    while (current != NULL) {
        localCompare++;
        if (key == current->key) {
            compareCount += localCompare;
            searchCount++;
            return current;
        }
        else if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    compareCount += localCompare;
    searchCount++;
    return NULL;
}

// 트리 해제 함수
void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// AVL 트리에 대한 배치 작업 수행 함수
void doAVLBatch() {
    searchCount = 0;  // 각 배치 작업 시작 시 초기화
    compareCount = 0;

    // 먼저 트리를 어느 정도 채워놓기
    for (int i = 0; i < 500; i++) {
        root = insertAVL(root, rand() % 1000);
    }

    // 이후 실제 작업 수행
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;

        if (A == 0) {
            root = insertAVL(root, B);
        }
        else if (A == 1) {
            root = deleteAVLNode(root, B);
        }
        else if (A == 2) {
            searchAVL(root, B);
        }
    }
}

// BST에 대한 배치 작업 수행 함수
void doBinaryBatch() {
    searchCount = 0;  // 각 배치 작업 시작 시 초기화
    compareCount = 0;

    // 먼저 트리를 어느 정도 채워놓기
    for (int i = 0; i < 500; i++) {
        root = insertBST(root, rand() % 1000);
    }

    // 이후 실제 작업 수행
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;

        if (A == 0) {
            root = insertBST(root, B);
        }
        else if (A == 1) {
            root = deleteBSTNode(root, B);
        }
        else if (A == 2) {
            searchBST(root, B);
        }
    }
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    float allCount = 0.0;

    // AVL 트리에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch();
    if (searchCount > 0) {
        allCount = (float)compareCount / searchCount;
        printf("average AVL compare count: %.2f\n", allCount);
    } else {
        printf("No search operations performed for AVL tree.\n");
    }

    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;

    // Binary Search Tree Batch를 수행한다.
    doBinaryBatch();
    if (searchCount > 0) {
        allCount = (float)compareCount / searchCount;
        printf("average Bin compare count: %.2f\n", allCount);
    } else {
        printf("No search operations performed for Binary Search Tree.\n");
    }

    freeTree(root);
    return 0;
}
