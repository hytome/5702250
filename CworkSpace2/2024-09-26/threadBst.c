#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
    int lthread, rthread; // 스레드 플래그 추가
} TreeNode;

TreeNode* CreateNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = newNode->rthread = 1; // 스레드 초기화
    return newNode;
}

TreeNode* InsertNode(TreeNode* root, int data) {
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

TreeNode* DeleteNode(TreeNode* root, int data) {
    TreeNode *parent = NULL, *ptr = root;

    // Find the node to be deleted
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
        printf("Node not found\n");
        return root;
    }

    // Node with two children
    if (ptr->lthread == 0 && ptr->rthread == 0) {
        TreeNode *succ = InOrderSuccessor(ptr);
        int val = succ->data;
        root = DeleteNode(root, succ->data);
        ptr->data = val;
        return root;
    }

    // Node with one or no child
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

void InOrderTraversal(TreeNode* root) {
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

void PostOrderTraversal(TreeNode* root) {
    // 후위 순회는 스레드 트리에서 구현하기 복잡하므로 생략
    printf("Post-order traversal is not supported in threaded BST.\n");
}

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
    int choice, value;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. In-order Traversal\n5. Post-order Traversal\n6. Print Tree\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = InsertNode(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = DeleteNode(root, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                TreeNode* result = SearchNode(root, value);
                if (result != NULL) {
                    printf("Node found: %d\n", result->data);
                } else {
                    printf("Node not found\n");
                }
                break;
            case 4:
                printf("In-order traversal: ");
                InOrderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Post-order traversal: ");
                PostOrderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Current tree structure:\n");
                PrintTree(root, 0);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}