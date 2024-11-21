#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100  // 배열의 크기를 정의 (정렬할 데이터의 개수)
#define TRIALS 20 // 평균 계산을 위해 반복할 실험 횟수

int is_seeded = 0; // 난수 생성 시, srand가 한 번만 실행되었는지 확인하는 플래그

// 난수 생성 함수
// - 배열을 난수 값으로 채웁니다.
// - srand를 이용하여 난수 생성을 초기화합니다.
void generateRandomNumber(int array[]) {
    if (!is_seeded) {  // srand가 한 번만 호출되도록 보장
        srand(time(NULL));  // 현재 시간을 기준으로 난수 생성 초기화
        is_seeded = 1;      // 시드가 설정되었음을 표시
        // Note: 동일한 실행 시 동일한 난수 값이 생성되지 않도록 설정
    }
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999까지의 난수를 생성하여 배열에 저장
    }
}

// 배열 복사 함수
// - 소스 배열의 데이터를 목적지 배열로 복사합니다.
// - memcpy를 사용하여 효율적으로 메모리를 복사합니다.
void copyArray(int source[], int destination[]) {
    memcpy(destination, source, SIZE * sizeof(int));  // 배열의 메모리를 복사
}

// 쉘 정렬 함수
// - 배열을 정렬하는 데 사용되며, 삽입 정렬의 변형입니다.
// - 간격(gap)을 줄이면서 정렬하여 점진적으로 데이터를 정렬 상태로 만듭니다.
void doShellSort(int originalArray[], int gapFactor, int *avgComparison, int *avgMove) {
    int sortedArray[SIZE];
    copyArray(originalArray, sortedArray);  // 원본 데이터를 보호하기 위해 복사

    // 간격 배열 계산
    // - 간격은 gapFactor로 나누며 점점 작아집니다.
    int gaps[SIZE], gapCount = 0;
    for (int gap = SIZE / gapFactor; gap > 0; gap /= gapFactor) {
        gaps[gapCount++] = gap;  // 계산된 간격을 배열에 저장
    }

    // 간격에 따른 삽입 정렬 수행
    for (int g = 0; g < gapCount; g++) {
        int gap = gaps[g];  // 현재 간격 값

        for (int i = gap; i < SIZE; i++) {  // 간격 이상부터 데이터 정렬 시작
            int temp = sortedArray[i];  // 현재 정렬 대상 값 저장
            int j = i;

            // 삽입 정렬 수행 (현재 간격 기준)
            while (j >= gap && sortedArray[j - gap] > temp) {
                sortedArray[j] = sortedArray[j - gap];  // 값 이동
                j -= gap;
            }
            sortedArray[j] = temp;  // 정렬 위치에 삽입
        }

        // 현재 간격 상태를 출력
        printf("Gap %d:\n", gap);
        for (int k = 0; k < SIZE; k++) {
            if (k < 20) {
                printf("%d ", sortedArray[k]);  // 상위 20개 데이터 출력
            } else if (k == 20) {
                printf("... ");  // 데이터 생략 표시
                break;
            }
        }
        printf("\n\n");
    }

    // 최종 정렬된 결과 출력
    printf("Shell Sort Result (n/%d):\n", gapFactor);
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sortedArray[i]);
    }
    printf("\n\n");

    // 평균 비교 및 이동 횟수 계산
    *avgComparison = 0;  // 비교 횟수 초기화
    *avgMove = 0;        // 이동 횟수 초기화

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomNumber(tempArray);  // 실험을 위한 난수 배열 생성

        int comparisonCount = 0, moveCount = 0;

        // 정렬 수행 및 비교/이동 횟수 계산
        for (int g = 0; g < gapCount; g++) {
            int gap = gaps[g];
            for (int i = gap; i < SIZE; i++) {
                int temp = tempArray[i];
                int j = i;

                while (j >= gap && tempArray[j - gap] > temp) {
                    tempArray[j] = tempArray[j - gap];
                    j -= gap;
                    comparisonCount++;  // 비교 발생 시 카운트 증가
                    moveCount++;        // 이동 발생 시 카운트 증가
                }
                tempArray[j] = temp;
                moveCount++;  // 삽입 동작 카운트
            }
        }
        *avgComparison += comparisonCount;  // 총 비교 횟수 누적
        *avgMove += moveCount;              // 총 이동 횟수 누적
    }

    // 평균값 계산
    *avgComparison = *avgComparison / TRIALS;
    *avgMove = *avgMove / TRIALS;

    // 결과 출력
    printf("Shell Sort (n/%d) Compare Average: %d\n", gapFactor, *avgComparison);
    printf("Shell Sort (n/%d) Move Average: %d\n", gapFactor, *avgMove);
}

// 삽입 정렬 함수
// - 배열을 정렬하고 평균 비교 및 이동 횟수를 계산합니다.
// - 간격 없이 바로 옆 원소만 비교하는 가장 기본적인 정렬 방식
void doInsertionSort(int originalArray[], int *avgComparison, int *avgMove) {
    *avgComparison = 0;  // 평균 비교 횟수 초기화
    *avgMove = 0;        // 평균 이동 횟수 초기화

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomNumber(tempArray);  // 실험을 위한 난수 배열 생성

        int comparisonCount = 0, moveCount = 0;

        for (int i = 1; i < SIZE; i++) {
            int key = tempArray[i];  // 현재 정렬 대상 값
            int j = i - 1;

            // 현재 위치보다 큰 값들을 오른쪽으로 이동
            while (j >= 0 && tempArray[j] > key) {
                tempArray[j + 1] = tempArray[j];
                j--;
                comparisonCount++;  // 비교 발생 시 카운트 증가
                moveCount++;        // 이동 발생 시 카운트 증가
            }
            tempArray[j + 1] = key;  // 적절한 위치에 삽입
            moveCount++;  // 삽입 동작 카운트
        }
        *avgComparison += comparisonCount;  // 총 비교 횟수 누적
        *avgMove += moveCount;              // 총 이동 횟수 누적
    }

    *avgComparison = *avgComparison / TRIALS;  // 평균 비교 횟수 계산
    *avgMove = *avgMove / TRIALS;              // 평균 이동 횟수 계산

    // 결과 출력
    printf("Insertion Sort Compare Average: %d\n", *avgComparison);
    printf("Insertion Sort Move Average: %d\n", *avgMove);

    // 최종 정렬 결과 출력
    int sortedArray[SIZE];
    copyArray(originalArray, sortedArray);

    for (int i = 1; i < SIZE; i++) {
        int key = sortedArray[i];
        int j = i - 1;

        while (j >= 0 && sortedArray[j] > key) {
            sortedArray[j + 1] = sortedArray[j];
            j--;
        }
        sortedArray[j + 1] = key;
    }

    printf("Insertion Sort Result:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sortedArray[i]);
    }
    printf("\n");
}


int main() {
    int originalArray[SIZE];
    generateRandomNumber(originalArray);

    int shellComp2, shellMove2;
    printf("Shell Sort (n/2):\n");
    doShellSort(originalArray, 2, &shellComp2, &shellMove2);

    int shellComp3, shellMove3;
    printf("\nShell Sort (n/3):\n");
    doShellSort(originalArray, 3, &shellComp3, &shellMove3);

    int insertionComp, insertionMove;
    printf("\nInsertion Sort:\n");
    doInsertionSort(originalArray, &insertionComp, &insertionMove);
    printf("\n");
    

    printf("Comparison of Sorting Algorithms:\n");
    printf("Algorithm          Comparisons    Moves\n");
    printf("---------------------------------------\n");
    printf("Shell Sort (n/2):  %10d    %10d\n", shellComp2, shellMove2);
    printf("Shell Sort (n/3):  %10d    %10d\n", shellComp3, shellMove3);
    printf("Insertion Sort:    %10d    %10d\n", insertionComp, insertionMove);

    return 0;
}
