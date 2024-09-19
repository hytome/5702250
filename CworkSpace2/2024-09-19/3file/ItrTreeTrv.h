#pragma once
#include <stdlib.h>
#include <stdio.h>



typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode; 

void LinkOrders(TreeNode *root);
void GenerateLinkTree(TreeNode *root);
void LevelOrder(TreeNode *root);
void PlaceNode(TreeNode *parent, int direction, int data);
TreeNode *CreateNode(int data);

