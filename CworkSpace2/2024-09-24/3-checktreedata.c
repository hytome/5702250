#include <stdio.h>
#include <stdlib.h>

//재귀 후위 순회 방식이 아닌 큐를 이용하여 반복적으로 트리와 노드를 방문해보자!
//트리를 구성할 노드.
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;


//큐를 구성할 노드.
typedef struct QueueNode{
    TreeNode *treeNode;
    //트리 노드와 큐를 연결하기 위해 포인터 변수 선언.
    struct QueueNode *next;

}QueueNode;

typedef struct Queue{
    QueueNode *front, *rear;
}Queue;

TreeNode* CreateNode(int data){
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL){
        printf("메모리 할당 실패\n");
        exit(1);
    }
    //malloc함수로 새로운 노드를 생성하고 그 노드의 주소와 크기를 newNode에 할당.
    newNode->data = data;
    //newnode의 data변수에 매게 변수로 받은 data를 저장. 
    newNode->left = newNode->right = NULL;
    //노드의 왼쪽과 오른쪽 즉 자식 트리를 null로 초기화. 
    return newNode;
    //생성된 노드의 주소를 반환. 
}

void PlaceNode(TreeNode *node, int direction, int data){
    if(direction == 0){
        node->left = CreateNode(data);
        //0일때 왼쪽 자식 노드를 생성하고 데이터를 저장
    }else{
        node->right = CreateNode(data);
        //1일떄 오른쪽 노드를 생성하고 저장.
    }
}

//큐 넣었다 뺐다 하는 기능을 넣어봅시다~
void Enqueue(Queue *queue, TreeNode *treeNode){
    if (treeNode == NULL) return;
    //트리 노드가 null이면 함수 종료.
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL){
        printf("메모리 할당 실패\n");
        exit(1);
    }
    //새로운 큐  노드를 생성하고 동적할당. 
    newNode->treeNode = treeNode;
    //새로운 큐 노드의 트리 노드를 매개변수로 받은 트리 노드로 초기화
    //뉴노드에 트리노드를 삽입할 트리노드 포인터 저장.
    newNode->next = NULL;
    //새로운 큐 노드의 다음 노드를 null로 초기화.

    if (queue->rear) {
        //큐가 비어있지 않으면 
        queue->rear->next = newNode;
        //큐의 마지막 노드의 다음노드를 큐로 설정한다에요.
    } else {
        queue->front = newNode;
        //큐가 비어있다면 가장 앞,즉 front에 새로운 노드를 설정한다에요.
    }
    queue->rear = newNode;
    //큐의 마지막 노드를 새로운 노드로 업데이트 한다에요.
    //큐는 선입선출 구조라서 가장 먼저 들어온 노드가 가장 먼저 나가는 구조라는 점을 기억하자에요.

}

//큐 빼는 기능.
TreeNode *Dequeue(Queue *queue){
    if (queue->front == NULL) return NULL;
    //큐가 비어있으면 null을 반환.
    QueueNode *temp = queue->front;
    //큐의 맨 앞 노드를 임시 노드에 저장. 큐는 선입 선출 구조이기 때문에.
    //가장 먼저 들어온 노드가 나가야 한다에요 .
    TreeNode *treeNode = temp->treeNode;
    //임시 노드의 트리 노드를 트리 노드에 저장.
    //temp에 있는 트리노드를 들고 떠나는것이에요.
    queue->front = temp->next;
    //이제 아까 떠난 노드의 자리를 차지하는 다음노드로 업데이트 해야한다에요
    //이렇게 가장 먼저 들어온 노드를 순차적으로 뺼수 있다에요.
    //큐의 맨 앞 노드를 임시 노드의 다음 노드로 업데이트.
    if (queue->front == NULL){
        //만약 큐가 비어있다면?
        queue->rear = NULL;
        //큐가 비어있으면 마지막 노드도 null로 설정하게 해준다에요.
    }
    free(temp);
    //임시 노드의 메모리 해제.
    return treeNode;
    //트리 노드를 반환.
}

int IsQueueEmpty(Queue *queue){
    return queue->front == NULL;
}
//큐가 비어있는지 확인하는 함수.

//QueueSize:큐의 크기를 반환하는 함수.
//이를 이용하여 트리의 총합,노드의 갯수, 노드의 높이를 구할수 있다에요.
int QueueSize(Queue *queue){
    int size = 0;
    //먼저 큐의 크기를 저장할 변수를 선언하고 0으로 초기화 한다에요.
    QueueNode *current = queue->front;
    //1-2.큐의 맨앞 노드를 가리키는 포인터를 초기화 한다에요. 큐의 맨 앞 노드부터 시작하여 큐의 모든 노드를 순회하는 용도다에요 
    while (current != NULL){
        //현재 노드가 null이 아닐때 까지 반복한다에요.
        size++;
        //노드가 존재하므로 큐의 크기를 1 증가시킨다에요.
        current = current->next;
        //1-1.다음 노드를 가리키도록 포인터를 이동해요,현재 노드의 다음 노드로 이동하여.
        //반복문 으로 큐의 모든 노드를 순회할 수 있다에요.
    }
    return size;
    //큐의 크기를 반환한다에요.
    //큐의 모든 노드를 순회하고- 큐에 이쓴 노드의 총 갯수를 반환한다에요.
}

//이제 트리의 총합,노드의 갯수, 노드의 높이를 구하는 함수.
//재귀함수와 다르게 함수 하나로 전부 구현이 될꺼 같아 하나로 전부 구현.
void CalculateTreeProperties(TreeNode *root, int *sum, int *nodeCount, int *height, int *leafCount) {
    if (root == NULL) {
        //root가 null인경우 트리가 비어있으므로.
        *sum = 0;
        *nodeCount = 0;
        *height = 0;
        //합계,노드의 갯수,높이를 0으로 초기화 합니다.
        return;
    }

    Queue queue = {NULL, NULL};
    //큐를 초기화 합니다.
    Enqueue(&queue, root);
    //큐에 루트 노드를 추가합니다.
        //queue는 front 와 rear이 null인 빈큐로 시작합니다.
    *sum = 0;
    *nodeCount = 0;
    *height = 0;
    *leafCount = 0;
    //합계,노드의 갯수,높이를 0으로 초기화 합니다.
    while (!IsQueueEmpty(&queue)) {
        //큐가 비어있지 않는동안 반복합니다.
        int levelSize = QueueSize(&queue);
        //현재 레벨의 노드수를 계산하는 용도에요. QueueSize함수를 이용하여 큐에있는 노드수를 반환해요.
        (*height)++;
        //레벨의 모든 노드수를 반환했으니 높이를 1 증가시켜요.
        for (int i = 0; i < levelSize; i++) {
            //현재 레벨의 모든 노드를 처리하기 위한 for문이에요.
            //queue에 있는 선입 선출 방식.
            TreeNode *current = Dequeue(&queue);
            //큐에서 노드를 하나꺼내서(선입선출) current에 저장해요.
            (*sum) += current->data;
            //current에 있는 노드의 값을 sum에 저장합니다.
            (*nodeCount)++;
            //이제 노드를 하나처리 했으니~ 노드의 개수를 1 증가 시킵니다. 
            if (current->left == NULL && current->right == NULL){
                //현재노드 currrent 의 왼쪽 자식노드와 오른쪽 자식 노드 둘다 존재하지 않을때.
                (*leafCount)++;
                //현재 노드가 리프 노드일 경우 리프 노드의 개수를 1 증가시킵니다.
                //리프노드니까 카운트를 증가시킵니다.
            }
            if (current->left) Enqueue(&queue, current->left);
            //current의 왼쪽 자식이 있으면 큐에 추가합니다.
            if (current->right) Enqueue(&queue, current->right);
            //current의 오른쪽 자식이 있으면 큐에 추가합니다.
        }
    }
}
//노드의 구성요소를 만드는 함수다에요
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
//메모리 해제 함수.
void FreeTree(TreeNode *root) {
    if (root == NULL) return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

int main() {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;
    GenerateLinkTree(root);
    int sum, nodeCount, height, leafCount;
    CalculateTreeProperties(root, &sum, &nodeCount, &height, &leafCount);

    printf("Sum of Nodes: %d\n", sum);
    printf("Number of Nodes: %d\n", nodeCount);
    printf("Height of Tree: %d\n", height);
    printf("Number of Leaf Nodes: %d\n", leafCount);
    //트리의 모든 노드를 해제합니다.
    FreeTree(root);
    return 0;
}