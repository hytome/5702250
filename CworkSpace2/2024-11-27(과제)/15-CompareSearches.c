#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

// ========================= 퀵 정렬 관련 함수들 =========================
int partition(int *array, int low, int high, int *compareCount);

// 퀵 정렬 함수
// array: 정렬할 배열
// low: 정렬할 부분의 시작 인덱스
// high: 정렬할 부분의 끝 인덱스
// compareCount: 비교 횟수를 저장하는 포인터
int quickSort(int *array, int low, int high, int *compareCount) {
    if (low < high) {
        // 피벗을 기준으로 배열을 분할
        int pivot = partition(array, low, high, compareCount);
        // 피벗을 기준으로 왼쪽 부분 정렬
        quickSort(array, low, pivot - 1, compareCount);
        // 피벗을 기준으로 오른쪽 부분 정렬
        quickSort(array, pivot + 1, high, compareCount);
    }
    return *compareCount;
}

// 퀵 정렬의 분할 함수
// 피벗을 기준으로 작은 값은 왼쪽, 큰 값은 오른쪽으로 분할
int partition(int *array, int low, int high, int *compareCount) {
    int pivot = array[high];  // 피벗으로 마지막 요소 선택
    int i = (low - 1);  // 작은 요소들의 경계를 나타내는 인덱스
    
    // 피벗보다 작은 요소들을 왼쪽으로 이동
    for (int j = low; j <= high - 1; j++) {
        (*compareCount)++;  // 비교 횟수 증가
        if (array[j] < pivot) {
            i++;
            // 현재 요소를 작은 요소들의 영역으로 스왑
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    // 피벗을 올바른 위치로 이동
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

// ========================= 유틸리티 함수들 =========================

// 랜덤 배열 생성 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999까지의 난수 생성
    }
}

// 배열 출력 함수
// 처음 20개와 마지막 20개 요소만 출력
void printArray(int *array) {
    printf("Array Sorting Result:\n");
    // 처음 20개 요소 출력
    for(int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    // 마지막 20개 요소 출력
    for(int i = SIZE-20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// ========================= 검색 관련 함수들 =========================

// 순차 탐색의 평균 비교 횟수 계산 함수
float getAverageLinearSearchCompareCount(int *array) {
    int totalCompareCount = 0;
    // 100번의 검색 시도
    for (int i = 0; i < 100; i++) {
        int key = rand() % 1000;  // 검색할 키 값 랜덤 생성
        int compareCount = 0;
        int found = 0;  // 키 값 발견 여부

        // 첫 번째 탐색 - 키 값이 존재하는지 확인
        for (int j = 0; j < SIZE; j++) {
        
            if (array[j] == key) {
                compareCount++;
                found = 1;
                break;
            }
        }

        // 키 값탐 존재하는 경우에만 배열에서 탐색  수행
        if (found) {
            for (int j = 0; j < SIZE; j++) {
                compareCount++;
                if (array[j] == key) {
                    break;
                }
            }
            totalCompareCount += compareCount;
        }
    }
    return (float)totalCompareCount / 100;  // 평균 비교 횟수 반환
}

// 퀵 정렬의 비교 횟수 반환 함수
int getQuickSortCompareCount(int *array) {
    int compareCount = 0;
    quickSort(array, 0, SIZE - 1, &compareCount);
    return compareCount;
}

// 이진 탐색의 평균 비교 횟수 계산 함수
float getAverageBinarySearchCompareCount(int *array) {
    int totalCompareCount = 0;
    // 100번의 검색 시도
    for (int i = 0; i < 100; i++) {
        int key = rand() % 1000;  // 검색할 키 값 랜덤 생성
        int compareCount = 0;
        int found = 0;  // 키 값 발견 여부

        // 첫 번째 탐색 - 키 값이 존재하는지 확인
        for (int j = 0; j < SIZE; j++) {
            
            if (array[j] == key) {
                compareCount++;
                found = 1;
                break;
            }
        }

        // 키 값이 존재하는 경우에만 이진 탐색 수행
        if (found) {
            int low = 0, high = SIZE - 1;
            while (low <= high) {
                compareCount++;
                int mid = low + (high - low) / 2;
                if (array[mid] == key) {
                    break;
                }
                if (array[mid] < key) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            totalCompareCount += compareCount;
        }
    }
    return (float)totalCompareCount / 100;  // 평균 비교 횟수 반환
}

// ========================= 메인 함수 =========================
int main(int argc, char *argv[]) {
    srand(time(NULL));  // 난수 생성기 초기화
    int array[SIZE];
    
    generateRandomArray(array);  // 랜덤 배열 생성
    
    // 각 검색 방법의 비교 횟수 계산 및 출력
    printf("Average Linear Search Compare Count: %.2f\n", 
           getAverageLinearSearchCompareCount(array));
    
    int compareCount = getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);
    
    printf("Average Binary Search Compare Count: %.2f\n\n", 
           getAverageBinarySearchCompareCount(array));
    
    printArray(array);  // 정렬된 배열 출력
    return 0;
}