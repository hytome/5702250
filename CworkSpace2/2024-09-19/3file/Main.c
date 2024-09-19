#include "ItrTreeTrv.h"
#include <stdio.h>
#include <stdlib.h>

// 함수 선언 추가
void GenerateLinkTree(TreeNode *root);

int main() {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;
    printf("트리 생성\n");
    GenerateLinkTree(root);
    printf("\n-큐 기반 트리 순회-\n");
    LinkOrders(root);
    
    return 0;
}