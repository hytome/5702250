#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int partition(int *array, int low, int high, int *compareCount);

int quickSort(int *array, int low, int high, int *compareCount) { //퀵 정렬 (일단 재귀로 구현 )
    if (low < high) {
        int pivot = partition(array, low, high, compareCount);
        quickSort(array, low, pivot - 1, compareCount); //가장 작은 곳이랑 가장 큰곳 비교 
        quickSort(array, pivot + 1, high, compareCount);
    }
    return *compareCount;
}

int partition(int *array, int low, int high, int *compareCount) {
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        (*compareCount)++;
        if (array[j] < pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int *array) {
    printf("Array Sorting Result:\n");
    for(int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for(int i = SIZE-20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

//순차 탐색 비교횟수    
float getAverageLinearSearchCompareCount(int *array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int key = rand() % 1000;
        int compareCount = 0;
        int found = 0; 

    
        for (int j = 0; j < SIZE; j++) {
            if (array[j] == key) {
                found = 1;
                break;
            }
        }

        
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
    return (float)totalCompareCount / 100;
}

int getQuickSortCompareCount(int *array) {
    int compareCount = 0;
    quickSort(array, 0, SIZE - 1, &compareCount);
    return compareCount;
}

// 이진 탐색 비교횟수
float getAverageBinarySearchCompareCount(int *array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int key = rand() % 1000;
        int compareCount = 0;
        int found = 0; 

        
        for (int j = 0; j < SIZE; j++) {
            if (array[j] == key) {
                found = 1;
                break;
            }
        }

        
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
    return (float)totalCompareCount / 100;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    printf("Average Linear Search Compare Count: %.2f\n", getAverageLinearSearchCompareCount(array));
    int compareCount = getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);
    printf("Average Binary Search Compare Count: %.2f\n\n", getAverageBinarySearchCompareCount(array));
    printArray(array);
    return 0;
}