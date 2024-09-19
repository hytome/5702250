#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

// 함수 정의
void InitQueue(Queue *queue) {
    queue->front = queue->rear = NULL;
}

void Enqueue(Queue *queue, TreeNode *node) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->data = node;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

TreeNode* Dequeue(Queue *queue) {
    if (queue->front == NULL) return NULL;
    QueueNode *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    TreeNode *node = temp->data;
    free(temp);
    return node;
}

int IsQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}