#include "TreeOperations.h"
#include "Queue.h"
#include <stdio.h>

int CountNodes(TreeNode *root) {
    if (root == NULL) return 0;
    int leftCount = CountNodes(root->left);
    int rightCount = CountNodes(root->right);
    return 1 + leftCount + rightCount;
    //현재노드(1) + 왼쪽노드(2) + 오른쪽노드(3) = 6
}

int Height(TreeNode *root) {
    if (root == NULL) return 0;
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    //왼쪽 서브트리와 오른쪽 서브트리의 높이를 비교하여 높은 값에 1을 더한 값을 반환
    //여기서 1은 루트노드의 높이를 의미한다에요.
}

int SumTree(TreeNode *root) {
    if (root == NULL) return 0;
    int leftSum = SumTree(root->left);
    int rightSum = SumTree(root->right);
    return root->data + leftSum + rightSum;
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