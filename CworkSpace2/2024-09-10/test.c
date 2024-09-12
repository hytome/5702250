#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 15

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

void GenerateArrayTree(int* tree) {
    //이 함수는 메인 함수의 arr 배열을 초기화 하고, 출력하는 함수이다.
    int list[15] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };
    // .        1
    // .   2          9
    // . 3   5     10    13
    // 4 6  7 8  11 12 14 15
    //트리의 구조는 이렇게 되어있다
    for (int i = 0; i < 15; i++) {
        //배열의 인덱스는 0부터 시작하기 때문에 15개의 원소를 가진 배열에 대해 15번 반복하면서 값을 넣어준다.
        tree[i] = list[i];
        //트리의 구조에 list가 들어간다.
    }

    for (int i = 0; i < 15; i++) {
        printf("%2d ", tree[i]);
        //15번 동안 배열의 값을 출력하는 기능.
    }
    printf("\n");
}

void ArrayPreOrder(int* tree, int index) {
    //배열을 이용한 전위 순회 함수.
    if (index < MAX_SIZE && tree[index] != -1) {
        //현재 노드의 인덱스가 배열의 크기를 넘지 않는지 확인한다.
        //현재 노드가 유효한지 확인한다.
        //만약 tree[index]가 -1이면 유효하지 않은 노드이기 때문에 재귀함수를 호출하지 않는다.
        printf("[%2d] ", tree[index]);
        //현재 노드의 값을 출력한다.
        ArrayPreOrder(tree, 2 * index + 1);
        //왼쪽 자식 노드를 방문한다.
        ArrayPreOrder(tree, 2 * index + 2);
        //오른쪽 자식 노드를 방문한다.
    }
}

void ArrayInorder(int* tree, int index) {
    //배열을 이용한 중위 함수.
    //중위함수: 왼쪽 자식 노드 -> 현재 노드 -> 오른쪽 자식 노드
    if (index < MAX_SIZE && tree[index] != -1) {
        //현재 노드의 인덱스가 배열의 크기를 넘지 않는지 확인한다.
        //현재 노드가 유효한지 확인한다.
        //만약 tree[index]가 -1이면 유효하지 않은 노드이기 때문에 재귀함수를 호출하지 않는다.
        ArrayInorder(tree, 2 * index + 1);
        //왼쪽 자식 노드를 방문한다.
        printf("[%2d] ", tree[index]);
        //현재 노드의 값을 출력한다.
        ArrayInorder(tree, 2 * index + 2);
        //오른쪽 자식 노드를 방문한다.
    }
}

void ArrayPostOrder(int* tree, int index) {
    //배열을 이용한 후위 함수.
    //후위함수: 왼쪽 자식 노드 -> 오른쪽 자식 노드 -> 현재 노드
    if (index < MAX_SIZE && tree[index] != -1) {
        //현재 노드의 인덱스가 배열의 크기를 넘지 않는지 확인한다.
        //현재 노드가 유효한지 확인한다.
        //만약 tree[index]가 -1이면 유효하지 않은 노드이기 때문에 재귀함수를 호출하지 않는다.
        ArrayPostOrder(tree, 2 * index + 1);
        //왼쪽 자식 노드를 방문한다.
        ArrayPostOrder(tree, 2 * index + 2);
        //오른쪽 자식 노드를 방문한다.
        printf("[%2d] ", tree[index]);
        //현재 노드의 값을 출력한다.
    }
}

void ArrayOrders(int* tree) {
    printf("Preorder: ");
    ArrayPreOrder(tree, 0);
    printf("\n");

    printf("Inorder: ");
    ArrayInorder(tree, 0);
    printf("\n");

    printf("Postorder: ");
    ArrayPostOrder(tree, 0);
    printf("\n");
}

void PlaceNode(TreeNode** node, int data) {
    //이 함수는 메인 함수의 root 노드에 데이터를 넣는 함수이다.
    if (*node == NULL) {
        // 만약 현재 노드가 NULL이면 새로운 노드를 생성(루트),그 이후 데이터에 삽입한다.
        *node = (TreeNode*)malloc(sizeof(TreeNode));
        //동적할당으로 노드를 생성한다. 
        (*node)->data = data;
        //노드의 데이터에 삽입한다.
        (*node)->left = NULL;
        //왼쪽 자식 노드를 NULL로 초기화한다.
        (*node)->right = NULL;
        //오른쪽 자식 노드를 NULL로 초기화한다.
    }
    else {
        if (data < (*node)->data) {
            //만약 데이터가 현재 노드의 데이터보다 작으면 왼쪽 자식 노드에 삽입한다.
            PlaceNode(&((*node)->left), data);
            //재귀함수를 호출하여 왼쪽 자식 노드에 삽입한다.
            //이진탐색트리는 왼쪽 서브트리의 모든 노드의 값이 현재 노드의 값보다 작아야 한다.
        }
        else {
            PlaceNode(&((*node)->right), data);
            //재귀함수를 호출하여 오른쪽 자식 노드에 삽입한다.
            //이진탐색트리는 오른쪽 서브트리의 모든 노드의 값이 현재 노드의 값보다 커야 한다.
        }
    }
}
//create node:단순히 노드를 생성하는 함수.
//place node: 생성된 노드를 트리의 적절한 위치에 삽입하는 역할.
TreeNode* CreateNode(int data) {
    //이 함수는 메인 함수의 노드를 생성하는 함수이다.
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    //동적할당으로 노드를 생성한다.
    newNode->data = data;
    //노드의 데이터에 삽입한다.
    newNode->left = NULL;
    //왼쪽 자식 노드를 NULL로 초기화한다.
    
    newNode->right = NULL;
    //오른쪽 자식 노드를 NULL로 초기화한다.
    return newNode;
}

void GenerateLinkTree(TreeNode** root) {
    TreeNode* nodes[15];
    //조교님 이 정해주신 15개의 노드를  담을수  있는  배열.
    int list[15] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };
    //array tree와 동일한 값을 가진 리스트.
    for (int i = 0; i < 15; i++) {
        nodes[i] = CreateNode(list[i]);
        //배열의 각 인덱스에 노드를 생성하고(create node함수) 그 노드의 값을 리스트의 값으로 초기화한다.
    }
    //이진 탐색 트리에서 각 노드의 왼쪽 자식 노드와 오른쪽 자식 노드를 결정하는 과정.
    for (int i = 0; i < 15; i++) {
        if (2 * i + 1 < 15) {
            nodes[i]->left = nodes[2 * i + 1];
            //왼쪽 자식 노드를 결정한다.
            //2*i+1은 왼쪽 자식 노드의 인덱스이다.
            //15는 배열의 크기이다.
            //만약 2*i+1이 15보다 작으면 왼쪽 자식 노드를 결정한다.
            //인덱스의 번호에 따른 이진트리, 구조참고. 
        }
        if (2 * i + 2 < 15) {
            nodes[i]->right = nodes[2 * i + 2];
            //오른쪽 자식 노드를 결정한다.
            //2*i+2는 오른쪽 자식 노드의 인덱스이다.
            //15는 배열의 크기이다.
            //만약 2*i+2이 15보다 작으면 오른쪽 자식 노드를 결정한다.
        }
    }
    //root 노드를 결정한다.

    *root = nodes[0];
}

void LinkPreOrder(TreeNode* root) {
    if (root != NULL) {
        printf("%2d ", root->data);
        LinkPreOrder(root->left);
        LinkPreOrder(root->right);
    }
}

void LinkInOrder(TreeNode* root) {
    if (root != NULL) {
        LinkInOrder(root->left);
        printf("%2d ", root->data);
        LinkInOrder(root->right);
    }
}

void LinkPostOrder(TreeNode* root) {
    if (root != NULL) {
        LinkPostOrder(root->left);
        LinkPostOrder(root->right);
        printf("%2d ", root->data);
    }
}

void LinkOrders(TreeNode* root) {
    printf("Preorder: ");
    LinkPreOrder(root);
    printf("\n");

    printf("Inorder: ");
    LinkInOrder(root);
    printf("\n");

    printf("Postorder: ");
    LinkPostOrder(root);
    printf("\n");
}

void FreeTree(TreeNode* root) {
    if (root != NULL) {
        FreeTree(root->left);
        FreeTree(root->right);
        free(root);
    }
}

int main(void) {
    int arr[MAX_SIZE];
    TreeNode* root = NULL;

    GenerateArrayTree(arr);
    ArrayOrders(arr);

    GenerateLinkTree(&root);
    LinkOrders(root);

    FreeTree(root);
    return 0;
}