#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100
#define TRIALS 1

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
        printf("%3d ", array[i]); //3자리수로 출력.
    }
    printf("\n");
}

void printPartialArray(int array[], int rounds) {
    if (rounds % 10 == 0) { // 10번에 한 번 출력
        printf("라운드 %d - 배열 상태:\n", rounds);

        // 0~9 출력
        for (int i = 0; i < 10; i++) {
            printf("%3d ", array[i]);
        }
        printf("| ");

        // 중앙-1 ~ 중앙+10 출력
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) {
            printf("%3d ", array[i]);
        }
        printf("\n\n");
    }
}

void merge(int array[], int left, int mid, int right, int *comparisons, int *moves, int *rounds) {
    int n1 = mid - left + 1; //왼쪽 배열의 크기 계산.
    int n2 = right - mid; //오른쪽 배열의 크기 계산.
    int L[n1], R[n2]; //임시 배열 선언.

    // 왼쪽 배열 의 크기만큼 반복하며 왼쪽 배열을 임시 배열에 복사.
    //즉 정복 과정의 시작. 
    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
        (*moves)++;
    }
    // 오른쪽 배열 복사
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
        (*moves)++;
    }

    int i = 0, j = 0, k = left;
    // 왼쪽 배열과 오른쪽 배열 비교 후 작은 값을 원본 배열에 저장.
    //즉 본격 적인 정복 과정.
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
        (*moves)++;
    }

    // 왼쪽 배열에 남은 값을 원본 배열에 복사.
    //즉 결합 과정. 
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
        (*moves)++;
    }
    // 오른쪽 배열에 남은 값을 원본 배열에 복사.
    //즉 결합 과정. 
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
        (*moves)++;
    }

    (*rounds)++;
    printPartialArray(array, *rounds); // 배열 상태 출력
}

void mergeSort(int array[], int left, int right, int *comparisons, int *moves, int *rounds) {
    if (left < right) {
        int mid = left + (right - left) / 2; //중간 값 계산 단순하게 말해서 반쪼개기.

        mergeSort(array, left, mid, comparisons, moves, rounds);
        mergeSort(array, mid + 1, right, comparisons, moves, rounds);
        merge(array, left, mid, right, comparisons, moves, rounds);
    }
}

void doMergeSort(int array[]) {
    int comparisons = 0;
    int moves = 0;
    int rounds = 0; // 라운드 카운터
    int originalArray[SIZE];

    generateRandomNumber(array);
    copyArray(array, originalArray, SIZE);

    printf("정렬이 안된 난수 배열:\n");
    printArray(originalArray, SIZE);

    printf("\n병합 정렬 진행:\n");
    mergeSort(originalArray, 0, SIZE - 1, &comparisons, &moves, &rounds);

    printf("\n최종 병합 정렬된 배열:\n");
    printArray(originalArray, SIZE);

    printf("\nTotal Comparisons: %d\n", comparisons);
    printf("Total Moves: %d\n", moves);
}

int main() {
    int randomData[SIZE];

    printf("Merge Sort Run:\n");
    doMergeSort(randomData);

    return 0;
}
