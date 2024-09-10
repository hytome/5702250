#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
    //왼쪽 자식 노드와 오른쪽 자식 노드를 가리키는 포인터 변수.
}TreeNode;

#define SIZE 100
//스택의 크기를 100으로 정의. 즉 스택에는 최대 100개의 TreeNode 포인터를 저장할 수 있음.
int top= -1;
//스택의 최상위 요소를 가리키는 인덱스를 나타낸다.
//초기값은 -1로 설정되어 스택이 비어있음을 나타낸다. 
TreeNode *stack[SIZE];
//TreeNode 포인터를 저장할수 있는 배열을 선언합니다.
//이 배열은 스택으로 사용되며,트리 노드의 주소로 저장됩니다. 
//이 스택은 재귀적인 함수 호출을 대신하여 사용됩니다. 
//따라서 재귀를 사용하지 않고 반복적으로 트리를 순회할 수 있습니다.

//스택에 노드의 주소를 저장하는 함수. push.
void push(TreeNode *p){
    if(top < SIZE-1){
        stack[++top] = p;
        //스택에 현재 노드의 주소를 저장.
    }
}

TreeNode *pop(){
    TreeNode *p = NULL;
    //현재 노드의 주소를 저장할 포인터 p를 null로 초기화.
    if(top >=0){
        //조건문을 통해 스택이 비어있지 않은 경우에만 실행.
            p = stack[top--];
            //스택의 최상위 요소를 가리키는 포인터 p에 저장하고, top을 하나 감소시킴.
    }
    return p;
    //현재 노드의 주소를 반환.
}

void inorder_iter(TreeNode *root){
    //중위 순회를 반복적으로 구현하는 함수.
    while(1){
        //무한 루프를 시작.
        for(;root;root = root->left){
            //현재 노드가 null이 아니면 왼쪽 자식 노드로 이동.
            push(root);
            //현재 노드의 주소를 스택에 저장.
        }
        root = pop();
        //스택에서 노드의 주소를 꺼내옴.
        if(!root) break;
        //노드가 null이면 루프를 종료.
            printf("[%d] ", root->data);
            //현재 노드의 데이터를 출력.
             root = root->right;
            //현재 노드의 오른쪽 자식 노드로 이동.
    }
}

//       15
//    4       20
// 1      16  25

TreeNode n1 = {1, NULL, NULL};
//1 밑에는 어떠한 자식노드가 없음.
TreeNode n2 = {4, &n1, NULL};
//4 밑에는 1이라는 자식노드가 있음.
TreeNode n3 = {16, NULL, NULL};
//16 밑에는 어떠한 자식노드가 없음.
TreeNode n4 = {25, NULL, NULL}; 
//25 밑에는 어떠한 자식노드가 없음.
TreeNode n5 = {20, &n3, &n4};
//20 밑에는 16과 25라는 자식노드가 있음.
TreeNode n6 = {15, &n2, &n5};
//15 밑에는 4와 20이라는 자식노드가 있음.
TreeNode *root = &n6;
//15이라는 노드가 루트 노드가 됨.

int main(void){
    printf("중위 순회: ");
    inorder_iter(root);
    printf("\n");
    return 0;
}