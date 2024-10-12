#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
//배열이 아닌 이러한 방식이 옳을까?
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 새로운 노드를 생성하는 함수
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 트리 상태를 출력하는 함수
void printTree(TreeNode* root, int level) {
    if (root == NULL) return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("   ");
    printf("%d\n", root->value);
    printTree(root->left, level + 1);
}

// 최대 히프 트리에 값을 삽입하는 함수
void InsertMaxHeapTree(TreeNode** root, int value, int showState) {
    if (*root == NULL) {
        *root = createNode(value);
        return;
    }

    if (showState) {
        printf("삽입 전 상태:\n");
        printTree(*root, 0);
    }

    TreeNode* current = *root;
    TreeNode* parent = NULL;
    int moveCount = 0;

    while (current != NULL) {
        parent = current;
        if (value > current->value) {
            int temp = current->value;
            current->value = value;
            value = temp;
            moveCount++;
        }
        if (current->left == NULL) {
            current->left = createNode(value);
            break;
        } else if (current->right == NULL) {
            current->right = createNode(value);
            break;
        } else {
            current = current->left;
        }
    }

    if (showState) {
        printf("삽입 후 상태:\n");
        printTree(*root, 0);
        printf("노드가 이동된 횟수: %d\n", moveCount);
    }
}

// 가장 오른쪽 아래 노드를 찾는 함수
TreeNode* findLastNode(TreeNode* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL && root->right == NULL) return root;
    TreeNode* left = findLastNode(root->left);
    TreeNode* right = findLastNode(root->right);
    return right ? right : left;
}

// 최대 히프 트리에서 루트 노드를 삭제하는 함수
void deleteRoot(TreeNode** root) {
    if (*root == NULL) {
        printf("트리가 비어 있습니다.\n");
        return;
    }

    printf("삭제 전 상태:\n");
    printTree(*root, 0);

    TreeNode* lastNode = findLastNode(*root);
    if (lastNode == NULL) return;

    (*root)->value = lastNode->value;
    free(lastNode);
    lastNode = NULL;

    TreeNode* current = *root;
    int moveCount = 0;

    while (current) {
        TreeNode* largest = current;
        if (current->left && current->left->value > largest->value) {
            largest = current->left;
        }
        if (current->right && current->right->value > largest->value) {
            largest = current->right;
        }
        if (largest == current) break;
        int temp = current->value;
        current->value = largest->value;
        largest->value = temp;
        current = largest;
        moveCount++;
    }

    printf("삭제 후 상태:\n");
    printTree(*root, 0);
    printf("노드가 이동된 횟수: %d\n", moveCount);
}

// 트리를 레벨 순서로 출력하는 함수
void printLevelOrder(TreeNode* root) {
    if (root == NULL) return;

    printf("트리 레벨별 출력\n");
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 1;
    while (front < rear) {
        int nodeCount = rear - front;
        printf("[%d] ", level++);
        while (nodeCount > 0) {
            TreeNode* node = queue[front++];
            printf("%d ", node->value);
            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
            nodeCount--;
        }
        printf("\n");
    }
}

// 사용자 인터페이스를 실행하는 함수
void runUserInterface(TreeNode* root) {
    char command;
    int value;
    while (1) {
        printf("---------------------\n");
        printf("| i : 노드 추가     |\n");
        printf("| d : 노드 삭제     |\n");
        printf("| p : 레벨별 출력   |\n");
        printf("| c : 프로그램 종료 |\n");
        printf("---------------------\n");
        printf("메뉴 입력: ");
        scanf(" %c", &command);
        switch (command) {
            case 'i':
                printf("추가할 값 입력: ");
                scanf("%d", &value);
                InsertMaxHeapTree(&root, value, 1);
                break;
            case 'd':
                deleteRoot(&root);
                break;
            case 'p':
                printLevelOrder(root);
                break;
            case 'c':
                return;
            default:
                printf("잘못된 입력입니다.\n");
        }
    }
}

// 트리의 모든 노드를 해제하는 함수
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int inputData[] = {90, 89, 70, 36, 75, 63, 13, 21, 18, 5};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 트리 생성
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        InsertMaxHeapTree(&root, inputData[i], 0);  // 초기 데이터는 이동 과정을 출력하지 않음
    }

    runUserInterface(root);

    freeTree(root);  // 동적 메모리 해제
    return 0;
}