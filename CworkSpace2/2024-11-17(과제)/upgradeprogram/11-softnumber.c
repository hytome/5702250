//이 프로그램은 제가 generateRandomNumber 함수에서 20번의 반복 동안.
//다른 난수가 성공적으로 생성되어 20번의 정렬이 이루어지는지 확인하는 기능이 추가된 프로그램입니다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100
#define TRIALS 20

int is_seeded = 0; // 시드 설정 여부를 나타내는 전역 변수

// 난수 생성 함수
void generateRandomNumber(int array[]) {
    if (!is_seeded) {
        srand(time(NULL));  // 난수 생성기 시드 설정
        is_seeded = 1;      // 시드가 설정되었음을 표시
        //이렇게 time의 선언은 처음에 한번만 이루어 져야한다.
        //아니면 generateRandomNumber 함수가 여러번 호출될시 동일한 시드가 설정되어 호출할때마다 동일한 난수가 생성된다.
        //그러면 굳이 20번 반복해서 비교횟수나 이동횟구를 구하는 프로그램의 의도 대로 작동하지 않는다.
        //왜냐면 time은 프로그램이 실행되는 순간 난수값이 결정되기 떄문. 
    }
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
        if ((i + 1) == 10 || ((i + 1) > 10 && ((i + 1) - 10) % 20 == 0) || i == SIZE - 2){
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", tempArray[k]);
            }
            printf("\n\n");
        }
    }
    printf("Selection Sort Result:\n");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", tempArray[k]);
    }
    printf("\n");
}

void printArraySample(int array[]) {
    printf("[");
    for (int i = 0; i < 5; i++) {  // 앞의 5개 요소만 출력
        printf("%d", array[i]);
        if (i < 4) {
            printf(", ");
        }
    }
    printf(", ...]\n");
}

// 삽입 정렬 함수
void doInsertionSort(int array[]) {
    int totalComparisons = 0;

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];
        generateRandomNumber(tempArray);  // 매번 새로운 난수 배열 생성
        printf("Insertion Sort - Trial %d: Random data generated. Sample: ", trial + 1);
        printArraySample(tempArray);
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

    
    generateRandomNumber(randomData);

    printf("Selection Sort:\n");
    doSelectionSort(randomData);  // 선택 정렬

    printf("\nInsertion Sort:\n");
    doInsertionSort(randomData);  // 삽입 정렬

    printf("\nBubble Sort:\n");
    doBubbleSort(randomData);     // 버블 정렬

    return 0;
}
