#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 100
#define TRIALS 20

int is_seeded = 0;

// 난수 생성 함수
void generateRandomNumber(int array[]) {
    if (!is_seeded) {
        srand(time(NULL));
        is_seeded = 1;
    }
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 배열 복사 함수
void copyArray(int source[], int destination[]) {
    memcpy(destination, source, SIZE * sizeof(int));
}

// 쉘 정렬 함수
void doShellSort(int array[], int gapType, int *comparisonCount, int *moveCount) {
    int tempArray[SIZE];
    copyArray(array, tempArray);
    *comparisonCount = 0;
    *moveCount = 0;

    int gaps[SIZE];
    int gapCount = 0;

    // 간격 계산
    if (gapType == 2) {
        for (int gap = SIZE / 2; gap > 0; gap /= 2) {
            gaps[gapCount++] = gap;
        }
    } else if (gapType == 3) {
        for (int gap = SIZE / 3; gap > 0; gap /= 3) {
            gaps[gapCount++] = gap;
        }
    }

    // 쉘 정렬 수행
    for (int g = 0; g < gapCount; g++) {
        int gap = gaps[g];
        for (int i = gap; i < SIZE; i++) {
            int temp = tempArray[i];
            int j = i;

            while (j >= gap && tempArray[j - gap] > temp) {
                tempArray[j] = tempArray[j - gap];
                j -= gap;
                (*comparisonCount)++;
                (*moveCount)++;
            }
            tempArray[j] = temp;
            (*moveCount)++;
        }

        // 현재 간격에 대한 배열 상태 출력
        printf("Gap %d:\n", gap);
        for (int k = 0; k < SIZE; k++) {
            printf("%d ", tempArray[k]);
        }
        printf("\n\n");
    }

    printf("Shell Sort Result:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", tempArray[i]);
    }
    printf("\n");
}

int main() {
    int randomData[SIZE];
    int comparisonCount, moveCount;

    generateRandomNumber(randomData);

    // Shell Sort (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(randomData, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Shell Sort (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(randomData, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    return 0;
}
