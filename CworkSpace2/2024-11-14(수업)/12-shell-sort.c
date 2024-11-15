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



// 쉘 정렬 (Shell Sort)
void doShellSortN2(int array[]) {
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
        printf("shell sort n/2\n");
        printf("Shell Sort with Gap %d:\n", gap);
        printArray(array);
        printf("\n");
    }
}

void doShellSortN3(int array[]) {
    for (int gap = SIZE / 3; gap > 0; gap /= 3) { // 간격을 줄여가며 반복
        for (int i = gap; i < SIZE; i++) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }

        // 정렬 과정 출력: 간격마다 배열 상태를 출력
        printf("shell sort n/3\n");
        printf("Shell Sort with Gap %d:\n", gap);
        printArray(array);
        printf("\n");
    }
}

int main() {
    int array[SIZE];
    srand(time(0));

    // 난수 데이터 생성
    generateRandomData(array);
    printf("Original Array:\n");
    printArray(array);
    printf("\n");

    // 쉘 정렬 수행
    doShellSortN2(array);
    doShellSortN3(array);
    printf("Array after Shell Sort:\n");
    printArray(array);

    return 0;
}
