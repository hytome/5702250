#include <stdio.h>
#include <stdlib.h>
#define SPACE_INCREMENT 10

// 트리 구조체 및 함수 선언
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// 스택 구조체 및 함수 선언
typedef struct StackNode {
    struct TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

Stack* CreateStack();
void Push(Stack* stack, struct TreeNode* treeNode);
struct TreeNode* Pop(Stack* stack);
int IsStackEmpty(Stack* stack);
void FreeStack(Stack* stack);

// 큐 구조체 및 함수 선언
typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

Queue* CreateQueue();
void Enqueue(Queue* queue, TreeNode* treeNode);
TreeNode* Dequeue(Queue* queue);
int IsQueueEmpty(Queue* queue);
void FreeQueue(Queue* queue);

// 트리 함수 선언
TreeNode* CreateNode(int data);
TreeNode* InsertNode(TreeNode* root, int data);
TreeNode* SearchNode(TreeNode* root, int data);
TreeNode* FindMin(TreeNode* node);
TreeNode* DeleteNode(TreeNode* root, int data);
void InOrderTraversal(TreeNode* root);
void PostOrderTraversal(TreeNode* root);
void PrintTree(TreeNode* root, int space);
void FreeTree(TreeNode* root);

// 스택 함수 정의
Stack* CreateStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void Push(Stack* stack, struct TreeNode* treeNode) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->treeNode = treeNode;
    newNode->next = stack->top;
    stack->top = newNode;
}

struct TreeNode* Pop(Stack* stack) {
    if (IsStackEmpty(stack)) return NULL;
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    TreeNode* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

int IsStackEmpty(Stack* stack) {
    return stack->top == NULL;
}

void FreeStack(Stack* stack) {
    while (!IsStackEmpty(stack)) {
        Pop(stack);
    }
    free(stack);
}

// 큐 함수 정의
Queue* CreateQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void Enqueue(Queue* queue, TreeNode* treeNode) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

TreeNode* Dequeue(Queue* queue) {
    if (queue->front == NULL) return NULL;
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    TreeNode* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

int IsQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

void FreeQueue(Queue* queue) {
    while (!IsQueueEmpty(queue)) {
        Dequeue(queue);
    }
    free(queue);
}

// 트리 함수 정의
TreeNode* CreateNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* InsertNode(TreeNode* root, int data) {
    TreeNode* newNode = CreateNode(data);
    if (root == NULL) {
        return newNode;
    }
    TreeNode* current = root;
    TreeNode* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return root;
}

TreeNode* SearchNode(TreeNode* root, int data) {
    TreeNode* current = root;
    while (current != NULL && current->data != data) {
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

TreeNode* FindMin(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

TreeNode* DeleteNode(TreeNode* root, int data) {
    TreeNode* parent = NULL;
    TreeNode* current = root;
    while (current != NULL && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (current == NULL) return root;

    if (current->left == NULL || current->right == NULL) {
        TreeNode* newCurrent;
        if (current->left == NULL) {
            newCurrent = current->right;
        } else {
            newCurrent = current->left;
        }
        if (parent == NULL) {
            free(current);
            return newCurrent;
        }
        if (current == parent->left) {
            parent->left = newCurrent;
        } else {
            parent->right = newCurrent;
        }
        free(current);
    } else {
        TreeNode* p = NULL;
        TreeNode* temp;
        temp = current->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }
        if (p != NULL) {
            p->left = temp->right;
        } else {
            current->right = temp->right;
        }
        current->data = temp->data;
        free(temp);
    }
    return root;
}

void InOrderTraversal(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* current = root;
    Stack* stack = CreateStack();
    while (current != NULL || !IsStackEmpty(stack)) {
        while (current != NULL) {
            Push(stack, current);
            current = current->left;
        }
        current = Pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
    FreeStack(stack);
}

void PostOrderTraversal(TreeNode* root) {
    if (root == NULL) return;
    Stack* stack1 = CreateStack();
    Stack* stack2 = CreateStack();
    Push(stack1, root);
    while (!IsStackEmpty(stack1)) {
        TreeNode* node = Pop(stack1);
        Push(stack2, node);
        if (node->left) Push(stack1, node->left);
        if (node->right) Push(stack1, node->right);
    }
    while (!IsStackEmpty(stack2)) {
        TreeNode* node = Pop(stack2);
        printf("%d ", node->data);
    }
    FreeStack(stack1);
    FreeStack(stack2);
}



void PrintTree(TreeNode* root, int space) {
    if (root == NULL) return;
    space += SPACE_INCREMENT;
    PrintTree(root->left, space);  // 왼쪽 자식을 먼저 출력
    printf("\n");
    for (int i = SPACE_INCREMENT; i < space; i++) printf(" ");
    printf("%d\n", root->data);
    PrintTree(root->right, space);  // 오른쪽 자식을 나중에 출력
}

void FreeTree(TreeNode* root) {
    if (root == NULL) return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

int main() {
    TreeNode *root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. In-order Traversal\n5. Post-order Traversal\n6. Print Tree\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = InsertNode(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = DeleteNode(root, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                TreeNode* result = SearchNode(root, value);
                if (result != NULL) {
                    printf("Node found: %d\n", result->data);
                } else {
                    printf("Node not found\n");
                }
                break;
            case 4:
                printf("In-order traversal: ");
                InOrderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Post-order traversal: ");
                PostOrderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Current tree structure:\n");
                PrintTree(root, 0);
                printf("\n");
                break;
            case 7:
                FreeTree(root);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}