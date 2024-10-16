#include <stdio.h>

// 두 정수 포인터의 값을 교환
// 두 정수 포인터가 가리키는 값을 교환합니다.
void swp(int *a, int *b) {
    int tmp = *a;  // 첫 번째 정수의 값을 임시 변수에 저장합니다.
    *a = *b;  // 첫 번째 정수에 두 번째 정수의 값을 저장합니다.
    *b = tmp;  // 두 번째 정수에 임시 변수의 값을 저장합니다.
}

// 힙의 현재 상태를 출력
// 힙 배열의 모든 요소를 출력합니다.
void prtHp(int data[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);  // 각 요소를 출력합니다.
    }
    printf("\n");  // 줄바꿈을 추가합니다. 
    //각 요소를 보기 좋게 출력하는 용도입니다.
}

// 힙화
// 주어진 인덱스에서 힙 속성을 유지하도록 배열을 재배치합니다.
void hpy(int data[], int n, int i) { //이 프로그램은 최대 히프를 사용합니다.
    int lgst = i;  // 현재 인덱스를 가장 큰 값으로 설정합니다.
    int lft = 2 * i + 1;  // 왼쪽 자식 노드의 인덱스를 계산합니다.
    int rgt = 2 * i + 2;  // 오른쪽 자식 노드의 인덱스를 계산합니다.

    // 왼쪽 자식 노드가 존재하고, 값이 더 크면 가장 큰 값으로 설정합니다.
    if (lft < n && data[lft] > data[lgst])
        lgst = lft;

    // 오른쪽 자식 노드가 존재하고, 값이 더 크면 가장 큰 값으로 설정합니다.
    if (rgt < n && data[rgt] > data[lgst])
        lgst = rgt;

    // 가장 큰 값이 현재 인덱스가 아니면 노드를 교환하고 재귀적으로 힙화합니다.
    if (lgst != i) {
        swp(&data[i], &data[lgst]);
        hpy(data, n, lgst);
    }
}

// 힙에 요소 삽입
// 새로운 요소를 힙에 삽입하고 힙 속성을 유지합니다.
void insHp(int data[], int n) {
    int i = n - 1;  // 새로운 요소의 인덱스를 설정합니다.
    // 부모 노드와 비교하여 힙 속성을 만족할 때까지 위로 이동합니다.
    while (i != 0 && data[(i - 1) / 2] < data[i]) {
        swp(&data[i], &data[(i - 1) / 2]);  // 부모 노드와 교환합니다.
        i = (i - 1) / 2;  // 부모 노드의 인덱스로 이동합니다.
    }
}

// 힙 정렬
// 힙을 정렬하여 배열을 오름차순으로 만듭니다.
void hpSrt(int data[], int n) {
    for (int i = n - 1; i > 0; i--) {
        swp(&data[0], &data[i]);  // 루트와 마지막 요소를 교환합니다.
        prtHp(data, i);  // 교환 후 힙의 상태를 출력합니다.
        hpy(data, i, 0);  // 루트에서 힙화를 수행합니다.
    }
}

int main() {
    int inputData[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86};  // 입력 데이터 배열
    int size = sizeof(inputData) / sizeof(inputData[0]);  // 배열의 크기를 계산합니다.
    int heap[size];  // 힙 배열을 선언합니다.
    int heapSize = 0;  // 힙의 초기 크기를 0으로 설정합니다.

    printf("<Sort>\n");

    // 입력 데이터를 힙에 삽입하고 상태를 출력합니다.
    for (int i = 0; i < size; i++) {
        heap[heapSize] = inputData[i];  // 데이터를 힙에 삽입합니다.
        heapSize++;  // 힙의 크기를 증가시킵니다.
        insHp(heap, heapSize);  // 힙 속성을 유지합니다.
        prtHp(heap, heapSize);  // 힙의 현재 상태를 출력합니다.
    }

    hpSrt(heap, heapSize);  // 힙 정렬을 수행합니다.

    printf("\nSorted Array:\n");
    for (int i = 0; i < heapSize; i++) {
        printf("%d ", heap[i]);  // 정렬된 배열을 출력합니다.
    }
    printf("\n");

    return 0;  // 프로그램을 종료합니다.
}