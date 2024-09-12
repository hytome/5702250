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
    if (treeNode == NULL) return; 
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->treeNode = treeNode;
    newNode->next = *top;
    *top = newNode;
    printf("push(%d) ", treeNode->data);
}

TreeNode *Pop(StackNode **top) {
    if (*top == NULL) return NULL; 
    StackNode *temp = *top;
    TreeNode *treeNode = temp->treeNode;
    *top = (*top)->next;
    free(temp);
    printf("pop(%d) ", treeNode->data);
    return treeNode;
}

int IsEmpty(StackNode *top) {
    return top == NULL;
}

void LinkedPreOrder(TreeNode *root) {
    StackNode *stack = NULL;
    Push(&stack, root);
    while (!IsEmpty(stack)) {
        TreeNode *node = Pop(&stack);
        if (node) {
            printf("visit(%d)\ ", node->data);
            printf("\n");
            Push(&stack, node->right);
            Push(&stack, node->left);
        }
    }
    printf("\n");
}

void LinkedInOrder(TreeNode *root) {
    StackNode *stack = NULL;
    TreeNode *current = root;
    while (!IsEmpty(stack) || current) {
        if (current) {
            Push(&stack, current);
            current = current->left;
        } else {
            current = Pop(&stack);
            printf("visit(%d) ", current->data);
            printf("\n");
            current = current->right;
        }
    }
    printf("\n");
}

void LinkedPostOrder(TreeNode *root) {
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
        printf("visit(%d) ", node->data);
        printf("\n");
    }
    printf("\n");
}

void LinkOrders(TreeNode *root) {
    printf("스택기반 전위 순회 : ");
    LinkedPreOrder(root);
    printf("스택기반 중위 순회: ");
    LinkedInOrder(root);
    printf("스택기반 후위 순회: ");
    LinkedPostOrder(root);
}

TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void PlaceNode(TreeNode *node, int direction, int data) {
    if (direction == 0) {
        node->left = CreateNode(data);
    } else {
        node->right = CreateNode(data);
    }
}

void GenerateLinkTree(TreeNode *root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

int main() {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;

    GenerateLinkTree(root);

    printf("\n-스택 기반 트리 순회-\n");
    LinkOrders(root);

    return 0;
}