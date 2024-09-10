#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
}TreeNode;

//       15
//    4       20
// 1      16  25

TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4, &n1, NULL};
TreeNode n3 = {16, NULL, NULL};
TreeNode n4 = {25, NULL, NULL};
TreeNode n5 = {20, &n3, &n4};
TreeNode n6 = {15, &n2, &n5};
TreeNode *root = &n6;

//중위 순회.
//중위 순회: 왼쪽 자식 노드 -> 현재 노드 -> 오른쪽 자식 노드 순으로 방문
void inorder(TreeNode *root){
    //1.매개변수: 트리의 루트 노드를 가리키는 포인터
    //-현재 방문 중인 노드를 가리키는 포인터 입니다.
    //반환값: 없음
    //기능: 중위 순회를 이용하여 트리의 모든 노드를 출력
    //2.조건문.
    if(root != NULL){
        //root가 NULL이 아니면 중위 순회를 이용하여 트리의 모든 노드를 출력
        inorder(root->left);
        //현재 노드의 왼쪽 자식 노드를 가리키는 포인터
        //왼쪽 자식 노드를 중위 순회 합니다.
        printf("%d ", root->data);
        //현재 노드의 데이터를 출력합니다.
        inorder(root->right);
        //마지막으로 오른쪽 자식 노드를 방문합니다.
    }
}   

//전위 순외.
//전위 순회: 현재 노드 -> 왼쪽 자식 노드 -> 오른쪽 자식 노드 순으로 방문
void preorder(TreeNode *root){
    if(root){
        //root에 값이 있을 경우. 이 조건문이 돌아간다. 
        printf("%d ", root->data);
        //현재 노드의 데이터를 출력.
        preorder(root->left);
        //현재 노드의 왼쪽 자식 노드를 전위 순외.
        preorder(root->right); 
        //현재 노드의 오른쪽 자식 노드를 전위 순외. 
    }
}
//후위 순외.
//후위 순회: 왼쪽 자식 노드 -> 오른쪽 자식 노드 -> 현재 노드 순으로 방문
void postorder(TreeNode *root){
    if(root){
        postorder(root->left);
        //현재 노드의 왼쪽 자식 노드를 후위 순외.
        postorder(root->right);
        //현재 노드의 오른쪽 자식 노드를 후위 순외.
        printf("%d ", root->data);
        //현재 노드의 데이터를 출력.
    }
}

int main(){
    //중위 순회 출력.
    printf("중위 순회: ");
    inorder(root);
    printf("\n");
    //전위 순회 출력.
    printf("전위 순회: ");
    preorder(root);
    printf("\n");
    //후위 순회 출력.   
    printf("후위 순회: ");
    postorder(root);
    printf("\n");
    return 0;
}
