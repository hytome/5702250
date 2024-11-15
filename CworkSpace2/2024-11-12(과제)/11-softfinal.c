#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100
#define TRIALS 20

// 난수 생성 함수
void generateRandomNumber(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 배열 복사 함수
void copyArray(int source[], int destination[]) {
    memcpy(destination, source, SIZE * sizeof(int));
}

// 선택 정렬 함수 (Step 출력 유지)
void doSelectionSort(int array[]) {
    int tempArray[SIZE];
    copyArray(array, tempArray);  // 원본 데이터 보호를 위해 배열 복사

    int i, j, minIdx, temp;
    for (i = 0; i < SIZE - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < SIZE; j++) {
            if (tempArray[j] < tempArray[minIdx]) {
                minIdx = j;
            }
        }
        temp = tempArray[i];
        tempArray[i] = tempArray[minIdx];
        tempArray[minIdx] = temp;

        // Step 출력 조건
        if ((i + 1) == 10 || (i + 1) == 30 || (i + 1) == 50 || (i + 1) == 70 || (i + 1) == 90 || i == SIZE - 2) {
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", tempArray[k]);
            }
            printf("\n");
        }
    }
    printf("Selection Sort Result:\n");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", tempArray[k]);
    }
    printf("\n");
}

// 삽입 정렬 함수
void doInsertionSort(int array[]) {
    int totalComparisons = 0;

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomNumber(tempArray);  // 매번 새로운 난수 배열 생성

        int comparisons = 0;
        for (int i = 1; i < SIZE; i++) {
            int key = tempArray[i];
            int j = i - 1;

            while (j >= 0 && tempArray[j] > key) {
                tempArray[j + 1] = tempArray[j];
                j--;
                comparisons++;
            }
            tempArray[j + 1] = key;
        }
        totalComparisons += comparisons;
    }

    printf("Insertion Sort Compare Average: %d\n", totalComparisons / TRIALS);

    // 최종 결과 출력 (원본 배열을 복사하여 사용)
    int finalArray[SIZE];
    copyArray(array, finalArray);
    for (int i = 1; i < SIZE; i++) {
        int key = finalArray[i];
        int j = i - 1;

        while (j >= 0 && finalArray[j] > key) {
            finalArray[j + 1] = finalArray[j];
            j--;
        }
        finalArray[j + 1] = key;
    }
    printf("Insertion Sort Result:\n");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", finalArray[k]);
    }
    printf("\n");
}

// 버블 정렬 함수
void doBubbleSort(int array[]) {
    int totalMoves = 0;

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomNumber(tempArray);  // 매번 새로운 난수 배열 생성

        int moves = 0;
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempArray[j] > tempArray[j + 1]) {
                    int temp = tempArray[j];
                    tempArray[j] = tempArray[j + 1];
                    tempArray[j + 1] = temp;
                    moves += 3;
                }
            }
        }
        totalMoves += moves;
    }

    printf("Bubble Sort Move Average: %d\n", totalMoves / TRIALS);

    // 최종 결과 출력 (원본 배열을 복사하여 사용)
    int finalArray[SIZE];
    copyArray(array, finalArray);
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (finalArray[j] > finalArray[j + 1]) {
                int temp = finalArray[j];
                finalArray[j] = finalArray[j + 1];
                finalArray[j + 1] = temp;
            }
        }
    }
    printf("Bubble Sort Result:\n");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", finalArray[k]);
    }
    printf("\n");
}

int main() {
    int randomData[SIZE];

    srand(time(NULL));
    generateRandomNumber(randomData);

    printf("Selection Sort:\n");
    doSelectionSort(randomData);  // 선택 정렬

    printf("\nInsertion Sort:\n");
    doInsertionSort(randomData);  // 삽입 정렬

    printf("\nBubble Sort:\n");
    doBubbleSort(randomData);  // 버블 정렬

    return 0;
}
