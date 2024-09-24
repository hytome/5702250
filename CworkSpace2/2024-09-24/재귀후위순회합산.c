#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// 큐 노드 구조체 정의
typedef struct QueueNode {
    TreeNode *treeNode;
    struct QueueNode *next;
} QueueNode;

// 큐 구조체 정의
typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

// 새로운 트리 노드를 생성하는 함수
TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 노드를 특정 위치에 배치하는 함수
void PlaceNode(TreeNode *node, int direction, int data) {
    if (direction == 0) {
        node->left = CreateNode(data);
    } else {
        node->right = CreateNode(data);
    }
}

int CountNodes(TreeNode *root) {
    //노드의 개수를 세는 함수
    if (root == NULL) return 0; // 기저 조건: 노드가 NULL이면 0 반환
    int leftCount = CountNodes(root->left); // 왼쪽 서브트리의 노드 개수 계산
    int rightCount = CountNodes(root->right); // 오른쪽 서브트리의 노드 개수 계산
    return 1 + leftCount + rightCount; // 현재 노드를 포함한 총 노드 개수 반환
}
int Height(TreeNode *root) {
    //노드의 높이를 계산하는 함수
    if (root == NULL) return 0; // 기저 조건: 노드가 NULL이면 높이는 0
    int leftHeight = Height(root->left); // 왼쪽 서브트리의 높이 계산
    int rightHeight = Height(root->right); // 오른쪽 서브트리의 높이 계산
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight); // 현재 노드의 높이 반환
}



// 트리를 생성하는 함수
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

// 큐에 노드를 삽입하는 함수
void Enqueue(Queue *queue, TreeNode *treeNode) {
    if (treeNode == NULL) return;
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (queue->rear) {
        queue->rear->next = newNode;
    } else {
        queue->front = newNode;
    }
    queue->rear = newNode;
}

// 큐에서 노드를 제거하고 반환하는 함수
TreeNode *Dequeue(Queue *queue) {
    if (queue->front == NULL) return NULL;
    QueueNode *temp = queue->front;
    TreeNode *treeNode = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return treeNode;
}

// 큐가 비어있는지 확인하는 함수
int IsQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

// 트리의 모든 노드를 레벨 순서대로 출력하는 함수
void PrintLevelOrder(TreeNode *root) {
    if (root == NULL) return;
    Queue queue = {NULL, NULL};
    Enqueue(&queue, root);
    while (!IsQueueEmpty(&queue)) {
        TreeNode *node = Dequeue(&queue);
        printf("%d ", node->data);
        if (node->left) Enqueue(&queue, node->left);
        if (node->right) Enqueue(&queue, node->right);
    }
    printf("\n");
}
// 트리의 모든 숫자의 합을 계산하는 함수 (후위 순회 사용)
int SumTree(TreeNode *root) {
    if (root == NULL) return 0;
    int leftSum = SumTree(root->left);
    //왼쪽 서브트리의 합을 계산 
    int rightSum = SumTree(root->right);
    //오른쪽 서브트리의 합을 계산
    return root->data + leftSum + rightSum;
    //현재의 노드의 값을 더하여 반환. 
}

// 후위 순회 함수
void PostOrder(TreeNode *root) {
    //우위 순회는 트리의 왼쪽->오른쪽->루트 순으로 방문하는 방식이다. 
    if (root == NULL) return;
    //노드가 null이면 재귀 종료 
    PostOrder(root->left);
    //1-1.왼쪽 서브 트리를 순회. 1일 경우에 노드2가된다.
    //1-2. 2의 왼쪽 서브트리인 3를 재귀적으로 또 방문한다.
    //1-3. 3의 왼쪽 서브트리인 4를 재귀적으로 또 방문한다.
    //1-4. 4의 왼쪽 서브트리인 없으니 재귀 종료.
    PostOrder(root->right);
    //1-6. 노드 3의 오른쪽 서브트리인 6을 재귀적으로 방문한다.
    //1-7. 노드 6는 자식이 없다.
    printf("visit(%d) ", root->data);
    //1-5. 4의 자식은 없으므로 visit(4) 출력 후 재귀 종료
    //1-8. 노드 6의 자식은 없으므로 visit(6) 출력 후 재귀 종료
}

int main() {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;

    GenerateLinkTree(root);

    printf("트리의 모든 노드: ");
    PrintLevelOrder(root);
    printf("\n");

    printf("\n-후위 순회-\n");
    PostOrder(root);
    printf("\n");

    int totalSum = SumTree(root);
    printf("트리의 모든 숫자의 합: %d\n", totalSum);

    int nodeCount = CountNodes(root);
    printf("트리의 노드 개수: %d\n", nodeCount);



    int height = Height(root);
    printf("트리의 높이: %d\n", height);
    return 0;
}