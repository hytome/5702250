#include <stdio.h>

#define SIZE 10

int list[SIZE] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

int search_binary2(int key, int low, int high) {
    int middle;
    while (low <= high) { 
        middle = (low + high) / 2;
        if (key == list[middle]) return middle; 
        else if (key > list[middle]) low = middle + 1; 
        else high = middle - 1; 
    }
    return -1; 
}

int search_sequential(int key) {
    for (int i = 0; i < SIZE; i++) {
        if (list[i] == key) {
            return i; 
        }
    }
    return -1; 
}

int main() {
    int key = 7;
    int result;

    // 순차 탐색
    result = search_sequential(key);
    if (result != -1) {
        printf("순차 탐색: 키 %d는 인덱스 %d에 있습니다.\n", key, result);
    } else {
        printf("순차 탐색: 키 %d를 찾을 수 없습니다.\n", key);
    }

    // 이진 탐색
    result = search_binary2(key, 0, SIZE - 1);
    if (result != -1) {
        printf("이진 탐색: 키 %d는 인덱스 %d에 있습니다.\n", key, result);
    } else {
        printf("이진 탐색: 키 %d를 찾을 수 없습니다.\n", key);
    }

    return 0;
}