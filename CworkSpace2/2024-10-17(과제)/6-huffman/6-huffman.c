#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
// 허프만 트리의 각 노드를 나타내는 구조체입니다.
// 각 노드는 문자 데이터와 빈도, 왼쪽 및 오른쪽 자식 노드를 가집니다.
typedef struct Node { 
    char character;  // 노드의 문자 데이터를 저장합니다.
    int frequency;  // 노드의 빈도를 저장합니다.
    struct Node *left, *right;  // 왼쪽 및 오른쪽 자식 노드를 가리킵니다.
} Node;

// 우선순위 큐(최소 히프) 구조체 정의
// 허프만 트리 생성을 위한 최소 히프를 나타내는 구조체입니다.
// 히프는 노드 배열과 크기, 용량을 가집니다.
typedef struct MinHeap { //빈도 수가 적은 합을 구하여 노드를 구성하기 위해 최소 히프가 쓰입니다.
    int size;  // 현재 히프의 크기를 나타냅니다.
    int capacity;  // 히프의 최대 용량을 나타냅니다.
    Node** array;  // 노드 포인터 배열로 히프를 구현합니다.
} MinHeap;

// 새로운 노드 생성
// 주어진 문자 데이터와 빈도로 새로운 노드를 생성합니다.
Node* mkNode(char character, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));  // 새로운 노드를 위한 메모리를 할당합니다.
    node->character = character;  // 노드의 문자 데이터를 설정합니다.
    node->frequency = frequency;  // 노드의 빈도를 설정합니다.
    node->left = node->right = NULL;  // 초기에는 자식 노드가 없으므로 NULL로 설정합니다.
    return node;  // 생성된 노드를 반환합니다.
}

// 최소 히프 생성
// 주어진 용량으로 최소 히프를 생성합니다.
MinHeap* mkMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));  // 히프 구조체를 위한 메모리를 할당합니다.
    minHeap->size = 0;  // 초기 히프의 크기를 0으로 설정합니다.
    minHeap->capacity = capacity;  // 히프의 최대 용량을 설정합니다.
    minHeap->array = (Node**)malloc(minHeap->capacity * sizeof(Node*));  // 노드 포인터 배열을 위한 메모리를 할당합니다.
    return minHeap;  // 생성된 히프를 반환합니다.
}

// 두 노드의 포인터를 교환
// 두 노드의 포인터를 교환하여 히프 속성을 유지합니다.
void swapN(Node** a, Node** b) {
    Node* temp = *a;  // 임시 포인터에 첫 번째 노드를 저장합니다.
    *a = *b;  // 첫 번째 노드에 두 번째 노드를 저장합니다.
    *b = temp;  // 두 번째 노드에 임시 포인터의 노드를 저장합니다.
}

// 히프화
// 주어진 인덱스에서 히프 속성을 유지하도록 노드를 재배치합니다.
void hfy(MinHeap* minHeap, int idx) {
    int smallest = idx;  // 현재 인덱스를 가장 작은 값으로 설정합니다.
    int left = 2 * idx + 1;  // 왼쪽 자식 노드의 인덱스를 계산합니다.
    int right = 2 * idx + 2;  // 오른쪽 자식 노드의 인덱스를 계산합니다.

    // 왼쪽 자식 노드가 존재하고, 빈도가 더 작으면 가장 작은 값으로 설정합니다.
    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    // 오른쪽 자식 노드가 존재하고, 빈도가 더 작으면 가장 작은 값으로 설정합니다.
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    // 가장 작은 값이 현재 인덱스가 아니면 노드를 교환하고 재귀적으로 히프화합니다.
    if (smallest != idx) {
        swapN(&minHeap->array[smallest], &minHeap->array[idx]);
        hfy(minHeap, smallest);
    }
}

// 최소 히프에서 최소값 추출
// 히프의 루트 노드를 추출하고 히프 속성을 유지합니다.
Node* extMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];  // 루트 노드를 임시 포인터에 저장합니다.
    minHeap->array[0] = minHeap->array[minHeap->size - 1];  // 마지막 노드를 루트로 이동합니다.
    minHeap->size--;  // 히프의 크기를 줄입니다.
    hfy(minHeap, 0);  // 루트에서 히프화를 수행합니다.
    return temp;  // 추출된 노드를 반환합니다.
}

// 히프의 현재 상태를 출력
// 히프의 각 노드의 빈도를 출력합니다.
void prtHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]->frequency);  // 각 노드의 빈도를 출력합니다.
    }
    printf("\n");  // 줄바꿈을 추가합니다.
}

// 히프 삽입 후 상태 출력
// 새로운 노드를 히프에 삽입하고 히프의 상태를 출력합니다.
void insMinHeapAndPrt(MinHeap* minHeap, Node* node) {
    minHeap->size++;  // 히프의 크기를 증가시킵니다.
    int i = minHeap->size - 1;  // 새로운 노드를 삽입할 위치를 설정합니다.
    // 부모 노드와 비교하여 히프 속성을 만족할 때까지 위로 이동합니다.
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];  // 부모 노드를 아래로 이동합니다.
        i = (i - 1) / 2;  // 부모 노드의 인덱스로 이동합니다.
    }
    minHeap->array[i] = node;  // 최종 위치에 노드를 삽입합니다.

    // 삽입 후 히프 상태 출력
    prtHeap(minHeap);  // 히프의 현재 상태를 출력합니다.
}

// 빈도를 기반으로 최소 히프를 생성하고 단계별로 출력
// 주어진 문자와 빈도로 최소 히프를 생성하고 각 단계에서 히프의 상태를 출력합니다.
MinHeap* bldMinHeapWithPrt(char characters[], int frequencies[], int size) {
    MinHeap* minHeap = mkMinHeap(size);  // 주어진 크기로 히프를 생성합니다.
    for (int i = 0; i < size; i++) {
        insMinHeapAndPrt(minHeap, mkNode(characters[i], frequencies[i]));  // 각 문자를 노드로 생성하여 히프에 삽입합니다.
    }
    return minHeap;  // 생성된 히프를 반환합니다.
}

// 허프만 트리 생성
// 주어진 문자와 빈도로 허프만 트리를 생성합니다.
Node* bldHuffmanTree(char characters[], int frequencies[], int size) {
    Node *left, *right, *top;  // 왼쪽, 오른쪽, 상위 노드를 위한 포인터를 선언합니다.
    MinHeap* minHeap = bldMinHeapWithPrt(characters, frequencies, size);  // 최소 히프를 생성합니다.

    // 히프에 노드가 하나만 남을 때까지 반복합니다.
    while (minHeap->size != 1) {
        left = extMin(minHeap);  // 가장 작은 두 노드를 추출합니다.
        right = extMin(minHeap);

        // 새로운 노드의 데이터 결합
        top = mkNode('$', left->frequency + right->frequency);  // 새로운 노드를 생성합니다. 특수 문자로 내부 노드 표시
        top->left = left;  // 왼쪽 자식 노드를 설정합니다.
        top->right = right;  // 오른쪽 자식 노드를 설정합니다.
        insMinHeapAndPrt(minHeap, top);  // 새로운 노드를 히프에 삽입합니다.

        // 병합 과정 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);  // 병합 과정을 출력합니다.
    }

    return extMin(minHeap);  // 최종 허프만 트리의 루트를 반환합니다.
}

// 허프만 코드 출력
// 허프만 트리의 각 문자에 대한 허프만 코드를 출력합니다.
void prtCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;  // 왼쪽으로 이동할 때 1을 할당합니다.
        //물론 일반적으로 히프만 트리에서는 왼쪽 으로 이동할때 0 입니다.
        prtCodes(root->left, arr, top + 1);  // 왼쪽 자식 노드로 재귀 호출합니다.
    }
    if (root->right) {
        arr[top] = 0;  // 오른쪽으로 이동할 때 0을 할당합니다.
        //물론 일반적으로 히프만 트리에서는 오른쪽 으로 이동할때 1 입니다.
        prtCodes(root->right, arr, top + 1);  // 오른쪽 자식 노드로 재귀 호출합니다.
    }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->character);  // 리프 노드의 데이터를 출력합니다.
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);  // 경로를 따라 할당된 코드를 출력합니다.
        printf("\n");
    }
}

// 허프만 코드 생성 및 출력
// 주어진 문자와 빈도로 허프만 코드를 생성하고 출력합니다.
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = bldHuffmanTree(characters, frequencies, size);  // 허프만 트리를 생성합니다.
    int arr[100], top = 0;  // 코드 저장을 위한 배열과 인덱스를 초기화합니다.
    prtCodes(root, arr, top);  // 허프만 코드를 출력합니다.
}

int main() {
    char characters[] = {'a', 'e', 'i', 'o', 'u', 's', 't'};  // 입력 문자 배열
    int frequencies[] = {10, 15, 12, 3, 4, 13, 1};  // 각 문자의 빈도 배열
    int size = sizeof(characters) / sizeof(characters[0]);  // 배열의 크기를 계산합니다.

    printf("<Sort>\n");
    GenerateHuffmanCodes(characters, frequencies, size);  // 허프만 코드를 생성하고 출력합니다.

    return 0;  // 프로그램을 종료합니다.
}