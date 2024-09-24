#include "TreeNode.h"
#include <stdlib.h>

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
    PlaceNode(root, 0, 5);
    PlaceNode(root, 1, 9);
PlaceNode(root->left, 0, 6);
    PlaceNode(root->left, 1, 3);
    PlaceNode(root->right, 1, 7);
    
}