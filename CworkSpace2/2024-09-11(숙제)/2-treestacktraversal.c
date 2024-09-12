#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef struct StackNode {
    //스택 노드 구조체 
    TreeNode *treeNode;
    struct StackNode *next;
    //다음 노드를 가르키기 위한 포인터.
} StackNode;

void Push(StackNode **top, TreeNode *treeNode) {
    //스택에 노드를 추가하기 위한 함수.
    if (treeNode == NULL) return; 
    //노드가 비어있으면 종료
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    //새로운 노드 생성
    newNode->treeNode = treeNode;
    //새로운 노드의 트리노드를 현재 노드로 설정
    newNode->next = *top;
    //새로운 노드의 다음 노드를 현재 스택의 최상위 노드로 설정
    *top = newNode;
    //스택의 최상위 노드를 새로운 노드로 설정
    printf("push(%d) ", treeNode->data);
}

TreeNode *Pop(StackNode **top) {
    //스택에서 노드를 제거하기 위한 함수.
    if (*top == NULL) return NULL; 
    //스택이 비어있으면 종료
    StackNode *temp = *top;
    TreeNode *treeNode = temp->treeNode;
    //스택의 최상위 노드를 임시 노드로 저장
    *top = (*top)->next;
    //스택의 최상위 노드를 다음 노드로 설정
    free(temp);
    //임시 노드를 해제
    printf("pop(%d) ", treeNode->data);
    //제거된 노드의 데이터를 출력.
    return treeNode;
    //제거된 노드를 반환
}

int IsEmpty(StackNode *top) {
    return top == NULL;
}

void LinkedPreOrder(TreeNode *root) {
    //전위  순회  과정
    StackNode *stack = NULL;
    Push(&stack, root);
    while (!IsEmpty(stack)) {
        TreeNode *node = Pop(&stack);
        if (node) {
            printf("visit(%d) ", node->data);
            printf("\n");
            Push(&stack, node->right);
            //전위 순회 과정에서 오른쪽 노드를 먼저 방문하고 왼쪽 노드를 방문하는 이유는 스택의 특성 때문
            //스택은 선입후출 구조이기 때문 
            Push(&stack, node->left);
        }
    }
    printf("\n");
}

void LinkedInOrder(TreeNode *root) {
    //중위 순회 과정
    StackNode *stack = NULL;
    TreeNode *current = root;
    while (!IsEmpty(stack) || current) {
        if (current) {
            Push(&stack, current);
            current = current->left;
            //왼쪽 자식으로 이동.
        } else {
            //중위 순회 과정에서 왼쪽 노드를 모두 방문한 후 오른쪽 노드를 방문하는 이유는 스택의 특성 때문
            //스택은 선입후출 구조이기 때문 
            current = Pop(&stack);
            printf("visit(%d) ", current->data);//방문한 노드 출력
            
            printf("\n");
            current = current->right;//방문한 노드의 오른쪽 자식으로 이동. 
        }
    }
    printf("\n");
}

void LinkedPostOrder(TreeNode *root) {
    //후위 순회 과정
    StackNode *stack1 = NULL, *stack2 = NULL;
    //첫번째 스택:노드를 저장하고 왼쪽과 오른쪽 자식을 푸시 합니다.
    //두번째 스택: 노드를 팝하고 방문합니다.
    Push(&stack1, root);
    //먼저 루트 노드를 스택1에 푸시 
    while (!IsEmpty(stack1)) {
        TreeNode *node = Pop(&stack1);
        //스택1에서 노드를 꺼내서 방문
        //스택1에서 노드를 팝하고 스택2에 푸시
        if (node) {
            
            Push(&stack2, node);
            //스택2에 푸시.
            if (node->left) Push(&stack1, node->left);
          //팝한 노드의 왼쪽 자식을 스택1에 푸시
            if (node->right) Push(&stack1, node->right);
            //팝한 노드의 오른쪽 자식을 스택1에 푸시
        }
    }
    //두번째 스택에서 노드를 팝하고 방문 
    while (!IsEmpty(stack2)) {
        //스택2가 비어있지 않는 동안 반복합니다.
        TreeNode *node = Pop(&stack2);
        //방문한 노드 출력
        printf("visit(%d) ", node->data);
        
        printf("\n");
    }
    printf("\n");
}

void LinkOrders(TreeNode *root) {
    printf("스택기반 전위 순회 : ");
    LinkedPreOrder(root);
    printf("스택기반 중위 순회: ");
    LinkedInOrder(root);
    printf("스택기반 후위 순회: ");
    LinkedPostOrder(root);
}

TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void PlaceNode(TreeNode *node, int direction, int data) {
    if (direction == 0) {
        node->left = CreateNode(data);
    } else {
        node->right = CreateNode(data);
    }
}

void GenerateLinkTree(TreeNode *root) {
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

int main() {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;

    GenerateLinkTree(root);

    printf("\n-스택 기반 트리 순회-\n");
    LinkOrders(root);

    return 0;
}