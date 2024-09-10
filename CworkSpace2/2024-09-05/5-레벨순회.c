#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

//레벨 순회:각 노드를 레벨 순으로 검사하는 순회방법.
//지금 까지의 순회 법이 스택을 이용하여 순화하는 방법이라면.
//레벨 순회는 큐를 이용하여 순회 하는 방법이다.

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;

}TreeNode;

#define MAX_QUEUE_SIZE 100
