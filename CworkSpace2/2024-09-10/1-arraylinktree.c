#include <stdio.h>
#include <stdlib.h>


//배열과 링크를 이용한 트리 생성 및 순회 

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

void GenerateArrayTree(int *tree) {
    // list에 트리 순서에 맞는 수 입력
    int list[15] = {1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
        
    }
    printf("\n");
}

void ArrayPreOrder(int *tree) {
    // 전위 순회
    int order[15] = {0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 11, 12, 6, 13, 14};
    //Index:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
    //Value:  1  2  9  3  5 10 13  4  6  7  8 11 12 14 15
    //전위 순회는 루트-> 왼쪽 -> 오른쪽 순서로 노드를 방문합니다.
    //따라서 순회 순서를  order의 순서대로 하여 전위 순화를 출력.
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[order[i]]);
        //출력: 1 2 3 4 6 5 7 8 9 10 11 12 13 14 15
        //tree[order[0~14]];
        //이러한 구조로 전위 순회 출력 가능. 
    }
    printf("\n");
}

void ArrayInOrder(int *tree) {
    // 중위 순회
    // 중위 순회는 왼쪽->루트->오른쪽 순서로 배출. 
    int order[15] = {7, 3, 8, 1, 9, 4, 10, 0, 11, 5, 12, 2, 13, 6, 14};
    //Index:  7  3  8  1  9  4 10  0 11  5 12  2 13  6 14
    //Value:  4  3  6  2  7  5  8  1 11 10 12  9 14 13 15
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[order[i]]);
    }
    printf("\n");
}

void ArrayPostOrder(int *tree) {
    // 후위 순회
    // 후위 순회는 왼쪽->오른쪽->루트 순서로 방문하여 출력.
    int order[15] = {7, 8, 3, 9, 10, 4, 1, 11, 12, 5, 13, 14, 6, 2, 0};
    //Index:  7  8  3  9 10  4  1 11 12  5 13 14  6  2  0
    //Value:  4  6  3  7  8  5  2 11 12 10 14 15 13  9  1
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[order[i]]);
        //출력: 4 6 3 7 8 5 2 11 12 10 14 15 13 9 1
    }
    printf("\n");
}

void ArrayOrders(int *tree) {
    ArrayPreOrder(tree);
    ArrayInOrder(tree);
    ArrayPostOrder(tree);
}

// 노드를 만들고 입력받은 노드의 direction(0:left, 1:right)값에 따라
// 올바른 위치에 해당 노드를 배치하는 함수
void PlaceNode(TreeNode *node, int direction, int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    } else {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode *root) {
    //앞선 placeNode를 이용해 좌,우 를 구분 지어 노드 생성.
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);

    

}
void LinkPreOrder(TreeNode *root) {
    if (root) {
        printf("%d ", root->data);
        LinkPreOrder(root->left);
        LinkPreOrder(root->right);
    }
}

void LinkInOrder(TreeNode *root) {
    if (root) {
        LinkInOrder(root->left);
        printf("%d ", root->data);
        LinkInOrder(root->right);
    }
}

void LinkPostOrder(TreeNode *root) {
    if (root) {
        LinkPostOrder(root->left);
        LinkPostOrder(root->right);
        printf("%d ", root->data);
    }
}

void LinkOrders(TreeNode *root) {
    LinkPreOrder(root);
    printf("\n");
    LinkInOrder(root);
    printf("\n");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15];
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;
    // 루트 노드 생성 1로 초기화 
    root->left = root->right = NULL;

    // 각각의 방식(array법, link법)에 따른 트리 호출
    GenerateArrayTree(arr);
    GenerateLinkTree(root);
    // 각각의 방식(array법, link법)에 따른 트리 순회 
    printf("\n");
    
    ArrayOrders(arr);
    LinkOrders(root);

    return 0;
}