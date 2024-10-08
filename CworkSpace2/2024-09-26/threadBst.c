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
TreeNode* InsertNode(TreeNode* root, int data);
TreeNode* DeleteNode(TreeNode* root, int data);
TreeNode* InOrderSuccessor(TreeNode* ptr);
void InOrderTraversal(TreeNode* root);
void PostOrderTraversal(TreeNode* root);
void PrintTree(TreeNode* root, int space);
TreeNode* SearchNode(TreeNode* root, int data);

// 새로운 노드를 생성하고 스레드 플래그를 초기화
TreeNode* CreateNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = newNode->rthread = 1; // 스레드 초기화
    return newNode;
}

// 트리에 새로운 노드를 삽입
TreeNode* InsertNode(TreeNode* root, int data) {
    TreeNode *ptr = root;
    TreeNode *parent = NULL;

    // 삽입할 위치를 찾기 위한 반복문
    while (ptr != NULL) {
        if (data == ptr->data) {
            return root; // 중복된 값은 삽입하지 않음
        }
        parent = ptr;
        if (data < ptr->data) {
            if (ptr->lthread == 0) {
                ptr = ptr->left; // 왼쪽 자식으로 이동
            } else {
                break; // 스레드이므로 중단
            }
        } else {
            if (ptr->rthread == 0) {
                ptr = ptr->right; // 오른쪽 자식으로 이동
            } else {
                break; // 스레드이므로 중단
            }
        }
    }

    // 새로운 노드 생성
    TreeNode *newNode = CreateNode(data);
    if (parent == NULL) {
        root = newNode; // 트리가 비어있으면 새로운 노드가 루트
    } else if (data < parent->data) {
        // 부모의 왼쪽에 삽입
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0; // 왼쪽 자식이 생겼으므로 스레드 해제
        parent->left = newNode;
    } else {
        // 부모의 오른쪽에 삽입
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rthread = 0; // 오른쪽 자식이 생겼으므로 스레드 해제
        parent->right = newNode;
    }

    return root;
}

// 중위 순회에서의 후속자 찾기
TreeNode* InOrderSuccessor(TreeNode* ptr) {
    if (ptr->rthread == 1) {
        return ptr->right; // 스레드이므로 바로 후속자 반환
    }
    ptr = ptr->right;
    while (ptr->lthread == 0) {
        ptr = ptr->left; // 왼쪽 자식으로 계속 이동
    }
    return ptr;
}

// 트리에서 노드를 삭제
TreeNode* DeleteNode(TreeNode* root, int data) {
    TreeNode *parent = NULL, *ptr = root;

    // 삭제할 노드 찾기
    while (ptr != NULL) {
        if (data == ptr->data) {
            break; // 삭제할 노드 발견
        }
        parent = ptr;
        if (data < ptr->data) {
            if (ptr->lthread == 0) {
                ptr = ptr->left; // 왼쪽 자식으로 이동
            } else {
                ptr = NULL; // 스레드이므로 중단
            }
        } else {
            if (ptr->rthread == 0) {
                ptr = ptr->right; // 오른쪽 자식으로 이동
            } else {
                ptr = NULL; // 스레드이므로 중단
            }
        }
    }

    if (ptr == NULL) {
        printf("노드를 찾을 수 없습니다\n");
        return root; // 삭제할 노드가 없음
    }

    // 두 자식을 가진 노드
    if (ptr->lthread == 0 && ptr->rthread == 0) {
        TreeNode *succ = InOrderSuccessor(ptr);
        int val = succ->data;
        root = DeleteNode(root, succ->data); // 후속자를 삭제
        ptr->data = val; // 후속자의 값을 현재 노드에 복사
        return root;
    }

    // 하나 또는 자식이 없는 노드
    TreeNode *child;
    if (ptr->lthread == 1 && ptr->rthread == 1) {
        child = NULL; // 자식이 없음
    } else if (ptr->lthread == 0) {
        child = ptr->left; // 왼쪽 자식만 있음
    } else {
        child = ptr->right; // 오른쪽 자식만 있음
    }

    if (parent == NULL) {
        free(ptr);
        return child; // 루트 노드를 삭제하는 경우
    }

    if (ptr == parent->left) {
        parent->left = child;
        parent->lthread = ptr->lthread; // 스레드 상태 유지
    } else {
        parent->right = child;
        parent->rthread = ptr->rthread; // 스레드 상태 유지
    }

    // 선행자와 후속자의 스레드 조정
    TreeNode *pred = ptr->left;
    if (ptr->lthread == 0) {
        while (pred->rthread == 0) {
            pred = pred->right; // 오른쪽 자식으로 계속 이동
        }
        pred->right = ptr->right; // 후속자를 현재 노드의 후속자로 설정
    }

    TreeNode *succ = ptr->right;
    if (ptr->rthread == 0) {
        while (succ->lthread == 0) {
            succ = succ->left; // 왼쪽 자식으로 계속 이동
        }
        succ->left = ptr->left; // 선행자를 현재 노드의 선행자로 설정
    }

    free(ptr);
    return root;
}

// 중위 순회: 스레드를 활용하여 순회
void InOrderTraversal(TreeNode* root) {
    TreeNode *ptr = root;
    while (ptr != NULL) {
        while (ptr->lthread == 0) {
            ptr = ptr->left; // 왼쪽 자식으로 계속 이동
        }
        printf("%d ", ptr->data);

        while (ptr->rthread == 1) {
            ptr = ptr->right; // 스레드를 따라 후속자로 이동
            if (ptr == NULL) return;
            printf("%d ", ptr->data);
        }
        ptr = ptr->right; // 오른쪽 자식으로 이동
    }
}

// 후위 순회: 스레드 트리에서 구현하기 복잡하여 생략
void PostOrderTraversal(TreeNode* root) {
    printf("후위 순회는 스레드 이진 탐색 트리에서 지원되지 않습니다.\n");
}

// 트리의 구조를 시각적으로 출력
void PrintTree(TreeNode* root, int space) {
    printf("죄송합니다 현재 구현중입니다.\n");
}

// 트리에서 특정 값을 검색
TreeNode* SearchNode(TreeNode* root, int data) {
    TreeNode* ptr = root;
    while (ptr != NULL) {
        if (data == ptr->data) {
            return ptr; // 노드를 찾음
        }
        if (data < ptr->data) {
            if (ptr->lthread == 0) {
                ptr = ptr->left; // 왼쪽 자식으로 이동
            } else {
                break; // 스레드이므로 중단
            }
        } else {
            if (ptr->rthread == 0) {
                ptr = ptr->right; // 오른쪽 자식으로 이동
            } else {
                break; // 스레드이므로 중단
            }
        }
    }
    return NULL; // 노드를 찾지 못함
}

int main() {
    TreeNode *root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. 삽입\n2. 삭제\n3. 검색\n4. 중위 순회\n5. 후위 순회\n6. 트리 출력\n7. 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("삽입할 값을 입력하세요: ");
                scanf("%d", &value);
                root = InsertNode(root, value);
                break;
            case 2:
                printf("삭제할 값을 입력하세요: ");
                scanf("%d", &value);
                root = DeleteNode(root, value);
                break;
            case 3:
                printf("검색할 값을 입력하세요: ");
                scanf("%d", &value);
                TreeNode* result = SearchNode(root, value);
                if (result != NULL) {
                    printf("노드를 찾았습니다: %d\n", result->data);
                } else {
                    printf("노드를 찾을 수 없습니다\n");
                }
                break;
            case 4:
                printf("중위 순회: ");
                InOrderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("후위 순회: ");
                PostOrderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("현재 트리 구조:\n");
                PrintTree(root, 0);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("잘못된 선택입니다\n");
        }
    }

    return 0;
}