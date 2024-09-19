#pragma once

#include "ItrTreeTrv.h"  // TreeNode 정의 포함

typedef struct QueueNode {
    TreeNode *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

// 함수 선언
void InitQueue(Queue *queue);
void Enqueue(Queue *queue, TreeNode *node);
TreeNode* Dequeue(Queue *queue);
int IsQueueEmpty(Queue *queue);
