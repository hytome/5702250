#include "ItrTreeTrv.h"
#include "Queue.h" // Queue.c를 직접 포함하지 않고 Queue.h를 포함합니다.
#include <stdio.h>
#include <stdlib.h>

void LinkOrders(TreeNode *root) {
    printf("큐 기반 레벨 순회: ");
    if (root == NULL) {
        printf("트리가 비어 있습니다.\n");
        return;
    }
    LevelOrder(root);
}

void LevelOrder(TreeNode *root) {
    Queue queue;
    InitQueue(&queue);
    Enqueue(&queue, root);
    while (!IsQueueEmpty(&queue)) {
        TreeNode *treeNode = Dequeue(&queue);
        printf("%d ", treeNode->data);  
        if (treeNode->left) Enqueue(&queue, treeNode->left);
        if (treeNode->right) Enqueue(&queue, treeNode->right);
    }
}

TreeNode *CreateNode(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void PlaceNode(TreeNode *parent, int direction, int data) {
    if (direction == 0) {
        parent->left = CreateNode(data);
    } else {
        parent->right = CreateNode(data);
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
}