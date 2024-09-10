#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// 새 노드 생성 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// BST에 노드 삽입 함수
Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data);
    
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    
    return root;
}

// 중위 순회 함수
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 메인 함수
int main() {
    Node* root = NULL;
    int values[] = {5, 3, 7, 1, 4, 6, 8};
    int n = sizeof(values) / sizeof(values[0]);

    // BST 구성
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printf("중위 순회 결과 (오름차순 정렬): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}