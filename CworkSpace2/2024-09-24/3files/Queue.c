#include "Queue.h"
#include <stdlib.h>

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

TreeNode* Dequeue(Queue *queue) {
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

int IsQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}