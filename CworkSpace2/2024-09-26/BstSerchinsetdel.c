#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* CreateNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* InsertNode(TreeNode* root, int data) {
    if (root == NULL) {
        return CreateNode(data);
    }
    if (data < root->data) {
        root->left = InsertNode(root->left, data);
    } else if (data > root->data) {
        root->right = InsertNode(root->right, data);
    }
    return root;
}

TreeNode* SearchNode(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return SearchNode(root->left, data);
    } else {
        return SearchNode(root->right, data);
    }
}

TreeNode* FindMin(TreeNode* node) {
    while (node->left != NULL) node = node->left;
    return node;
}

TreeNode* DeleteNode(TreeNode* root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = DeleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = DeleteNode(root->right, data);
    } else {
        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }
        // Case 2: One child
        else if (root->left == NULL) {
            TreeNode* temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            TreeNode* temp = root;
            root = root->left;
            free(temp);
        }
        // Case 3: Two children
        else {
            TreeNode* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = DeleteNode(root->right, temp->data);
        }
    }
    return root;
}

void InOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        InOrderTraversal(root->left);
        printf("%d ", root->data);
        InOrderTraversal(root->right);
    }
}

int main() {
    TreeNode *root = NULL;
    root = InsertNode(root, 50);
    InsertNode(root, 30);
    InsertNode(root, 20);
    InsertNode(root, 40);
    InsertNode(root, 70);
    InsertNode(root, 60);
    InsertNode(root, 80);

    printf("In-order traversal before deletion:\n");
    InOrderTraversal(root);
    printf("\n");

    root = DeleteNode(root, 20);
    printf("In-order traversal after deleting 20:\n");
    InOrderTraversal(root);
    printf("\n");

    root = DeleteNode(root, 30);
    printf("In-order traversal after deleting 30:\n");
    InOrderTraversal(root);
    printf("\n");

    root = DeleteNode(root, 50);
    printf("In-order traversal after deleting 50:\n");
    InOrderTraversal(root);
    printf("\n");

    return 0;
}