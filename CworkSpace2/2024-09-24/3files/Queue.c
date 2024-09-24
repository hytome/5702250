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

int QueueSize(Queue *queue) {  // QueueSize 함수 정의 추가
    int size = 0;
    QueueNode *current = queue->front;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}