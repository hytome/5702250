#ifndef TREENODE_H
#define TREENODE_H
//헤더가드: 헤더파일이 여러번 포함되는걸 방지하기 위함.
//교수님이 쓰시는 prgma ones랑 같은 역할이라고 생각하면 됨.
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* CreateNode(int data);
void PlaceNode(TreeNode *node, int direction, int data);
void GenerateLinkTree(TreeNode *root);

#endif // TREENODE_H