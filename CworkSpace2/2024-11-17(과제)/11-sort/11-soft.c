#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100
#define TRIALS 20

int is_seeded = 0; // 시드 설정 여부를 나타내는 전역 변수

// 난수 생성 함수
// 주어진 배열에 난수를 생성하여 채웁니다.
void generateRandomNumber(int array[]) {
    if (!is_seeded) {
        srand(time(NULL));  // 난수 생성기 시드 설정
        is_seeded = 1;      // 시드가 설정되었음을 표시
        // 이렇게 time의 선언은 처음에 한번만 이루어 져야한다.
        // 아니면 generateRandomNumber 함수가 여러번 호출될시 동일한 시드가 설정되어 호출할때마다 동일한 난수가 생성된다.
        // 그러면 굳이 20번 반복해서 비교횟수나 이동횟구를 구하는 프로그램의 의도 대로 작동하지 않는다.
        // 왜냐면 time은 프로그램이 실행되는 순간 난수값이 결정되기 떄문. 
    }
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999까지의 난수를 생성하여 배열에 저장
    }
}

// 배열 복사 함수
// 소스 배열의 내용을 목적지 배열로 복사합니다.
// 프로그램 실행 결과에는 초기에 호출된 난수값을 이용하여 정렬문을 출력해 가독성을 높이기 때문입니다.
void copyArray(int source[], int destination[]) {
    memcpy(destination, source, SIZE * sizeof(int));  // 메모리 복사를 통해 배열 복사
}

// 선택 정렬 함수 (Step 출력 유지)
// 선택 정렬 알고리즘을 사용하여 배열을 정렬합니다.
void doSelectionSort(int array[]) {
    int tempArray[SIZE];
    copyArray(array, tempArray);  // 원본 데이터 보호를 위해 배열 복사

    int i, j, minIdx, temp;
    for (i = 0; i < SIZE - 1; i++) {
        minIdx = i;  // 현재 위치를 최소값 인덱스로 설정
        for (j = i + 1; j < SIZE; j++) {
            if (tempArray[j] < tempArray[minIdx]) {
                minIdx = j;  // 더 작은 값을 찾으면 최소값 인덱스 갱신
            }
        }
        temp = tempArray[i];  // 현재 위치와 최소값 위치의 요소를 교환
        tempArray[i] = tempArray[minIdx];
        tempArray[minIdx] = temp;

        // Step 출력 조건
        if ((i + 1) == 10 || ((i + 1) > 10 && ((i + 1) - 10) % 20 == 0) || i == SIZE - 2){
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", tempArray[k]);  // 현재 배열 상태 출력
            }
            printf("\n\n");
        }
    }
    printf("Selection Sort Result:\n");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", tempArray[k]);  // 정렬된 배열 출력
    }
    printf("\n");
}

// 삽입 정렬 함수
// 삽입 정렬 알고리즘을 사용하여 배열을 정렬하고 평균 비교 횟수를 계산합니다.
void doInsertionSort(int array[]) {
    int totalComparisons = 0;  // 총 비교 횟수를 저장하는 변수

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomNumber(tempArray);  // 매번 새로운 난수 배열 생성
        
        int comparisons = 0;  // 현재 시도에서의 비교 횟수
        for (int i = 1; i < SIZE; i++) {
            int key = tempArray[i];  // 현재 요소를 키로 설정
            int j = i - 1;

            while (j >= 0 && tempArray[j] > key) {
                tempArray[j + 1] = tempArray[j];  // 요소를 오른쪽으로 이동
                j--;
                comparisons++;  // 비교 횟수 증가
            }
            tempArray[j + 1] = key;  // 키를 올바른 위치에 삽입
        }
        totalComparisons += comparisons;  // 총 비교 횟수에 현재 시도의 비교 횟수 추가
    }

    printf("Insertion Sort Compare Average: %d\n", totalComparisons / TRIALS);  // 평균 비교 횟수 출력

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
        printf("%d ", finalArray[k]);  // 정렬된 배열 출력
    }
    printf("\n");
}

// 버블 정렬 함수
// 버블 정렬 알고리즘을 사용하여 배열을 정렬하고 평균 이동 횟수를 계산합니다.
void doBubbleSort(int array[]) {
    int totalMoves = 0;  // 총 이동 횟수를 저장하는 변수

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomNumber(tempArray);  // 매번 새로운 난수 배열 생성

        int moves = 0;  // 현재 시도에서의 이동 횟수
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempArray[j] > tempArray[j + 1]) {
                    int temp = tempArray[j];  // 인접 요소 교환
                    tempArray[j] = tempArray[j + 1];
                    tempArray[j + 1] = temp;
                    moves += 3;  // 교환 시 이동 횟수 증가(과제에서 제시한 이동횟수 3회 구현.)
                }
            }
        }
        totalMoves += moves;  // 총 이동 횟수에 현재 시도의 이동 횟수 추가
    }

    printf("Bubble Sort Move Average: %d\n", totalMoves / TRIALS);  // 평균 이동 횟수 출력

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
        printf("%d ", finalArray[k]);  // 정렬된 배열 출력
    }
    printf("\n");
}

int main() {
    int randomData[SIZE];

    generateRandomNumber(randomData);

    printf("Selection Sort:\n");
    doSelectionSort(randomData);  // 선택 정렬

    printf("\nInsertion Sort:\n");
    doInsertionSort(randomData);  // 삽입 정렬

    printf("\nBubble Sort:\n");
    doBubbleSort(randomData);     // 버블 정렬

    return 0;
}