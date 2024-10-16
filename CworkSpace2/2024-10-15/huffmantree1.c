#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체 정의
// 허프만 트리의 각 노드를 나타내는 구조체입니다.
// 각 노드는 문자 데이터와 빈도, 왼쪽 및 오른쪽 자식 노드를 가집니다.
typedef struct Node {
    char* data;  // 노드의 문자 데이터를 저장합니다.
    unsigned freq;  // 노드의 빈도를 저장합니다.
    struct Node *left, *right;  // 왼쪽 및 오른쪽 자식 노드를 가리킵니다.
} Node;

// 우선순위 큐(최소 히프) 구조체 정의
// 허프만 트리 생성을 위한 최소 히프를 나타내는 구조체입니다.
// 히프는 노드 배열과 크기, 용량을 가집니다.
typedef struct MinHeap {
    unsigned size;  // 현재 히프의 크기를 나타냅니다.
    unsigned capacity;  // 히프의 최대 용량을 나타냅니다.
    Node** array;  // 노드 포인터 배열로 히프를 구현합니다.
} MinHeap;

// 새로운 노드 생성
// 주어진 문자 데이터와 빈도로 새로운 노드를 생성합니다.
Node* newNode(char* data, unsigned freq) {
    Node* temp = (Node*)malloc(sizeof(Node));  // 새로운 노드를 위한 메모리를 할당합니다.
    temp->left = temp->right = NULL;  // 초기에는 자식 노드가 없으므로 NULL로 설정합니다.
    temp->data = strdup(data);  // 문자열 데이터를 복사하여 저장합니다.
    temp->freq = freq;  // 노드의 빈도를 설정합니다.
    return temp;  // 생성된 노드를 반환합니다.
}

// 최소 히프 생성
// 주어진 용량으로 최소 히프를 생성합니다.
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));  // 히프 구조체를 위한 메모리를 할당합니다.
    minHeap->size = 0;  // 초기 히프의 크기를 0으로 설정합니다.
    minHeap->capacity = capacity;  // 히프의 최대 용량을 설정합니다.
    minHeap->array = (Node**)malloc(minHeap->capacity * sizeof(Node*));  // 노드 포인터 배열을 위한 메모리를 할당합니다.
    return minHeap;  // 생성된 히프를 반환합니다.
}

// 두 노드의 빈도를 비교
// 두 노드의 포인터를 교환하여 히프 속성을 유지합니다.
void swapNode(Node** a, Node** b) {
    Node* t = *a;  // 임시 포인터에 첫 번째 노드를 저장합니다.
    *a = *b;  // 첫 번째 노드에 두 번째 노드를 저장합니다.
    *b = t;  // 두 번째 노드에 임시 포인터의 노드를 저장합니다.
}

// 히프화
// 주어진 인덱스에서 히프 속성을 유지하도록 노드를 재배치합니다.
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;  // 현재 인덱스를 가장 작은 값으로 설정합니다.
    int left = 2 * idx + 1;  // 왼쪽 자식 노드의 인덱스를 계산합니다.
    int right = 2 * idx + 2;  // 오른쪽 자식 노드의 인덱스를 계산합니다.

    // 왼쪽 자식 노드가 존재하고, 빈도가 더 작으면 가장 작은 값으로 설정합니다.
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    // 오른쪽 자식 노드가 존재하고, 빈도가 더 작으면 가장 작은 값으로 설정합니다.
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    // 가장 작은 값이 현재 인덱스가 아니면 노드를 교환하고 재귀적으로 히프화합니다.
    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 최소 히프에서 최소값 추출
// 히프의 루트 노드를 추출하고 히프 속성을 유지합니다.
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];  // 루트 노드를 임시 포인터에 저장합니다.
    minHeap->array[0] = minHeap->array[minHeap->size - 1];  // 마지막 노드를 루트로 이동합니다.
    --minHeap->size;  // 히프의 크기를 줄입니다.
    minHeapify(minHeap, 0);  // 루트에서 히프화를 수행합니다.
    return temp;  // 추출된 노드를 반환합니다.
}

// 최소 히프 삽입
// 새로운 노드를 히프에 삽입하고 히프 속성을 유지합니다.
void insertMinHeap(MinHeap* minHeap, Node* node) {
    ++minHeap->size;  // 히프의 크기를 증가시킵니다.
    int i = minHeap->size - 1;  // 새로운 노드를 삽입할 위치를 설정합니다.
    // 부모 노드와 비교하여 히프 속성을 만족할 때까지 위로 이동합니다.
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];  // 부모 노드를 아래로 이동합니다.
        i = (i - 1) / 2;  // 부모 노드의 인덱스로 이동합니다.
    }
    minHeap->array[i] = node;  // 최종 위치에 노드를 삽입합니다.
}

// 최소 히프 생성
// 주어진 문자와 빈도로 최소 히프를 생성합니다.
MinHeap* buildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);  // 주어진 크기로 히프를 생성합니다.
    for (int i = 0; i < size; ++i) {
        char str[2] = {data[i], '\0'};  // 문자에서 문자열로 변환합니다.
        minHeap->array[i] = newNode(str, freq[i]);  // 각 문자를 노드로 생성하여 히프에 삽입합니다.
    }
    minHeap->size = size;  // 히프의 크기를 설정합니다.
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);  // 히프 속성을 유지하도록 히프화를 수행합니다.
    return minHeap;  // 생성된 히프를 반환합니다.
}

// 허프만 트리 생성
// 주어진 문자와 빈도로 허프만 트리를 생성합니다.
Node* buildHuffmanTree(char data[], int freq[], int size) {
    Node *left, *right, *top;  // 왼쪽, 오른쪽, 상위 노드를 위한 포인터를 선언합니다.
    MinHeap* minHeap = buildMinHeap(data, freq, size);  // 최소 히프를 생성합니다.

    // 히프에 노드가 하나만 남을 때까지 반복합니다.
    while (minHeap->size != 1) {
        left = extractMin(minHeap);  // 가장 작은 두 노드를 추출합니다.
        right = extractMin(minHeap);

        // 결합 과정 출력
        printf("노드의 빈도 합산: '%s'(%d) + '%s'(%d)\n", left->data, left->freq, right->data, right->freq);

        // 새로운 노드의 데이터 결합
        char* combinedData = (char*)malloc(strlen(left->data) + strlen(right->data) + 1);
        strcpy(combinedData, left->data);
        strcat(combinedData, right->data);

        top = newNode(combinedData, left->freq + right->freq);  // 새로운 노드를 생성합니다.
        free(combinedData);  // 임시 문자열 해제
        top->left = left;  // 왼쪽 자식 노드를 설정합니다.
        top->right = right;  // 오른쪽 자식 노드를 설정합니다.
        insertMinHeap(minHeap, top);  // 새로운 노드를 히프에 삽입합니다.
    }

    Node* root = extractMin(minHeap); // 루트에 최종 트리 노드 저장
    free(minHeap->array);// 히프 배열 해제
    free(minHeap);// 히프 구조체 해제
    return root; // 최종 허프만 트리의 루트를 반환합니다.
}

// 허프만 코드 출력
// 허프만 트리의 각 문자에 대한 허프만 코드를 출력합니다.
void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;  // 왼쪽으로 이동할 때 1을 할당합니다.
        printCodes(root->left, arr, top + 1);  // 왼쪽 자식 노드로 재귀 호출합니다.
    }
    if (root->right) {
        arr[top] = 0;  // 오른쪽으로 이동할 때 0을 할당합니다.
        printCodes(root->right, arr, top + 1);  // 오른쪽 자식 노드로 재귀 호출합니다.
    }
    if (!(root->left) && !(root->right)) {
        printf("%s: ", root->data);  // 리프 노드의 데이터를 출력합니다.
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);  // 경로를 따라 할당된 코드를 출력합니다.
        printf("\n");
    }
}

void freeNode(Node* node) {
    if (node==NULL) return;
    freeNode(node->left);
    freeNode(node->right);
    free(node->data);
    free(node);
}
// 허프만 코드 생성 및 출력
// 주어진 문자와 빈도로 허프만 코드를 생성하고 출력합니다.
void HuffmanCodes(char data[], int freq[], int size) {
    Node* root = buildHuffmanTree(data, freq, size);  // 허프만 트리를 생성합니다.
    int arr[100], top = 0;  // 코드 저장을 위한 배열과 인덱스를 초기화합니다.
    printCodes(root, arr, top);  // 허프만 코드를 출력합니다.
    freeNode(root);
}

int main() {
    char arr[] = {'A', 'E', 'I', 'O', 'U', 'S','T'};  // 입력 문자 배열
    int freq[] = {10, 15, 12, 3, 4, 13, 1 };  // 각 문자의 빈도 배열
    int size = sizeof(arr) / sizeof(arr[0]);  // 배열의 크기를 계산합니다.

    printf("왼쪽과 오른쪽의 트리로 구분지어서 완성한 허프만 비트코드:\n");
    HuffmanCodes(arr, freq, size);  // 허프만 코드를 생성하고 출력합니다.

    return 0;  // 프로그램을 종료합니다.
}