#ifndef QUEUE_H
#define QUEUE_H
//헤더가드: 헤더파일이 여러번 포함되는걸 방지하기 위함.
//교수님이 쓰시는 prgma ones랑 같은 역할이라고 생각하면 됨.
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
int QueueSize(Queue *queue);

#endif // QUEUE_H