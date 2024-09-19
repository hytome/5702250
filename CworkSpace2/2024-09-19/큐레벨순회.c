#include <stdio.h>
#include <stdlib.h>
//큐 자료구조를 이용하여 이진트리를 레벨 순회 하는 방식.
typedef struct TreeNode {
    //트리노드: 이진트리의 각 노드를 나타내며.
    int data; //데이터와 
    struct TreeNode *left, *right;
    //왼쪽,오른쪽 자식을 가르키는 포인터를 가집니다.
} TreeNode;

//QueueNode의 역할과 기능.
//큐의 각요소를 나타내며 선입선출 특성을 유지하는데 중요한 역할을 한다.
//큐에 삽입되는 각 트리노드를 이 구조체를 통해 저장됩니다.
//next포인터를 통해 연결 리스트 형태를 구현합니다.
//이는 큐의 front 와 rear을 이동시키며 효율적으로 요소를 삽입하고 삭제할 수 있게 합니다.
typedef struct QueueNode {
    //큐노드 구조체는 큐의 자료구조를 구현하는데 사용된다.
    TreeNode *treeNode;
    //큐에 저장될 실제 트리노드를 가르키는 포인트 입니다.
    //이로인하여 트리노드의 data left right에 순차적으로 접근하고 관리할수 있게 됩니다. 
    struct QueueNode *next;
    //다음 QueueNode를 가르키는 포인터입니다.
    //큐는 연결리스트 형태로 구현되며 각 QueueNode는 자기 자신과 다음 노드를 연결합니다.
    //next 포인터는 큐에서 현재 노드의 다음 위치에 있는 노드를 가르키며 이를 통해 큐의 순서를 유지하고,
    //노드 간의 연결을 관리 할수 있습니다.
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

//Enqueue 함수는 노드에 큐를 삽입하는 함수입니다.
//그러나 노드가 null일 경우 삽입하지 않습니다.
void Enqueue(Queue *queue, TreeNode *treeNode) {
    //QueueNode의 메모리 관리.
    if (treeNode == NULL) return;
    //새로운 트리 노드가 null이 아닌 경우에만 큐에 삽입.
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    //새로운 큐노드를 동적 메모리 할당으로 생성하여 트리 노드를 큐에 삽입하고
    //DeQueue 함수에서 큐에서 노드를 제거하고 메모리를 해제 합니다.
    //이를 통해 효율적인 메모리 관리를 지원합니다.
    newNode->treeNode = treeNode;
    //newnode의 treenode 필드에 삽입할 treenode 포인터를 저장하고.
    newNode->next = NULL;
    //newnode의 next 필드를 null로 초기화 합니다.
    if (queue->rear) {
        //큐가 비어 있지 않으면 (rear가 null이 아니면)
        queue->rear->next = newNode;
        //큐의 rear노드의 next 포인터를 newnode로 설정하여 큐의 끝에 연결합니다 . 
    } else {
        queue->front = newNode;
         //큐가 비어 있으면 (front가 null이면)
        //front 포인터를 newNOde로 설정하여 큐의 첫번쨰 노드로 설정합니다.
    }
    queue->rear = newNode;
    //rear 포인터를 newnode로 업데이트 하여 큐의 뒤를 가르키도록합니다.
    printf("enqueue(%d) ", treeNode->data);
    //삽입한 노드의 데이터를 출력하여 큐의 상태를 확인합니다.
}

//Dequeue 함수는 큐의 앞에서 트리노드를 제거하고 반환합니다.
//큐가 비어있으면 null을 반환합니다.
TreeNode *Dequeue(Queue *queue) {
    if (queue->front == NULL) return NULL;
    //큐가 비어있으면 null을 반환합니다.
    QueueNode *temp = queue->front;
    //front에 있는 Queuenode를 제가하기 위해 temp 포인터에 현재 front 노드를 저장합니다.
    //비유:큐의 앞에 있는 사람이 식당에서 음식을 받을 준비를 하고 있는것,여기서 temp는 그사람을 가르키는 포인터.
    TreeNode *treeNode = temp->treeNode;
    //Queuenode에 저장된 실제 트리 노드를 추출하여 treeNode에 저장합니다.
    //temp의 treenode 필드를 통해 삭제할 treenode를 추출합니다.
    //비유: 식당에서 음식을 받은 사람(temp)이 자신의 접시(treeNode)를 들고 식당을 떠나는 것과 같습니다.
    queue->front = queue->front->next;
    //목적:큐의 앞 front 포인터를 다음노드로 이동 시켜 큐에서 첫번째 노드를 제거하는 것.
    //큐의 front 포인터를 다음 노드로 이동시킵니다.(즉 현재 큐의 두번쨰 노드를 가르키도록 하는것.)
    //이를통해 큐의 앞을 다음 노드로 업데이트 하여 첫번쨰 노드를 큐에서 제외시킵니다.
    //비유:방금 첫번쨰 손님(temp)이 식사를 마치고 접시를(treeNode) 가지고 떠난후 두번쨰 손님이 이제 식사를 받을 준비가 끝난것.

    if (queue->front == NULL) {
        //만약 큐가 비게 된다
        queue->rear = NULL;
        //rear 포인터도 null로 설정하여 큐가 비어있음을 나타냅니다.
    }
    free(temp);
    //제거된 queuenode 메모리를 free를 통해 해제합니다.
    printf("dequeue(%d) ", treeNode->data);
    //삭제된 노드의 데이터를 출력하여 큐의 상태를 확인합니다.
    return treeNode;
    //삭제된 treenode를 반환합니다.
}
//예시:front -> [Node1(data=1)] -> [Node2(data=2)] -> [Node3(data=3)] -> NULL
//rear --------------------------------------------↑

//Dequeue 함수 호출 후:
//1.temp는 Node1을 가리킵니다.
//2.treeNode는 Node1의 TreeNode 포인터를 저장합니다.
//3.queue->front는 Node2로 업데이트됩니다.
//4.Node1의 메모리가 해제됩니다.
//5.Node1의 데이터인 1이 출력됩니다.
//6.treeNode (Node1의 데이터)를 반환합니다.
//7.업데이트된 큐 상태는 다음과 같습니다:

//front -> [Node2(data=2)] -> [Node3(data=3)] -> NULL
//rear ----------------------------↑

int IsQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

void LevelOrder(TreeNode *root) {
    Queue queue = {NULL, NULL};
    Enqueue(&queue, root);
    while (!IsQueueEmpty(&queue)) {
        TreeNode *node = Dequeue(&queue);
        if (node) {
            printf("visit(%d) ", node->data);
            Enqueue(&queue, node->left);
            Enqueue(&queue, node->right);
        }
    }
    printf("\n");
}

void LinkOrders(TreeNode *root) {
    printf("큐 기반 레벨 순회: ");
    LevelOrder(root);
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

    printf("\n-큐 기반 트리 순회-\n");
    LinkOrders(root);

    return 0;
}