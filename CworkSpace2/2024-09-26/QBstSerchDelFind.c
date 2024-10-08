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
    //TreeNode 와 StackNode를 서로 연결하기 위한 용도입니다.
    struct StackNode* next;
    //stackNode의 Next 즉 다음노드를 가르키는(연결하기 위한)용도입니다.
} StackNode;

typedef struct Stack {
    //Stack의 구조체 자체를 가르키는 용도입니다.
    StackNode* top;
    //Stack의 가장 높은 노드를 가르키는 용도입니다.
} Stack;

//Stack을 수행할 함수들 선언 파트 입니다.
//stack 형태의 구조체를 생성하는 함수입니다.
Stack* CreateStack();
void Push(Stack* stack, struct TreeNode* treeNode);
//Stack에 노드를 추가하는 (push) 함수입니다.
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
void InOrderTraversal(TreeNode* root);//중위순회
void PostOrderTraversal(TreeNode* root);//후위순회
void LevelOrderTraversal(TreeNode* root);//레벨 순회로 트리 출력
void FreeTree(TreeNode* root); 

// 스택 함수 정의
Stack* CreateStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    //새로운 스택을 동적할당으로 생성합니다.
    stack->top = NULL;
    //스택의 top을 null로 초기화 합니다.
    return stack;
}

//스택에 노드를 추가하는 함수.
void Push(Stack* stack, struct TreeNode* treeNode) {
    //넘어오는 매게변수는 스택과 트리노드 입니다.
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    //새로운 스택 노드를 동적할당으로 생성합니다.
    newNode->treeNode = treeNode;
    //새로운 스택노드의 트리노드를 넘어온 트리노드로 연결합니다.
    newNode->next = stack->top;
    //새로운 스택노드의 다음노드를 스택의 top으로 연결합니다.
    stack->top = newNode;
    //스택의 top을 새로운 스택노드로 연결합니다.
    //이로써 스택에 노드를 추가하는 함수가 완성되었습니다.
}

//스택에서 노드를 삭제하는 함수.
struct TreeNode* Pop(Stack* stack) {
    //넘어오는 매게변수는 스택입니다.
    if (IsStackEmpty(stack)) return NULL;
    //스택이 비어있으면 null을 반환합니다.
    StackNode* temp = stack->top;
    //스택의 top을 temp:임시변수에 저장합니다.
    stack->top = stack->top->next;
    //스택의 top을 스택의 top의 다음노드로 변경합니다.
    TreeNode* treeNode = temp->treeNode;
    //temp의 트리노드를 treeNode에 저장합니다.
    free(temp);
    //temp를 해제합니다.
    return treeNode;
    //treeNode를 반환합니다.
    //이과정에서 최근에 추가된 노드가 가장 먼저 제거되므로 선입 후출에 원칙이 지켜집니다.
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
//큐 삽입함수 
void Enqueue(Queue* queue, TreeNode* treeNode) {
    //넘어오는 매게변수는 큐와 트리노드
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    //큐노드 동적할당으로 생성.
    newNode->treeNode = treeNode;
    //큐노드의 트리노드는 넘어온 트리 노드를 가르키도록 합니다.
    newNode->next = NULL;
    //큐노드의 다음 노드를 null로 초기화 합니다.
    if (queue->rear == NULL) {
        //큐의 뒤가 널이면 큐의 앞과 뒤가 새로운 노드를 가르키도록 합니다.
        queue->front = queue->rear = newNode;
        //큐의 앞과 뒤에 새로운 노드를 가르키고 반환합니다.
        return;
    }
    queue->rear->next = newNode;
    //큐의 뒤에 다음노드는 새로운 노드를 가르키도록 합니다.
    queue->rear = newNode;
    //큐의 뒤가 새로운 노드를 가르키도록 합니다.
}

//큐 삭제함수 
TreeNode* Dequeue(Queue* queue) {
    //넘어오는 매게변수는 큐입니다.
    if (queue->front == NULL) return NULL;
    //큐의 앞이 null이면 더이상 값이 없다는 것이니 null을 반환합니다.
    QueueNode* temp = queue->front;
    //큐의 앞을 temp:임시변수에 저장합니다.
    queue->front = queue->front->next;
    //큐의 앞을 큐의 앞의 다음노드로 변경합니다.
    if (queue->front == NULL) queue->rear = NULL;
    //큐의 앞이 null이면 큐의 뒤도 null로 초기화 합니다.
    TreeNode* treeNode = temp->treeNode;
    //큐의 앞(temp)의 트리노드를 treeNode에 저장합니다.
    free(temp);
    //temp를 해제합니다.
    return treeNode;
    //treeNode를 반환합니다.
    //이로써 큐의 앞에서 노드를 삭제하고 반환하는 함수가 완성되었습니다
}

//큐가 비어있는지 확인하는 함수
int IsQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

//큐를 해제하는 함수
void FreeQueue(Queue* queue) {
    while (!IsQueueEmpty(queue)) {
        Dequeue(queue);
    }
    free(queue);
}

// 트리 함수 정의
//트리노드를 생성하는 함수 
TreeNode* CreateNode(int data) {
    //넘어오는 매게변수는 데이터 입니다
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    //새로운 트리노드를 동적할당으로 생성합니다.
    newNode->data = data;
    //새로운 트리노드의 데이터를 넘어온 데이터로 초기화 합니다.
    newNode->left = newNode->right = NULL;
    //새로운 트리노드의 왼쪽과 오른쪽을 null로 초기화 합니다.
    return newNode;
    //새로운 트리노드를 반환합니다.
}

//트리에 노드를 삽입하는 함수.
TreeNode* InsertNode(TreeNode* root, int data) {
    TreeNode* newNode = CreateNode(data);
    if (root == NULL) {
        //루트가 null이면 
        return newNode;
        //새로운 트리노드를 반환합니다.
    }
    TreeNode* current = root;
    //현재 노드를 root로 초기화 합니다
    TreeNode* parent = NULL;
    //부모노드를 null로 초기화 합니다.
    while (current != NULL) {
        //현재 노드가 null이 아니면 반복합니다.
        parent = current;
        //부모노드를 현재노드로 초기화 합니다.
        if (data < current->data) {
            //넘어온 데이터가 현재노드의 데이터보다 작으면
            current = current->left;
            //현재노드를 현재노드의 왼쪽으로 이동합니다.
            //bst의 왼쪽은 작은 값을 가지는 노드들이 위치하는 곳입니다.
        } else {
            current = current->right;
            //넘어온 데이터가 현재노드의 데이터보다 크면
            //현재노드를 현재노드의 오른쪽으로 이동합니다.
            //bst의 오른쪽은 큰 값을 가지는 노드들이 위치하는 곳입니다.
        }
    }
    if (data < parent->data) {
        //넘어온 데이터가 부모노드의 데이터보다 작으면
        parent->left = newNode;
        //부모노드의 왼쪽에 새로운 노드를 연결합니다.
    } else {
        parent->right = newNode;
        //부모노드의 오른쪽에 새로운 노드를 연결합니다.
    }
    return root;    
    //root를 반환합니다.
}

//트리에서 노드를 찾는 함수입니다.
TreeNode* SearchNode(TreeNode* root, int data) {
    //넘어오는 매게변수는 루트와 데이터 입니다.
    TreeNode* current = root;
    //현재 노드를 root로 초기화 합니다.
    while (current != NULL && current->data != data) {
        //현재 노드가 null이 아니고 현재 노드의 데이터가 넘어온 데이터와 같지 않으면 반복합니다.
        if (data < current->data) {
            //넘어온 데이터가 현재 노드의 데이터보다 작으면
            current = current->left;
            //현재 노드를 현재 노드의 왼쪽으로 이동합니다.
        } else {
            current = current->right;
            //넘어온 데이터가 현재 노드의 데이터보다 크면
            //현재 노드를 현재 노드의 오른쪽으로 이동합니다.
        }
    }
    return current;
    //현재 노드를 반환합니다.
    //이로써 넘어온 데이터가 현제 데이터보다 작으면 왼쪽 크면 오른쪽으로 이동하는 bst의 탐색을 완료할수 있습니다.
}

//트리에서 최소값을 찾는 함수입니다.
TreeNode* FindMin(TreeNode* node) {
    //넘어오는 매게변수는 노드입니다.
    TreeNode* current = node;
    //현재 노드를 넘어온 노드로 초기화 합니다.
    while (current && current->left != NULL) {
        //현재 노드가 null이 아니고 현재 노드의 왼쪽이 null이 아니면 반복합니다.
        current = current->left;
        //현재 노드를 현재 노드의 왼쪽으로 이동합니다.
    }
    return current;
    //현재 노드를 반환합니다.
    //이로써 넘어온 노드의 왼쪽 노드들 중 최소값을 찾을수 있습니다.
}

//트리에서 노드를 삭제하는 함수입니다.
TreeNode* DeleteNode(TreeNode* root, int data) {
    //넘어오는 매게변수는 루트와 데이터 입니다게
    TreeNode* parent = NULL;
    //부모노드를 먼저 null로 초기화 한후 
    TreeNode* current = root;
    //current=삭제할 노드를 가르킬 용도.
    //현재 노드를 루트로 초기화 합니다.
    while (current != NULL && current->data != data) {
        //반복문:현재 노드가 null이 아니고,현재 노드의 데이터가 넘어온 데이터와 같지않다면(즉 아직 찾지 못했다면)
        parent = current;
        //부모노드를 현재노드로 초기화 합니다.
        if (data < current->data) {
            //넘어온 데이터가 현재 노드의 데이터보다 작다
            current = current->left;
            //bst의 구조상 왼쪽으로 이동 
        } else {
            current = current->right;
            //크다면 오른쪽으로 이동.
        }
    }
    if (current == NULL) return root;
    //현재 노드가 null이면 넘어온 데이터가 트리에 없다는 것이니 루트를 반환합니다.

    if (current->left == NULL || current->right == NULL) {
        //현재 노드의 왼쪽이나 오른쪽이 null이면 자식노드가 하나이하인 경우
        TreeNode* newCurrent;
        //새로운 현재노드를 선언합니다.(대체할 노드를 가리킬 포인터 )
        if (current->left == NULL) {
            //현재 노드의 왼쪽이 null이면 (왼쪽 자식이 없으면 )
            newCurrent = current->right;
            //새로운 현재노드를 현재 노드의 오른쪽으로 초기화 합니다.(오른쪽 자식 선택.)
        } else {
            newCurrent = current->left;
            //현재 노드의 오른쪽이 null이면 (오른쪽 자식이 없으면)
            //새로운 현재노드를 현재 노드의 왼쪽으로 초기화 합니다.(왼쪽 자식 선택 )
        }
        if (parent == NULL) {
            //부모노드가 null이면 현재 노드가 루트노드라는 것이니
            //(즉 삭제할 노드가 루트 노드.)
            free(current);
            //현재 노드를 해제합니다.(메모)
            return newCurrent;
            //새로운 현재노드를 반환합니다.
        }
        //부모노드의 자식포인터를 대체 노드로 업데이트.
        if (current == parent->left) {
           //삭제할 노드가 부모노드의 왼쪽 자식이면  
            parent->left = newCurrent;
            //부모노드의 왼쪽을 대체할 노드로 연결 
        } else {
            parent->right = newCurrent;
            //삭제할 노드가 부모노드의 오른쪽 자식이면
            //부모노드의 오른쪽을 대체할 노드로 연결 
        }
        free(current);//현재 노드를 메모리에서 해제.
    } else {
        //자식노드가 두개인 경우
        TreeNode* p = NULL;
        //대체할 노드의 부모를 추적하기 위한 포인터.
        TreeNode* temp;
        //temp를 null로 초기화 합니다.
        temp = current->right;
        //temp를 이용하여 오른쪽 서브트리에서 가장 작은 노드를 찾습니다.
        while (temp->left != NULL) {
            //오른쪽 서브트리에서 가장 작은 노드를 찾음.
            p = temp;
            //p를 부모노드로 업데이트 
            temp = temp->left;
            //temp를 왼쪽으로 계속이동 
        }
        if (p != NULL) {
            //p가 null이 아니면(대체할 노드에 부모가 존재하는 경우 )
            p->left = temp->right;
            //대체할 노드의 부모의 왼쪽을 대체할 노드의 오른쪽으로 연결 
        } else {
            current->right = temp->right;
            //대체할 노드가 바로 오른쪽 자식인 경우.
        }
        current->data = temp->data;
        //현재 노드의 데이터를 대체할 노드의 데이터로 교체 
        free(temp);
        //temp를 해제합니다. 대체할 노드를 메모리에서 삭제.
    }
    return root;
}

//중위순회 함수 
//중위순회는 왼쪽 자식, 루트, 오른쪽 자식 순으로 방문하는 방위
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

//후위순회 함수 
//후위순회는 왼쪽 자식, 오른쪽 자식, 루트 순으로 방문하는 방위
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

//트리를 출력하는 함수 

// 레벨 순회를 이용한 트리 출력
void LevelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;
    Queue* queue = CreateQueue();
    Enqueue(queue, root);
    int levelNodes = 1; // 현재 레벨의 노드 수

    while (!IsQueueEmpty(queue)) {
        int nextLevelNodes = 0; // 다음 레벨의 노드 수
        while (levelNodes > 0) {
            TreeNode* current = Dequeue(queue);
            printf("%d ", current->data);
            if (current->left != NULL) {
                Enqueue(queue, current->left);
                nextLevelNodes++;
            }
            if (current->right != NULL) {
                Enqueue(queue, current->right);
                nextLevelNodes++;
            }
            levelNodes--;
        }
        printf("\n"); // 레벨이 끝날 때 줄바꿈
        levelNodes = nextLevelNodes; // 다음 레벨로 이동
    }
    FreeQueue(queue);
}

void PrintTree(TreeNode* root, int space) {
    if (root == NULL) return;

    int COUNT = 5;
    space += COUNT;

    PrintTree(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    PrintTree(root->left, space);
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
        printf("\n1. 삽입\n2. 삭제\n3. 검색\n4. 중위 순회\n5. 후위 순회\n6. 트리 출력\n7. 레벨 순회 트리 출력\n8. 종료\n");
        printf("원하는 작업을 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("삽입할 값을 입력하세요: ");
                scanf("%d", &value);
                root = InsertNode(root, value);
                break;
            case 2:
                printf("삭제할 값을 입력하세요: ");
                scanf("%d", &value);
                root = DeleteNode(root, value);
                break;
            case 3:
                printf("검색할 값을 입력하세요: ");
                scanf("%d", &value);
                TreeNode* result = SearchNode(root, value);
                if (result != NULL) {
                    printf("노드를 찾았습니다: %d\n", result->data);
                } else {
                    printf("노드를 찾을 수 없습니다\n");
                }
                break;
            case 4:
                printf("중위 순회 결과: ");
                InOrderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("후위 순회 결과: ");
                PostOrderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("DFS기반 트리 구조 :\n");
                PrintTree(root ,0);  // 레벨 순회로 트리 출력
                printf("\n");
                break;
            case 7:
                printf("레벨 순회 트리 구조 :\n");
                LevelOrderTraversal(root);
                printf("\n");
                break;
            case 8:
                FreeTree(root);
                exit(0);
            default:
                printf("잘못된 선택입니다\n");
        }
    }

    return 0;
}