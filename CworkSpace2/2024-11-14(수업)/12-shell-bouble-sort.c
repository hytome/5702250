#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define TRIALS 20

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

// 선택 정렬 (Selection Sort)
void doSelectionSort(int array[]) {
    int i, j, minIdx, temp;
    for (i = 0; i < SIZE - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < SIZE; j++) {
            if (array[j] < array[minIdx]) {
                minIdx = j;
            }
        }
        // Swap
        temp = array[i];
        array[i] = array[minIdx];
        array[minIdx] = temp;

        // 정렬 과정 출력: 10부터 20단위 및 마지막 단계 출력
        if ((i + 1) == 10 || ((i + 1) > 10 && ((i + 1) - 10) % 20 == 0) || i == SIZE - 2) {
            printf("Selection Sort Step %d:\n", i + 1);
            printArray(array);
            printf("\n");
        }
    }
}

// 쉘 정렬 (Shell Sort)
void doShellSort(int array[]) {
    for (int gap = SIZE / 2; gap > 0; gap /= 2) { // 간격을 줄여가며 반복
        for (int i = gap; i < SIZE; i++) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }

        // 정렬 과정 출력: 간격마다 배열 상태를 출력
        printf("Shell Sort with Gap %d:\n", gap);
        printArray(array);
        printf("\n");
    }
}

// 버블 정렬 (Bubble Sort)
void doBubbleSort(int array[]) {
    int temp;
    for (int i = 0; i < SIZE - 1; i++) {
        int swapped = 0; // 스왑이 일어났는지 확인
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Swap
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = 1;
            }
        }

        // 정렬 과정 출력: 10단위로 출력
        if ((i + 1) == 10 || ((i + 1) > 10 && ((i + 1) - 10) % 10 == 0) || i == SIZE - 2) {
            printf("Bubble Sort Step %d:\n", i + 1);
            printArray(array);
            printf("\n");
        }

        // 만약 스왑이 일어나지 않았다면 정렬 완료된 상태
        if (!swapped) break;
    }
}

int main() {
    int array[SIZE];
    srand(time(0));

    // 난수 데이터 생성
    generateRandomData(array);
    printf("Original Array:\n");
    printArray(array);

    // 버블 정렬 수행
    int bubbleArray[SIZE];
    for (int i = 0; i < SIZE; i++) bubbleArray[i] = array[i];
    doBubbleSort(bubbleArray);
    printf("Array after Bubble Sort:\n");
    printArray(bubbleArray);

    // 선택 정렬 수행
    int selectionArray[SIZE];
    for (int i = 0; i < SIZE; i++) selectionArray[i] = array[i];
    doSelectionSort(selectionArray);
    printf("Array after Selection Sort:\n");
    printArray(selectionArray);

    // 쉘 정렬 수행
    int shellArray[SIZE];
    for (int i = 0; i < SIZE; i++) shellArray[i] = array[i];
    doShellSort(shellArray);
    printf("Array after Shell Sort:\n");
    printArray(shellArray);

    return 0;
}
