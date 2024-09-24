#ifndef QUEUE_H
#define QUEUE_H

#include "TreeNode.h"

typedef struct QueueNode {
    TreeNode *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

void Enqueue(Queue *queue, TreeNode *treeNode);
TreeNode* Dequeue(Queue *queue);
int IsQueueEmpty(Queue *queue);

#endif // QUEUE_H