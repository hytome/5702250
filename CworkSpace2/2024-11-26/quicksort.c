#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// 함수 선언
void quickSort(int array[], int low, int high);
int partition(int array[], int low, int high);

// 랜덤 데이터 생성 함수
void generateRandomData(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 배열 출력 함수
void printArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 퀵 정렬 (Quick Sort) 함수
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

// 파티션 함수
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

int main() {
    int array[SIZE];
    srand(time(0));

    // 난수 데이터 생성
    generateRandomData(array);
    printf("Original Array:\n");
    printArray(array);
    printf("\n");

    // 퀵 정렬 수행
    quickSort(array, 0, SIZE - 1);
    printf("Array after Quick Sort:\n");
    printArray(array);

    return 0;
}