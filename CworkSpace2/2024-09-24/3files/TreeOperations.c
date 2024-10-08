#include "TreeOperations.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
//반복문을 이용한 방식의 기능.

int CountNodes(TreeNode *root) {
    if (root == NULL) return 0;
    int count = 0;
    Queue queue = {NULL, NULL};
    Enqueue(&queue, root);
    while (!IsQueueEmpty(&queue)) {
        TreeNode *node = Dequeue(&queue);
        count++;
        if (node->left) Enqueue(&queue, node->left);
        if (node->right) Enqueue(&queue, node->right);
    }
    return count;
}

int Height(TreeNode *root) {
    if (root == NULL) return 0;
    int height = 0;
    Queue queue = {NULL, NULL};
    Enqueue(&queue, root);
    while (!IsQueueEmpty(&queue)) {
        int nodeCount = QueueSize(&queue);
        height++;
        while (nodeCount > 0) {
            TreeNode *node = Dequeue(&queue);
            if (node->left) Enqueue(&queue, node->left);
            //둘의 높이계산
            if (node->right) Enqueue(&queue, node->right);
            nodeCount--;
        }
    }
    return height;
}

int SumTree(TreeNode *root) {
    if (root == NULL) return 0;
    int sum = 0;
    Queue queue = {NULL, NULL};
    Enqueue(&queue, root);
    while (!IsQueueEmpty(&queue)) {
        TreeNode *node = Dequeue(&queue);
        sum += node->data;
        if (node->left) Enqueue(&queue, node->left);
        if (node->right) Enqueue(&queue, node->right);
    }
    return sum;
}

int NumberOfLeafNodes(TreeNode *root) {
    //자식이 없는 노드.
    if (root == NULL) return 0;
    int leafCount = 0;
    Queue queue = {NULL, NULL};
    Enqueue(&queue, root);
    while (!IsQueueEmpty(&queue)) {
        TreeNode *node = Dequeue(&queue);
        if (node->left == NULL && node->right == NULL) {
            leafCount++;
        }
        if (node->left) Enqueue(&queue, node->left);
        if (node->right) Enqueue(&queue, node->right);
    }
    return leafCount;
}

void PostOrder(TreeNode *root) {
    if (root == NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    printf("visit(%d) ", root->data);
}

void PrintLevelOrder(TreeNode *root) {
    if (root == NULL) return;
    Queue queue = {NULL, NULL};
    Enqueue(&queue, root);
    while (!IsQueueEmpty(&queue)) {
        TreeNode *node = Dequeue(&queue);
        printf("%d ", node->data);
        if (node->left) Enqueue(&queue, node->left);
        if (node->right) Enqueue(&queue, node->right);
    }
    printf("\n");
}