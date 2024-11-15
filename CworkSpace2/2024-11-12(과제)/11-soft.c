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
        }
    }
    printf("Selection Sort Final Result:\n");
    printArray(array);
}

// 삽입 정렬 (Insertion Sort)
void doInsertionSort(int array[]) {
    int totalComparisons = 0;

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomData(tempArray);
        int comparisons = 0;

        for (int i = 1; i < SIZE; i++) {
            int key = tempArray[i];
            int j = i - 1;

            while (j >= 0) {
                comparisons++;
                if (tempArray[j] > key) {
                    tempArray[j + 1] = tempArray[j];
                    j--;
                } else {
                    break;
                }
            }
            tempArray[j + 1] = key;
        }
        totalComparisons += comparisons;

    }
    printf("Insertion Sort - Average Comparisons: %d\n", totalComparisons / TRIALS);
    printf("Insertion Sort Final Result:\n");
    printArray(array); // 마지막 정렬 결과 출력
}

// 버블 정렬 (Bubble Sort)
void doBubbleSort(int array[]) {
    int totalMoves = 0;

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomData(tempArray);
        int moves = 0;

        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempArray[j] > tempArray[j + 1]) {
                    // Swap
                    int temp = tempArray[j];
                    tempArray[j] = tempArray[j + 1];
                    tempArray[j + 1] = temp;
                    moves += 3; // 이동 횟수는 스왑마다 3으로 계산
                }
            }
        }
        totalMoves += moves;
    }

    printf("Bubble Sort - Average Moves: %d\n", totalMoves/TRIALS);
    printf("Bubble Sort Final Result:\n");
    printArray(array); // 마지막 정렬 결과 출력
}

int main() {
    int randomData[SIZE];
    srand(time(NULL));

    generateRandomData(randomData);
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
