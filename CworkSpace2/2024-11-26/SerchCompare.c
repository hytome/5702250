#include <stdio.h>

#define SIZE 10

int list[SIZE] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

int search_binary2(int key, int low, int high, int *count) {
    int middle;
    while (low <= high) {
        (*count)++; 
        middle = (low + high) / 2;
        if (key == list[middle]) return middle;
        else if (key > list[middle]) low = middle + 1;
        else high = middle - 1;
    }
    return -1;
}

int search_sequential(int key, int *count) {
    for (int i = 0; i < SIZE; i++) {
        (*count)++; // 비교 횟수 증가
        if (list[i] == key) {
            return i;
        }
    }
    return -1;
}

int main() {
    int key = 7;
    int result;
    int binary_count = 0;
    int sequential_count = 0;

    
    result = search_sequential(key, &sequential_count);
    if (result != -1) {
        printf("순차 탐색: 키 %d는 인덱스 %d에 있습니다. (비교 횟수: %d)\n", key, result, sequential_count);
    } else {
        printf("순차 탐색: 키 %d를 찾을 수 없습니다. (비교 횟수: %d)\n", key, sequential_count);
    }

    
    result = search_binary2(key, 0, SIZE - 1, &binary_count);
    if (result != -1) {
        printf("이진 탐색: 키 %d는 인덱스 %d에 있습니다. (비교 횟수: %d)\n", key, result, binary_count);
    } else {
        printf("이진 탐색: 키 %d를 찾을 수 없습니다. (비교 횟수: %d)\n", key, binary_count);
    }

    return 0;
}