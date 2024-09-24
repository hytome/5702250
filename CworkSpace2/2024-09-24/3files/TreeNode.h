#ifndef TREENODE_H
#define TREENODE_H

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* CreateNode(int data);
void PlaceNode(TreeNode *node, int direction, int data);
void GenerateLinkTree(TreeNode *root);

#endif // TREENODE_H