#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000           // 배열의 크기
#define SEARCH_COUNT 1000    // 탐색 횟수
#define INSERTION_SORT_THRESHOLD 10 // 삽입 정렬을 적용할 서브 배열의 최대 크기

// 함수 선언
void generateRandomArray(int array[]);
void QuickSort(int *array, int low, int high);
int medianOfThree(int *array, int low, int high);
int partition(int *array, int low, int high);
void insertionSort(int *array, int low, int high);
void printArray(int *array);
int binarySearch(int *array, int size, int key, int *compareCount);
int interpolationSearch(int *array, int size, int key, int *compareCount);
float getAverageBinarySearchCompareCount(int *array);
float getAverageInterpolationSearchCompareCount(int *array);

// 1. 랜덤 배열 생성 함수
// - 배열을 0부터 9999 사이의 난수로 채웁니다.
void generateRandomArray(int array[]) {
    for(int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000; // 0부터 9999 사이의 숫자
    }
}

// 2. 최적화된 퀵 정렬 구현
// - 배열을 정렬하는 데 사용되며, 서브 배열의 크기가 작을 경우 삽입 정렬을 사용합니다.
// - 피벗 선택을 Median-of-Three 방식으로 최적화합니다.
void QuickSort(int *array, int low, int high) {
    while (low < high) {
        // 서브 배열의 크기가 임계값 이하인 경우 삽입 정렬 적용
        if (high - low + 1 <= INSERTION_SORT_THRESHOLD) {
            insertionSort(array, low, high);
            break;
        } else {
            // 피벗 선택 최적화 (Median-of-Three)
            int pivot = medianOfThree(array, low, high);
            // 파티션 수행
            int p = partition(array, low, high);
            // 작은 서브 배열을 먼저 정렬하여 스택 깊이를 줄임
            if (p - low < high - p) {
                QuickSort(array, low, p - 1);
                low = p + 1;
            } else {
                QuickSort(array, p + 1, high);
                high = p - 1;
            }
        }
    }
}

// Median-of-Three 피벗 선택 함수
// - 세 개의 요소 중 중앙값을 선택하여 피벗으로 사용합니다.
//기존의 퀵 정렬에서 피벗을 선택하는 방법을 최적화한 것
int medianOfThree(int *array, int low, int high) {
    int mid = low + (high - low) / 2;
    
    //세 값을 비교하여 중앙 값을 찾는 과정입니다.
    if (array[low] > array[mid]) {
        // 스왑 array[low]와 array[mid]
        int temp = array[low];
        array[low] = array[mid];
        array[mid] = temp;
    }
    
    if (array[low] > array[high]) {
        // 스왑 array[low]와 array[high]
        int temp = array[low];
        array[low] = array[high];
        array[high] = temp;
    }
    
    if (array[mid] > array[high]) {
        // 스왑 array[mid]와 array[high]
        int temp = array[mid];
        array[mid] = array[high];
        array[high] = temp;
    }
    
    // 중앙값을 피벗으로 설정 (array[mid]을 array[high]와 교환)
    int temp = array[mid];
    array[mid] = array[high];
    array[high] = temp;
    
    return array[high];
}

// 파티션 함수 (퀵 정렬의 핵심)
// - 피벗을 기준으로 배열을 두 부분으로 나눕니다.
//작은 값은 왼쪽 큰 값은 오른쪽으로 정렬하는 과정입니다.
int partition(int *array, int low, int high) {
    int pivot = array[high]; // Median-of-Three로 선택된 피벗
    int i = low - 1; // 작은 요소의 인덱스

    for(int j = low; j <= high - 1; j++) {
        if(array[j] < pivot) {
            i++;
            // array[i]와 array[j]를 교환
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    // 피벗을 제자리에 놓기
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

// 작은 배열을 위한 삽입 정렬 함수
// - 서브 배열의 크기가 작을 때 사용하여 효율성을 높입니다.
void insertionSort(int *array, int low, int high) {
    for(int i = low + 1; i <= high; i++) {
        int key = array[i];
        int j = i - 1;
        while(j >= low && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

// 6. 배열 출력 함수
// - 배열의 처음 20개와 마지막 20개 요소를 출력합니다.
void printArray(int *array) {
    printf("Array Sorting Result:\n");
    // 처음 20개 요소 출력
    for(int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    // 마지막 20개 요소 출력
    for(int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// 3. 이진 탐색 함수
// - 정렬된 배열에서 키를 찾고, 비교 횟수를 기록합니다.
int binarySearch(int *array, int size, int key, int *compareCount) {
    int low = 0;
    int high = size - 1;
    while(low <= high) {
        (*compareCount)++; // 비교 횟수 증가
        int mid = low + (high - low) / 2;
        if(array[mid] == key) {
            return mid; // 찾은 위치 반환
        }
        if(array[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // 찾지 못함 (실제로는 항상 찾는 값이므로 도달하지 않음)
}

// 4. 보간 탐색 함수
// - 정렬된 배열에서 키를 찾고, 비교 횟수를 기록합니다.
// - 보간 공식 사용
int interpolationSearch(int *array, int size, int key, int *compareCount) {
    int low = 0, high = size - 1;

    while(low <= high && key >= array[low] && key <= array[high]) {
        (*compareCount)++; // 비교 횟수 증가

        if(array[high] == array[low]) {
            if(array[low] == key)
                return low;
            else
                break;
        }

        // 보간 공식 (정수 연산으로 변경)
        int pos = low + ((long)(high - low) * (key - array[low])) / (array[high] - array[low]);

        // 배열 범위를 벗어나지 않도록 확인
        if(pos < low || pos > high)
            break;

        if(array[pos] == key) {
            return pos;
        }
        if(array[pos] < key) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    return -1; // 찾지 못함 (실제로는 항상 찾는 값이므로 도달하지 않음)
}

// 5. 이진 탐색 평균 비교 횟수 계산 함수
// - 여러 번의 탐색을 통해 평균 비교 횟수를 계산합니다.
float getAverageBinarySearchCompareCount(int *array) {
    int totalCompareCount = 0;
    for(int i = 0; i < SEARCH_COUNT; i++) {
        int target = array[rand() % SIZE]; // 항상 존재하는 데이터 선택
        int compareCount = 0;
        binarySearch(array, SIZE, target, &compareCount);
        totalCompareCount += compareCount;
    }
    return (float)totalCompareCount / SEARCH_COUNT;
}

// 6. 보간 탐색 평균 비교 횟수 계산 함수
// - 여러 번의 탐색을 통해 평균 비교 횟수를 계산합니다.
float getAverageInterpolationSearchCompareCount(int *array) {
    int totalCompareCount = 0;
    for(int i = 0; i < SEARCH_COUNT; i++) {
        int target = array[rand() % SIZE]; // 항상 존재하는 데이터 선택
        int compareCount = 0;
        interpolationSearch(array, SIZE, target, &compareCount);
        totalCompareCount += compareCount;
    }
    return (float)totalCompareCount / SEARCH_COUNT;
}

// 메인 함수
int main(int argc, char *argv[]) {
    srand(time(NULL)); // 랜덤 시드 초기화
    int array[SIZE];
    
    // 1. 랜덤 배열 생성
    generateRandomArray(array);
    
    // 2. 퀵 정렬 수행 (최적화된 버전)
    QuickSort(array, 0, SIZE - 1);
    
    // 배열의 처음 20개와 마지막 20개 출력
    printArray(array);
    
    // 3. 이진 탐색 평균 비교 횟수 계산 및 출력
    printf("Average Compare Count of Binary Search: %.2f\n",
           getAverageBinarySearchCompareCount(array));
    
    // 4. 보간 탐색 평균 비교 횟수 계산 및 출력
    printf("Average Compare Count of Interpolation Search: %.2f\n",
           getAverageInterpolationSearchCompareCount(array));
    
    return 0;
}