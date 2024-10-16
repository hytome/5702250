#include <stdio.h>

// 배열 출력 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 힙화 함수
void heapify(int arr[], int n, int i) {
    int largest = i; // 루트를 가장 큰 값으로 설정
    int left = 2 * i + 1; // 왼쪽 자식
    int right = 2 * i + 2; // 오른쪽 자식

    // 왼쪽 자식이 루트보다 크면
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 오른쪽 자식이 현재 가장 큰 값보다 크면
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 가장 큰 값이 루트가 아니면 교환
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // 재귀적으로 힙화
        heapify(arr, n, largest);
    }
}

// 힙 정렬 함수
void heapSort(int arr[], int n) {
    // 힙을 구성
    for (int i = 0; i < n; i++) {
        // 현재까지의 배열을 힙으로 구성
        for (int j = i / 2 - 1; j >= 0; j--) {
            heapify(arr, i + 1, j);
        }
        // 현재 상태 출력
        printArray(arr, i + 1);
    }

    

    // 하나씩 요소를 힙에서 추출
    for (int i = n - 1; i > 0; i--) {
        // 현재 루트를 끝으로 이동
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 감소된 힙에 대해 힙화
        heapify(arr, i, 0);

        // 현재 상태 출력
        printArray(arr, i);
    }
}

int main() {
    int arr[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("<Sort>\n");
    heapSort(arr, n);

    printf("Sorted Array:\n");
    printArray(arr, n);

    return 0;
}