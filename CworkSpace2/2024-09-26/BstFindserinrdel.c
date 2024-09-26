#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* CreateNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
//InsertNode의 작동방식.
//노드를 삽입하는 함수 기능입니다.  
TreeNode* InsertNode(TreeNode* root, int data) {
    if (root == NULL) {
        //root가 null이면 새로운 노드를 생성하고 반환.
        return CreateNode(data);
        //즉 처음 입력한 값이 루트 노드가 되는 것입니다.
    }
    if (data < root->data) {
        //이제 루트노드와 이후의 데이터를 비교합니다.
        //현재 노드의 값보다 만약 작다면,
        root->left = InsertNode(root->left, data);
        //왼쪽 자식 노드에 새로운 노드를 삽입하고 반환합니다. 
    } else if (data > root->data) {
        root->right = InsertNode(root->right, data);
        //현재 노드의 값보다 크다면 오른쪽 자식 노드에 새로운 노드를 삽입하고 반환합니다. 
    }
    return root;
}

//SerchNode의 작동방식 
TreeNode* SearchNode(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        //root가 null이거나 현재 노드의 값과 찾는 값이 같다면 현재 노드를 반환합니다.
        return root;
    }
    if (data < root->data) {
        return SearchNode(root->left, data);
        //찾는 값이 현재 노드의 값보다 작다면 (중위순회니까) 왼쪽 자식 노드에서 재귀적으로 탐색합니다.
    } else {
        return SearchNode(root->right, data);
        //찾는 값이 현재 노드의 값보다 크다면 (중위순회니까) 오른쪽 자식 노드에서 재귀적으로 탐색합니다.
    }
}
//FindMin의 작동방식
TreeNode* FindMin(TreeNode* node) {
    while (node->left != NULL) node = node->left;
    //왼쪽 자식 노드가 null이 아니면 계속 왼쪽으로 이동합니다.
    return node;
    //최소값을 가진 노드를 반환합니다.
}

TreeNode* DeleteNode(TreeNode* root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        //찾는값이 현재 노드의 값보다 작다면 왼쪽 자식 노드에서 재귀적으로 탐색하고 삭제합니다삭
        root->left = DeleteNode(root->left, data);
        
    } else if (data > root->data) {
        root->right = DeleteNode(root->right, data);
        //찾는값이 현재 노드의 값보다 크다면 오른쪽 자식 노드에서 재귀적으로 탐색하고 삭제합니다.
    } else {
        // Case 1: No child -만약 자식노드가 없는 경우.
        if (root->left == NULL && root->right == NULL) {
            //메모리를 해제하고 루트를 null로 설정합니다.
            free(root);
            root = NULL;
        }
        // Case 2: One child
        else if (root->left == NULL) {
            //왼쪽 자식 노드가 없는 경우
            TreeNode* temp = root;
            //오른쪽 자식 노드를 임시로 저장합니다.
            root = root->right;
            //오른쪽 자식 노드를 루트로 설정합니다.
            free(temp);
            //임시 노드를 해제합니다.
        } else if (root->right == NULL) {
            //오른쪽 자식 노드가 없는 경우
            TreeNode* temp = root;  
            //루트를 임시로 저장합니다.
            root = root->left;
            //왼쪽 자식 노드를 루트로 설정합니다.
            free(temp);
            //임시 노드를 해제합니다.
        }
        // Case 3: Two children - 자식노드가 두개인 경우
        else {
            TreeNode* temp = FindMin(root->right);
            //오른쪽 자식 노드에서 최소값을 가진 노드를 찾습니다.
            root->data = temp->data;
            //루트의 값을 최소값을 가진 노드의 값으로 설정합니다.
            root->right = DeleteNode(root->right, temp->data);
            //최소값을 가진 노드를 삭제합니다.
        }
    }
    return root;
}

//InOrderTraversal의 작동방식 중위순회
void InOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        InOrderTraversal(root->left);
        //재귀적으로 왼쪽 자식 노드를 먼저 방문하고 
        printf("%d ", root->data);
        //현재 노드의 값을 출력합니다.(즉 루트)
        InOrderTraversal(root->right);
        //재귀적으로 오른쪽 자식 노드를 방문합니다.
    }
}

//PostOrderTraversal의 작동방식 후위순회
void PostOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        PostOrderTraversal(root->left);
        //재귀적으로 왼쪽 자식 노드를 먼저 방문하고
        PostOrderTraversal(root->right);
        //재귀적으로 오른쪽 자식 노드를 방문하트
        printf("%d ", root->data);
        //현재 노드의 값을 출력합니다.(즉 루트)
    }
}

void PrintTree(TreeNode* root, int space) {
    if (root == NULL) return;

    space += 10;
    PrintTree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) printf(" ");
    printf("%d\n", root->data);
    PrintTree(root->left, space);
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
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}