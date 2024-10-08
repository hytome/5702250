//스레드 이진트리는 기존 이진트리에서 선행자와 후속자를 가리키는 포인터를 추가한다.
//이렇게 추가된 선행자와 후속자로,메모리의 사용을 줄이고 성능개선,특히 스택이나 재귀를 사용하지 않고 순회할수 있게 한다.
//이러한 스레드 이진 트리를 이용하여 삽입한 트리를 스레드 이진 트리로 중위 순회 해보자.

#include <stdio.h>
#include <stdlib.h>

// 일반 이진 트리 노드 구조체
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// 쓰레드 이진 트리 노드 구조체
typedef struct ThreadNode {
    int data;
    struct ThreadNode *left, *right;
    int lthread, rthread; 

} ThreadNode;

// 일반 이진 트리에 노드 삽입
TreeNode* InsertBinaryTree(TreeNode* root, int data) {
    
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (data < root->data) {
        root->left = InsertBinaryTree(root->left, data);
    } else {
        root->right = InsertBinaryTree(root->right, data);
    }
    return root;
}

// 쓰레드 이진 트리에 노드 삽입
ThreadNode* InsertThreadTree_Node(ThreadNode* root, int data) {
    //넘어오는 매게변수는 루트 노드와 데이터(inputData[i])
    if (root == NULL) {
        //트리가 비어있다면 
        ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
        //새로운 노드 생성.
        newNode->data = data;
        //데이터 삽입
        newNode->left = newNode->right = NULL;
        //왼쪽 오른쪽 포인터 초기화
        newNode->lthread = newNode->rthread = 1;
        //스레드 플래그 초기화 (1일 경우에 스레드니까.)
        return newNode;
    }
    if (data < root->data) {
        //삽입할 data가 현재 노드의 데이터 보다 작다면.
       if (root->lthread == 0) {
            //스레드가 0이면 자식 노드가 있다는 뜻이니까.
            root->left = InsertThreadTree_Node(root->left, data);
            //(재귀 호출)왼쪽 자식으로 이동하여 서브트리에 대한 삽입 작업 수행.
        } else {
            //스레드가 1이면 자식 노드가 없다는 뜻이니까.
            ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
            //새로운 노드 생성
            newNode->data = data;
            newNode->left = root->left;
            //새 노드의 left는 현재 노드의 left를 가르키게 된다. -선행자를 가르킴
            newNode->right = root;
            //새 노드의 right는 현재 노드를 가르키게 된다.-후속자를 가르킴
            //-이렇게 중위 순회에서 선행자와 후속자를 설정하는것.
            newNode->lthread = newNode->rthread = 1;
            //스레드 플래그 초기화
            root->lthread = 0;
            //이제 현재 노드의 왼쪽 스레드 플래그를 0으로 설정하여 자식 노드가 있음을 표시 하고.
            root->left = newNode;
            //현재 노드의 left를 새로운 노드로 설정.
        }
    } else {//오른쪽 삽입 파트.
        if (root->rthread == 0) {
            //스레드가 0이면 자식 노드가 있다는 뜻이니까.
            root->right = InsertThreadTree_Node(root->right, data);
            //(재귀 호출)오른쪽 자식으로 이동하여 서브트리에 대한 삽입 작업 수행.
        } else {
            //스레드가 1이면 자식 노드가 없다는 뜻이니까.
            ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
            //새로운 노드 생성
            newNode->data = data;
            newNode->right = root->right;
            //새 노드의 right는 현재 노드의 right를 가르키게 된다.-후속자를 가르킴 
            newNode->left = root;
            //새 노드의 left는 현재 노드를 가르키게 된다.-선행자를 가르킴.
            //-이렇게 중위 순회에서 선행자와 후속자를 설정하는것.
            newNode->lthread = newNode->rthread = 1;
            //스레드 플래그 초기화
            root->rthread = 0;
            //현재 노드의 오른쪽 스레드 플래그를 0으로 설정하여 자식 노드가 있음을 표시
            root->right = newNode;
            //현재 노드의 right를 새로운 노드로 설정.
        }
    }
    return root;
}

// 일반 이진 트리 생성
TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = InsertBinaryTree(root, inputData[i]);
    }
    return root;
}

// 쓰레드 이진 트리 생성
ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = InsertThreadTree_Node(root, inputData[i]);
    }
    return root;
}

// 일반 이진 트리 중위 순회
void BinaryTreeInOrder(TreeNode* root) {
    if (root == NULL) return;
    BinaryTreeInOrder(root->left);
    printf("%d ", root->data);
    BinaryTreeInOrder(root->right);
}

// 쓰레드 이진 트리 중위 순회
//중위순회에서 쓰레드 이진트리는 선행자와 후속자를 가르킬수 있습니다.
//선행자: 현재 노드 이전에 방문한 노드.
//후속자: 현재 노드 이후에 방문할 노드.
void ThreadTreeInOrder(ThreadNode* root) {
    if (root == NULL) return;

    ThreadNode* ptr = root;
    //시작-먼저 가장 왼쪽 노드로 이동해야함.
    while (ptr->lthread == 0) {
        //왼쪽 스레드가 0일 동안 왼쪽 자식으로 계속 이동.
        ptr = ptr->left;
    }

    while (ptr != NULL) {
        printf("%d ", ptr->data);
        //현재 노드의 데이터를 출력.
        //중위 순회는 왼쪽 자식 현재 오른쪽 자식 순으로 방문.
        if (ptr->rthread == 1) {
            //스레드가 1인 경우. 이는 중위 순회에서 후속자를 가르킨다.
            //즉 후속자가 스레드인 경우 
            //따라서 ptr을 right로 이동하여 다음 노드로 이동.
            ptr = ptr->right;
        } else {
            //오른쪽 자식이 있는경우 
            ptr = ptr->right;
            //오른쪽 자식으로 이동한후 
            while (ptr != NULL && ptr->lthread == 0) {
                ptr = ptr->left;
                //그 서브트리의 또 가장 왼쪽 노드까지 이동. 이를 이용하여 중위 순회.
            }
        }
    }
}

int main() {
    int inputData[] = {4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11};
    int size = sizeof(inputData) / sizeof(inputData[0]);
    // 입력한 데이터 값을 먼저 확인. 순회가 이루어져야 하니까.
    printf("inputData: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    // 트리 생성
    TreeNode *root = GenerateBinaryTree(inputData, size);
    printf("BinaryTreeInOrder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode *troot = GenerateThreadTree(inputData, size);
    printf("ThreadTreeInOrder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    free(troot);
    return 0;
}