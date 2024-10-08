#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TreeNode 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
    int lthread, rthread; // 스레드 플래그: 1이면 스레드, 0이면 자식 노드
} TreeNode;

// 함수 프로토타입 선언
TreeNode* CreateNode(int data);
TreeNode* InsertNode(TreeNode* root, int data);
void ConvertToThreaded(TreeNode* root, TreeNode** prev);
void InOrderTraversalThreaded(TreeNode* root);
void InOrderTraversal(TreeNode* root);
void PrintTree(TreeNode* root, int space);

// 새로운 노드를 생성하고 스레드 플래그를 초기화
TreeNode* CreateNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = newNode->rthread = 0; // 초기화
    return newNode;
}

// 일반 이진 트리에 새로운 노드를 삽입
TreeNode* InsertNode(TreeNode* root, int data) {
    if (root == NULL) {
        return CreateNode(data);
    }
    if (data < root->data) {
        root->left = InsertNode(root->left, data);
    } else if (data > root->data) {
        root->right = InsertNode(root->right, data);
    }
    return root;
}

// 일반 이진 트리를 쓰레드 이진 트리로 변환
void ConvertToThreaded(TreeNode* root, TreeNode** prev) {
    if (root == NULL) return;

    // 왼쪽 서브트리 변환
    ConvertToThreaded(root->left, prev);

    // 현재 노드의 왼쪽이 NULL이면 선행자를 설정
    if (root->left == NULL) {
        root->left = *prev;
        root->lthread = 1;
    }

    // 이전 노드의 오른쪽이 NULL이면 후속자를 설정
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->rthread = 1;
    }

    // 이전 노드를 현재 노드로 갱신
    *prev = root;

    // 오른쪽 서브트리 변환
    ConvertToThreaded(root->right, prev);
}

// 쓰레드 이진 트리를 중위 순회하여 출력
void InOrderTraversalThreaded(TreeNode* root) {
    if (root == NULL) return;

    // 가장 왼쪽 노드로 이동
    TreeNode* ptr = root;
    while (ptr->lthread == 0) {
        ptr = ptr->left;
    }

    // 중위 순회
    while (ptr != NULL) {
        printf("%d ", ptr->data);

        // 후속자가 스레드인 경우
        if (ptr->rthread == 1) {
            ptr = ptr->right;
        } else {
            // 오른쪽 서브트리의 가장 왼쪽 노드로 이동
            ptr = ptr->right;
            while (ptr != NULL && ptr->lthread == 0) {
                ptr = ptr->left;
            }
        }
    }
}

// 일반 이진 트리를 중위 순회하여 출력
void InOrderTraversal(TreeNode* root) {
    if (root == NULL) return;
    InOrderTraversal(root->left);
    printf("%d ", root->data);
    InOrderTraversal(root->right);
}

// 트리의 구조를 시각적으로 출력
void PrintTree(TreeNode* root, int space) {
    if (root == NULL) return;

    space += 10;
    PrintTree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) printf(" ");
    printf("%d\n", root->data);
    PrintTree(root->left, space);
}

int main() {
    TreeNode *root = NULL;
    int choice;
    char input[256];

    while (1) {
        printf("\n1. 삽입\n2. 일반 중위 순회 출력\n3. 쓰레드 이진 트리로 변환 후 중위 순회 출력\n4. 트리 출력\n5. 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);
        getchar(); // 버퍼에 남은 개행 문자 제거

        switch (choice) {
            case 1:
                printf("삽입할 값을 입력하세요 (공백으로 구분): ");
                fgets(input, sizeof(input), stdin);
                char* token = strtok(input, " ");
                while (token != NULL) {
                    int value = atoi(token);
                    root = InsertNode(root, value);
                    token = strtok(NULL, " ");
                }
                break;
            case 2:
                printf("일반 중위 순회: ");
                InOrderTraversal(root);
                printf("\n");
                break;
            case 3: {
                TreeNode* prev = NULL;
                ConvertToThreaded(root, &prev);
                printf("쓰레드 이진 트리 중위 순회: ");
                InOrderTraversalThreaded(root);
                printf("\n");
                break;
            }
            case 4:
                printf("현재 트리 구조:\n");
                PrintTree(root, 0);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("잘못된 선택입니다\n");
        }
    }

    return 0;
}