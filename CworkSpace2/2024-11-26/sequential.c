#include <stdio.h>

// 색인 순차 탐색 함수
int indexed_sequential_search(int data[], int index[], int dataSize, int indexSize, int key) {
    int i, start, end;

    // 1. 색인 테이블 탐색: 키가 속한 구간 찾기
    for (i = 0; i < indexSize; i++) {
        if (key <= data[index[i]]) {  // 색인 테이블의 값과 비교
            break;
        }
    }

    // 2. 키가 색인 범위 내에 없는 경우
    if (i == 0) {
        start = 0;
    } else if (i == indexSize) {
        printf("Key not found (out of range).\n");
        return -1;
    } else {
        start = index[i - 1];
    }
    end = index[i];

    // 3. 해당 구간에서 순차 탐색
    for (int j = start; j <= end; j++) {
        if (data[j] == key) {  // 키를 발견
            return j;
        }
    }

    // 4. 탐색 실패
    printf("Key not found.\n");
    return -1;
}

// 테스트용 메인 함수
int main() {
    // 데이터 배열과 색인 테이블 정의
    int data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int index[] = {0, 3, 6, 8};  // 0~3, 4~6, 7~8 범위 구분
    int dataSize = sizeof(data) / sizeof(data[0]);
    int indexSize = sizeof(index) / sizeof(index[0]);
    int key = 50;

    // 색인 순차 탐색 수행
    int result = indexed_sequential_search(data, index, dataSize, indexSize, key);

    // 결과 출력
    if (result != -1) {
        printf("Key %d found at index %d.\n", key, result);
    }

    return 0;
}
