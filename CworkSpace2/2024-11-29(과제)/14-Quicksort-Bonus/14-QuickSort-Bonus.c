#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100       // 배열 크기: 정렬할 데이터의 개수
#define TRIALS 20      // 테스트 반복 횟수: 평균 계산을 위한 실행 횟수

// 전역 변수 선언
int comparisonCount = 0;  // 비교 횟수를 저장
int moveCount = 0;        // 이동 횟수를 저장
int rounds = 0;           // 정렬 과정의 진행 상태를 추적
int isFirst = 0;          // 첫 번째 실행 여부를 확인

// 랜덤한 숫자로 배열 초기화
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999까지의 랜덤 숫자를 배열에 저장
    }
}

// 배열의 전체 요소를 출력
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);  // 배열의 각 요소를 한 줄로 출력
    }
    printf("\n");
}

// 배열의 40~60번째 요소를 출력 (정렬 과정 중 확인용)
void printPartialArray(int array[]) {
    printf("정렬 과정의 배열 40~60번째 요소: ");
    for (int i = 40; i < 60; i++) {
        printf("%d ", array[i]);  // 40~60번째 요소를 출력
    }
    printf("\n\n");  // 두 줄 띄우기
}

// 파티션 함수: 배열을 피벗을 기준으로 두 부분으로 나눔
int partition(int array[], int low, int high) {
    int pivot = array[high];  // 마지막 요소를 피벗으로 선택
    int i = low - 1;          // 작은 요소들의 끝 위치를 추적

    // 피벗보다 작은 값을 왼쪽으로 정렬
    for (int j = low; j < high; j++) {
        comparisonCount++;  // 비교 횟수 증가
        if (array[j] <= pivot) {
            i++;
            // 두 값을 교환
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            moveCount += 3;  // 교환 시 3번의 이동 발생 (temp 저장, 대입)
        }
    }

    // 피벗을 올바른 위치로 이동
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    moveCount += 3;  // 교환 시 3번의 이동 발생

    return i + 1;  // 피벗의 최종 위치 반환
}

// 반복적 퀵 정렬 함수
void doQuickSort(int array[], int low, int high) {
    int stack[SIZE]; // 스택을 사용해 반복적 퀵 정렬 구반
    int top = -1;    // 스택의 최상위 인덱스를 추적

    // 초기 값(범위) 스택에 추가
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) { // 스택이 비어있지 않을 때까지 반복
        high = stack[top--];  // 스택에서 범위를 꺼냄
        low = stack[top--];

        // 파티션을 수행하고 피벗 위치를 받음
        int pivotIndex = partition(array, low, high);

        // 10번째 라운드마다 배열의 40~60번째 요소를 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            printPartialArray(array);
        }
        rounds++;  // 라운드 증가

        // 피벗 왼쪽 부분 배열을 스택에 추가
        if (pivotIndex - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }

        // 피벗 오른쪽 부분 배열을 스택에 추가
        if (pivotIndex + 1 < high) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}

// 메인 함수
int main() {
    srand(time(NULL));  // 랜덤 시드 초기화 (매번 다른 랜덤 값을 생성)
    int array[SIZE];    // 정렬할 배열
    int totalComparisons = 0;  // 총 비교 횟수를 누적
    int totalMoveCount = 0;    // 총 이동 횟수를 누적

    // 20회 반복하여 정렬 수행 및 결과 기록
    for (int i = 0; i < TRIALS; i++) {
        generateRandomArray(array);  // 랜덤 배열 생성
        comparisonCount = 0;        // 비교 횟수 초기화
        moveCount = 0;              // 이동 횟수 초기화
        rounds = 0;                 // 라운드 초기화

        if (i == 0) {  // 첫 번째 실행 시 출력
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);  // 퀵 정렬 수행
            printf("Result\n");
            printArray(array, SIZE);         // 정렬된 배열 출력
            isFirst++;  // 첫 번째 실행 완료 플래그 설정
        } else {
            doQuickSort(array, 0, SIZE - 1);  // 출력 없이 정렬만 수행
        }

        // 비교 횟수와 이동 횟수를 누적
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // 평균 비교 횟수와 이동 횟수를 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / (float)TRIALS);
    printf("Average Moves: %.2f\n", totalMoveCount / (float)TRIALS);

    return 0;  // 프로그램 종료
}
