#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef struct StackNode {
    TreeNode *treeNode;
    struct StackNode *next;
} StackNode;

void Push(StackNode **top, TreeNode *treeNode) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->treeNode = treeNode;
    newNode->next = *top;
    *top = newNode;
}

TreeNode *Pop(StackNode **top) {
    if (*top == NULL) return NULL;
    StackNode *temp = *top;
    TreeNode *treeNode = temp->treeNode;
    *top = (*top)->next;
    free(temp);
    return treeNode;
}

int IsEmpty(StackNode *top) {
    return top == NULL;
}

void StackPreOrder(TreeNode *root) {
    StackNode *stack = NULL;
    Push(&stack, root);
    while (!IsEmpty(stack)) {
        TreeNode *node = Pop(&stack);
        if (node) {
            printf("%d ", node->data);
            Push(&stack, node->right);
            Push(&stack, node->left);
        }
    }
    printf("\n");
}

void StackInOrder(TreeNode *root) {
    StackNode *stack = NULL;
    TreeNode *current = root;
    while (!IsEmpty(stack) || current) {
        if (current) {
            Push(&stack, current);
            current = current->left;
        } else {
            current = Pop(&stack);
            printf("%d ", current->data);
            current = current->right;
        }
    }
    printf("\n");
}

void StackPostOrder(TreeNode *root) {
    StackNode *stack1 = NULL, *stack2 = NULL;
    Push(&stack1, root);
    while (!IsEmpty(stack1)) {
        TreeNode *node = Pop(&stack1);
        if (node) {
            Push(&stack2, node);
            if (node->left) Push(&stack1, node->left);
            if (node->right) Push(&stack1, node->right);
        }
    }
    while (!IsEmpty(stack2)) {
        TreeNode *node = Pop(&stack2);
        printf("%d ", node->data);
    }
    printf("\n");
}

void StackOrders(TreeNode *root) {
    printf("스택 기반 전위 순회: ");
    StackPreOrder(root);
    printf("스택 기반 중위 순회: ");
    StackInOrder(root);
    printf("스택 기반 후위 순회: ");
    StackPostOrder(root);
}

TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* CreateTree() {
    TreeNode* root = CreateNode(1);
    root->left = CreateNode(2);
    root->right = CreateNode(9);

    root->left->left = CreateNode(3);
    root->left->right = CreateNode(5);
    root->right->left = CreateNode(10);
    root->right->right = CreateNode(13);

    root->left->left->left = CreateNode(4);
    root->left->left->right = CreateNode(6);
    root->left->right->left = CreateNode(7);
    root->left->right->right = CreateNode(8);

    root->right->left->left = CreateNode(11);
    root->right->left->right = CreateNode(12);
    root->right->right->left = CreateNode(14);
    root->right->right->right = CreateNode(15);

    return root;
}

int main() {
    TreeNode *root = CreateTree();

    printf("\n-스택 기반 트리 순회-\n");
    StackOrders(root);

    return 0;
}