#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

void GenerateArrayTree(int *tree) {
    int list[15] = {1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};
    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }
}

void ArrayPreOrder(int *tree) {
    int order[15] = {0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 11, 12, 6, 13, 14};
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[order[i]]);
    }
    printf("\n");
}

void ArrayInOrder(int *tree) {
    int order[15] = {7, 3, 8, 1, 9, 4, 10, 0, 11, 5, 12, 2, 13, 6, 14};
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[order[i]]);
    }
    printf("\n");
}

void ArrayPostOrder(int *tree) {
    int order[15] = {7, 8, 3, 9, 10, 4, 1, 11, 12, 5, 13, 14, 6, 2, 0};
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[order[i]]);
    }
    printf("\n");
}

void ArrayOrders(int *tree) {
    printf("배열 기반 전위 순회: ");
    ArrayPreOrder(tree);
    printf("배열 기반 중위 순회: ");
    ArrayInOrder(tree);
    printf("배열 기반 후위 순회: ");
    ArrayPostOrder(tree);
}

void PlaceNode(TreeNode *node, int direction, int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    } else {
        node->right = newNode;
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

void LinkPreOrder(TreeNode *root) {
    if (root) {
        printf("%d ", root->data);
        LinkPreOrder(root->left);
        LinkPreOrder(root->right);
    }
}

void LinkInOrder(TreeNode *root) {
    if (root) {
        LinkInOrder(root->left);
        printf("%d ", root->data);
        LinkInOrder(root->right);
    }
}

void LinkPostOrder(TreeNode *root) {
    if (root) {
        LinkPostOrder(root->left);
        LinkPostOrder(root->right);
        printf("%d ", root->data);
    }
}

void LinkOrders(TreeNode *root) {
    printf("연결 리스트 기반 전위 순회: ");
    LinkPreOrder(root);
    printf("\n");
    printf("연결 리스트 기반 중위 순회: ");
    LinkInOrder(root);
    printf("\n");
    printf("연결 리스트 기반 후위 순회: ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15];
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;

    // 각각의 방식(array법, link법)에 따른 트리 생성
    GenerateArrayTree(arr);
    GenerateLinkTree(root);

    // 각 생성한 트리 순회
    printf("배열 기반 트리 순회:\n");
    ArrayOrders(arr);
    printf("\n연결 리스트 기반 트리 순회:\n");
    LinkOrders(root);

    return 0;
}