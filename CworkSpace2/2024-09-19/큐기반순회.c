#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef struct QueueNode {
    TreeNode *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

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
    printf("enqueue(%d) ", treeNode->data);
}

TreeNode *Dequeue(Queue *queue) {
    if (queue->front == NULL) return NULL;
    QueueNode *temp = queue->front;
    TreeNode *treeNode = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    printf("dequeue(%d) ", treeNode->data);
    return treeNode;
}

int IsQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

void LinkedPreOrder(TreeNode *root) {
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

void LinkedInOrder(TreeNode *root) {
    Queue queue = {NULL, NULL};
    TreeNode *current = root;
    while (!IsQueueEmpty(&queue) || current) {
        if (current) {
            Enqueue(&queue, current);
            current = current->left;
        } else {
            current = Dequeue(&queue);
            printf("visit(%d) ", current->data);
            current = current->right;
        }
    }
    printf("\n");
}

void LinkedPostOrder(TreeNode *root) {
    Queue queue1 = {NULL, NULL}, queue2 = {NULL, NULL};
    Enqueue(&queue1, root);
    while (!IsQueueEmpty(&queue1)) {
        TreeNode *node = Dequeue(&queue1);
        if (node) {
            Enqueue(&queue2, node);
            if (node->left) Enqueue(&queue1, node->left);
            if (node->right) Enqueue(&queue1, node->right);
        }
    }
    while (!IsQueueEmpty(&queue2)) {
        TreeNode *node = Dequeue(&queue2);
        printf("visit(%d) ", node->data);
    }
    printf("\n");
}

void LinkOrders(TreeNode *root) {
    printf("큐 기반 전위 순회: ");
    LinkedPreOrder(root);
    printf("큐 기반 중위 순회: ");
    LinkedInOrder(root);
    printf("큐 기반 후위 순회: ");
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

    printf("\n-큐 기반 트리 순회-\n");
    LinkOrders(root);

    return 0;
}