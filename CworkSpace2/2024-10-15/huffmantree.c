#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
} Node;

// 우선순위 큐(최소 히프) 구조체 정의
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    Node** array;
} MinHeap;

// 새로운 노드 생성
Node* newNode(char data, unsigned freq) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// 최소 히프 생성
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(minHeap->capacity * sizeof(Node*));
    return minHeap;
}

// 두 노드의 빈도를 비교
void swapNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// 히프화
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 최소 히프에서 최소값 추출
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 최소 히프 삽입
void insertMinHeap(MinHeap* minHeap, Node* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// 최소 히프 생성
MinHeap* buildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

// 허프만 트리 생성
Node* buildHuffmanTree(char data[], int freq[], int size) {
    Node *left, *right, *top;
    MinHeap* minHeap = buildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // 결합 과정 출력
        printf("Combining nodes: '%c'(%d) + '%c'(%d)\n", 
               left->data ? left->data : '#', left->freq, 
               right->data ? right->data : '#', right->freq);

        top = newNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// 허프만 코드 출력
void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// 허프만 코드 생성 및 출력
void HuffmanCodes(char data[], int freq[], int size) {
    Node* root = buildHuffmanTree(data, freq, size);
    int arr[100], top = 0;
    printCodes(root, arr, top);
}

int main() {
    char arr[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Huffman Codes:\n");
    HuffmanCodes(arr, freq, size);

    return 0;
}