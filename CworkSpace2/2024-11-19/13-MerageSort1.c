#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100
#define TRIALS 20

int is_seeded = 0;

void generateRandomNumber(int array[]) {
    if (!is_seeded) {
        srand(time(NULL));
        is_seeded = 1;
    }
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//병합 과정에서 이동횟수와 비교횟수를 추적하는 과정.
//또한 병합 과정에서 왼쪽 오른쪽 배열을 복사하는 과정.
//즉 하위 배열을 병합하여 정렬을 하는 기능.
void merge(int array[], int left, int mid, int right, int *comparisons, int *moves) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
        (*moves)++; // 이동 횟수 증가
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
        (*moves)++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++; // 왼쪽 배열 인덱스 증가
        } else {
            array[k] = R[j];
            j++; // 오른쪽 배열 인덱스 증가
        }
        k++;
        (*moves)++; // 이동 횟수 증가
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
        (*moves)++; // 이동 횟수 증가
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
        (*moves)++;
    }
}

// 병합 정렬:왼쪽 오른쪽 반으로 쪼개기.
void mergeSort(int array[], int left, int right, int *comparisons, int *moves) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        //이걸 어떻게 반복적인 방법으로  구현하지...
        mergeSort(array, left, mid, comparisons, moves);
        mergeSort(array, mid + 1, right, comparisons, moves);
        merge(array, left, mid, right, comparisons, moves);
    }
}

// 병합 정렬 실행 함수
void doMergeSort(int array[]) {
    int totalComparisons = 0;
    int totalMoves = 0;
    int originalArray[SIZE];

    // 첫 번째 난수 배열 생성 및 저장
    generateRandomNumber(array);
    copyArray(array, originalArray, SIZE);

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomNumber(tempArray);
        copyArray(originalArray, tempArray, SIZE);
        //첫 번쨰 난수 배열 복사와 generateRandomNumber 함수를 이용하여 다시 난수 배열 생성.

        int comparisons = 0;
        int moves = 0;
        mergeSort(tempArray, 0, SIZE - 1, &comparisons, &moves);

        totalComparisons += comparisons;
        totalMoves += moves;
    }

    // 첫 번째 난수 배열 출력
    printf("정렬이 안된 난수 배열:\n");
    printArray(originalArray, SIZE);

    // 정렬된 배열 출력
    int comparisons = 0;
    int moves = 0;
    mergeSort(originalArray, 0, SIZE - 1, &comparisons, &moves);
    printf("합병 정렬된 배열:\n");
    printArray(originalArray, SIZE);

    printf("합병 정렬 비교 평균: %d\n", totalComparisons / TRIALS);
    printf("합병 정렬 이동 평균: %d\n", totalMoves / TRIALS);
}

int main() {
    int randomData[SIZE];

    printf("Merge Sort:\n");
    doMergeSort(randomData);

    return 0;
}