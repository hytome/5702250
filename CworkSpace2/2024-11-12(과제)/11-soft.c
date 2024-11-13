#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define TRIALS 20

// 랜덤 데이터 생성 함수
void generateRandomData(int array[]) {
    srand(time(NULL));
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

        // 정렬 과정 출력: 10, 30, 50, 70 단위 및 마지막 단계 출력
        if ((i + 1) == 10 || (i + 1) == 30 || (i + 1) == 50 || (i + 1) == 70 || i == SIZE - 2) {
            printf("Selection Sort Step %d:\n", i + 1);
            printArray(array);
        }
    }
    printf("Selection Sort Final Result:\n");
    printArray(array);
}

// 삽입 정렬 (Insertion Sort)
void doInsertionSort(int array[]) {
    int i, j, key;
    int totalComparisons = 0;

    for (i = 1; i < SIZE; i++) {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
            totalComparisons++;
        }
        array[j + 1] = key;
    }

    printf("Insertion Sort - Average Comparisons: %d\n", totalComparisons / SIZE);
    printf("Insertion Sort Final Result:\n");
    printArray(array);
}

// 버블 정렬 (Bubble Sort)
void doBubbleSort(int array[]) {
    int i, j, temp;
    int totalMoves = 0;

    for (i = 0; i < SIZE - 1; i++) {
        for (j = 0; j < SIZE - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Swap
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                totalMoves += 3; // 이동 횟수는 스왑마다 3으로 계산
            }
        }
    }

    printf("Bubble Sort - Average Moves: %d\n", totalMoves / SIZE);
    printf("Bubble Sort Final Result:\n");
    printArray(array);
}

int main() {
    int randomData[SIZE];

    // 선택 정렬
    generateRandomData(randomData);
    printf("Starting Selection Sort...\n");
    doSelectionSort(randomData);

    // 데이터 재생성 후 삽입 정렬
    generateRandomData(randomData);
    printf("\nStarting Insertion Sort...\n");
    doInsertionSort(randomData);

    // 데이터 재생성 후 버블 정렬
    generateRandomData(randomData);
    printf("\nStarting Bubble Sort...\n");
    doBubbleSort(randomData);

    return 0;
}
