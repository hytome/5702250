#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

int main(void){
    TreeNode *n1, *n2, *n3;
    // 노드 생성
    // n1
    // / |
    // n2 n3
    
    n1 = (TreeNode*)malloc(sizeof(TreeNode));
    n2 = (TreeNode*)malloc(sizeof(TreeNode));
    n3 = (TreeNode*)malloc(sizeof(TreeNode));
    
    n1 -> data = 10; //n1의 노드 설정.
    // n1의 왼쪽 노드 설정. 
    n1 -> left = n2;
    // n1의 오른쪽 노드 설정.
    n1 ->right = n3;

    n2 -> data = 20; //n2의 노드 설정.
    n2 -> left = NULL; //n2의 왼쪽 노드는 존재하지 않으니 null.
    n2 -> right = NULL; //n2의 오른쪽 노드는 존재하지 않으니 null.

    n3 -> data = 30; //n3의 노드 설정.
    n3 -> left = NULL; //n3의 왼쪽 노드는 존재하지 않으니 null.
    n3 -> right = NULL; //n3의 오른쪽 노드는 존재하지 않으니 null.

    //노드 출력문.
    printf("n1의 왼쪽 노드 : %d\n", n1->left->data);
    printf("n1의 오른쪽 노드 : %d\n", n1->right->data);
    printf("n2의 왼쪽 노드 : %d\n", n2->left);
    printf("n2의 오른쪽 노드 : %d\n", n2->right);
    printf("n3의 왼쪽 노드 : %d\n", n3->left);
    printf("n3의 오른쪽 노드 : %d\n", n3->right);

    free(n1); //동적 할당 해제. 
    free(n2);
    free(n3);
    
    return 0;

    
}
