#include <stdio.h>
#include <stdlib.h>
#include "TreeNode.h"
#include "TreeOperations.h"

int main() {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    int NumberOfLeafNodes(TreeNode *root);
    root->data = 1;
    root->left = root->right = NULL;

    GenerateLinkTree(root);

    printf("트리의 모든 노드: ");
    PrintLevelOrder(root);
    printf("\n");

    printf("\n-후위 순회-\n");
    PostOrder(root);
    printf("\n");

    int totalSum = SumTree(root);
    printf("트리의 모든 숫자의 합: %d\n", totalSum);

    int nodeCount = CountNodes(root);
    printf("트리의 노드 개수: %d\n", nodeCount);

    int height = Height(root);
    printf("트리의 높이: %d\n", height);

    int leafCount = NumberOfLeafNodes(root);
    printf("트리의 리프 노드 개수: %d\n", leafCount);

    return 0;
}