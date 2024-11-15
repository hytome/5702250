#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100  // 배열 크기를 100으로 설정
#define TRIALS 20  // 20번 반복과 평균을 구하기 위해 설정

// 랜덤 데이터 생성 함수
// 배열에 랜덤 숫자를 채웁니다.
void generateRandomNumber(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0~999까지의 랜덤 숫자 생성
    }
}

// 배열 출력 함수
// 배열의 모든 요소를 출력합니다.
void printArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);  // 배열 요소 출력
    }
    printf("\n");  // 줄바꿈
}

// 선택 정렬 (Selection Sort)
// 배열을 선택 정렬 알고리즘으로 정렬합니다.
void doSelectionSort(int array[]) {
    int i, j, minIdx, temp;  // 변수 선언
    for (i = 0; i < SIZE - 1; i++) {
        minIdx = i;  // 최소값 인덱스를 현재 인덱스로 초기화
        for (j = i + 1; j < SIZE; j++) {
            if (array[j] < array[minIdx]) {  // 더 작은 값 발견 시
                minIdx = j;  // 최소값 인덱스 갱신
            }
        }
        // Swap
        temp = array[i];  // 현재 요소와 최소값 요소 교환
        array[i] = array[minIdx];
        array[minIdx] = temp;

        // 정렬 과정 출력: 10부터 20단위 및 마지막 단계 출력 그걸 위한 조건문. 
        if ((i + 1) == 10 || ((i + 1) > 10 && ((i + 1) - 10) % 20 == 0) || i == SIZE - 2) {
            printf("Selection Sort Step %d:\n", i + 1);  // 단계 출력
            printArray(array);  // 배열 출력
        }
    }
    printf("Selection Sort Final Result:\n");  // 최종 결과 출력
    printArray(array);  // 배열 출력
}

// 삽입 정렬 (Insertion Sort)
// 배열을 삽입 정렬 알고리즘으로 정렬합니다.
void doInsertionSort(int array[]) {
    int totalComparisons = 0;  // 총 비교 횟수 초기화

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];  // 임시 배열 선언
        generateRandomNumber(tempArray);  // 랜덤 데이터 생성
        int comparisons = 0;  // 비교 횟수 초기화

        for (int i = 1; i < SIZE; i++) {
            int key = tempArray[i];  // 현재 키 설정
            int j = i - 1;  // 이전 인덱스 설정

            while (j >= 0) {
                comparisons++;  // 비교 횟수 증가
                if (tempArray[j] > key) {  // 현재 키보다 큰 경우
                    tempArray[j + 1] = tempArray[j];  // 요소 이동
                    j--;  // 인덱스 감소
                } else {
                    break;  // 루프 종료
                }
            }
            tempArray[j + 1] = key;  // 키 삽입
        }
        totalComparisons += comparisons;  // 총 비교 횟수 누적
    }
    printf("Insertion Sort - Average Comparisons: %d\n", totalComparisons / TRIALS);  // 평균 비교 횟수 출력
    printf("Insertion Sort Final Result:\n");  // 최종 결과 출력
    printArray(array);  // 배열 출력
}

// 버블 정렬 (Bubble Sort)
// 배열을 버블 정렬 알고리즘으로 정렬합니다.
void doBubbleSort(int array[]) {
    int totalMoves = 0;  // 총 이동 횟수 초기화

    for (int trial = 0; trial < TRIALS; trial++) {
        int tempArray[SIZE];  // 임시 배열 선언
        generateRandomNumber(tempArray);  // 랜덤 데이터 생성
        int moves = 0;  // 이동 횟수 초기화

        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempArray[j] > tempArray[j + 1]) {  // 인접 요소 비교
                    // Swap
                    int temp = tempArray[j];  // 요소 교환
                    tempArray[j] = tempArray[j + 1];
                    tempArray[j + 1] = temp;
                    moves += 3;  // 이동 횟수는 스왑마다 3으로 계산
                }
            }
        }
        totalMoves += moves;  // 총 이동 횟수 누적
    }

    printf("Bubble Sort - Average Moves: %d\n", totalMoves / TRIALS);  // 평균 이동 횟수 출력
    printf("Bubble Sort Final Result:\n");  // 최종 결과 출력
    printArray(array);  // 배열 출력
}

int main() {
    int randomData[SIZE]; 
    srand(time(NULL)); 

    generateRandomNumber(randomData);  
    doSelectionSort(randomData);  
    doInsertionSort(randomData);  
    doBubbleSort(randomData);  

    return 0;  // 프로그램 종료
}
