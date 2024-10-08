#include <stdio.h>
#include <stdlib.h>

// TreeNode 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
    int lthread, rthread; // 스레드 플래그: 1이면 스레드, 0이면 자식 노드
} TreeNode;

// 함수 프로토타입 선언
TreeNode* CreateNode(int data);
TreeNode* InsertNode(TreeNode* root, int data, int isThreaded);
TreeNode* DeleteNode(TreeNode* root, int data, int isThreaded);
TreeNode* InOrderSuccessor(TreeNode* ptr);
void InOrderTraversal(TreeNode* root, int isThreaded);
void PrintTree(TreeNode* root, int space);
TreeNode* SearchNode(TreeNode* root, int data, int isThreaded);

// 새로운 노드를 생성하고 스레드 플래그를 초기화
TreeNode* CreateNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = newNode->rthread = 1; // 스레드 초기화
    return newNode;
}

// 트리에 새로운 노드를 삽입
TreeNode* InsertNode(TreeNode* root, int data, int isThreaded) {
    if (!isThreaded) {
        // 일반 이진 트리 삽입
        if (root == NULL) {
            return CreateNode(data);
        }
        if (data < root->data) {
            root->left = InsertNode(root->left, data, isThreaded);
        } else if (data > root->data) {
            root->right = InsertNode(root->right, data, isThreaded);
        }
        return root;
    } else {
        // 쓰레드 이진 트리 삽입
        TreeNode *ptr = root;
        TreeNode *parent = NULL;

        while (ptr != NULL) {
            if (data == ptr->data) {
                return root; // 중복된 값은 삽입하지 않음
            }
            parent = ptr;
            if (data < ptr->data) {
                if (ptr->lthread == 0) {
                    ptr = ptr->left;
                } else {
                    break;
                }
            } else {
                if (ptr->rthread == 0) {
                    ptr = ptr->right;
                } else {
                    break;
                }
            }
        }

        TreeNode *newNode = CreateNode(data);
        if (parent == NULL) {
            root = newNode;
        } else if (data < parent->data) {
            newNode->left = parent->left;
            newNode->right = parent;
            parent->lthread = 0;
            parent->left = newNode;
        } else {
            newNode->right = parent->right;
            newNode->left = parent;
            parent->rthread = 0;
            parent->right = newNode;
        }

        return root;
    }
}

// 중위 순회에서의 후속자 찾기
TreeNode* InOrderSuccessor(TreeNode* ptr) {
    if (ptr->rthread == 1) {
        return ptr->right;
    }
    ptr = ptr->right;
    while (ptr->lthread == 0) {
        ptr = ptr->left;
    }
    return ptr;
}

// 트리에서 노드를 삭제
TreeNode* DeleteNode(TreeNode* root, int data, int isThreaded) {
    if (!isThreaded) {
        // 일반 이진 트리 삭제
        if (root == NULL) return root;

        if (data < root->data) {
            root->left = DeleteNode(root->left, data, isThreaded);
        } else if (data > root->data) {
            root->right = DeleteNode(root->right, data, isThreaded);
        } else {
            if (root->left == NULL) {
                TreeNode *temp = root->right;
                free(root);
                return temp;
            } else if (root->right == NULL) {
                TreeNode *temp = root->left;
                free(root);
                return temp;
            }

            TreeNode *temp = InOrderSuccessor(root);
            root->data = temp->data;
            root->right = DeleteNode(root->right, temp->data, isThreaded);
        }
        return root;
    } else {
        // 쓰레드 이진 트리 삭제
        TreeNode *parent = NULL, *ptr = root;

        while (ptr != NULL) {
            if (data == ptr->data) {
                break;
            }
            parent = ptr;
            if (data < ptr->data) {
                if (ptr->lthread == 0) {
                    ptr = ptr->left;
                } else {
                    ptr = NULL;
                }
            } else {
                if (ptr->rthread == 0) {
                    ptr = ptr->right;
                } else {
                    ptr = NULL;
                }
            }
        }

        if (ptr == NULL) {
            printf("노드를 찾을 수 없습니다\n");
            return root;
        }

        if (ptr->lthread == 0 && ptr->rthread == 0) {
            TreeNode *succ = InOrderSuccessor(ptr);
            int val = succ->data;
            root = DeleteNode(root, succ->data, isThreaded);
            ptr->data = val;
            return root;
        }

        TreeNode *child;
        if (ptr->lthread == 1 && ptr->rthread == 1) {
            child = NULL;
        } else if (ptr->lthread == 0) {
            child = ptr->left;
        } else {
            child = ptr->right;
        }

        if (parent == NULL) {
            free(ptr);
            return child;
        }

        if (ptr == parent->left) {
            parent->left = child;
            parent->lthread = ptr->lthread;
        } else {
            parent->right = child;
            parent->rthread = ptr->rthread;
        }

        TreeNode *pred = ptr->left;
        if (ptr->lthread == 0) {
            while (pred->rthread == 0) {
                pred = pred->right;
            }
            pred->right = ptr->right;
        }

        TreeNode *succ = ptr->right;
        if (ptr->rthread == 0) {
            while (succ->lthread == 0) {
                succ = succ->left;
            }
            succ->left = ptr->left;
        }

        free(ptr);
        return root;
    }
}

// 중위 순회: 스레드를 활용하여 순회
void InOrderTraversal(TreeNode* root, int isThreaded) {
    if (!isThreaded) {
        // 일반 이진 트리 중위 순회
        if (root == NULL) return;
        InOrderTraversal(root->left, isThreaded);
        printf("%d ", root->data);
        InOrderTraversal(root->right, isThreaded);
    } else {
        // 쓰레드 이진 트리 중위 순회
        TreeNode *ptr = root;
        while (ptr != NULL) {
            while (ptr->lthread == 0) {
                ptr = ptr->left;
            }
            printf("%d ", ptr->data);

            while (ptr->rthread == 1) {
                ptr = ptr->right;
                if (ptr == NULL) return;
                printf("%d ", ptr->data);
            }
            ptr = ptr->right;
        }
    }
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

// 트리에서 특정 값을 검색
TreeNode* SearchNode(TreeNode* root, int data, int isThreaded) {
    TreeNode* ptr = root;
    while (ptr != NULL) {
        if (data == ptr->data) {
            return ptr;
        }
        if (data < ptr->data) {
            if (!isThreaded || ptr->lthread == 0) {
                ptr = ptr->left;
            } else {
                break;
            }
        } else {
            if (!isThreaded || ptr->rthread == 0) {
                ptr = ptr->right;
            } else {
                break;
            }
        }
    }
    return NULL;
}

int main() {
    TreeNode *root = NULL;
    int choice, value, treeType;

    printf("트리 유형을 선택하세요 (1: 일반 이진 트리, 2: 쓰레드 이진 트리): ");
    scanf("%d", &treeType);
    int isThreaded = (treeType == 2);

    while (1) {
        printf("\n1. 삽입\n2. 삭제\n3. 검색\n4. 중위 순회\n5. 트리 출력\n6. 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("삽입할 값을 입력하세요: ");
                scanf("%d", &value);
                root = InsertNode(root, value, isThreaded);
                break;
            case 2:
                printf("삭제할 값을 입력하세요: ");
                scanf("%d", &value);
                root = DeleteNode(root, value, isThreaded);
                break;
            case 3:
                printf("검색할 값을 입력하세요: ");
                scanf("%d", &value);
                TreeNode* result = SearchNode(root, value, isThreaded);
                if (result != NULL) {
                    printf("노드를 찾았습니다: %d\n", result->data);
                } else {
                    printf("노드를 찾을 수 없습니다\n");
                }
                break;
            case 4:
                printf("중위 순회: ");
                InOrderTraversal(root, isThreaded);
                printf("\n");
                break;
            case 5:
                printf("현재 트리 구조:\n");
                PrintTree(root, 0);
                printf("\n");
                break;
            case 6:
                exit(0);
            default:
                printf("잘못된 선택입니다\n");
        }
    }

    return 0;
}