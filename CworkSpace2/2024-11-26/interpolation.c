#include <stdio.h>

// 보간 탐색 함수
int interpolation_search(int data[], int size, int key) {
    int low = 0, high = size - 1;

    while (low <= high && key >= data[low] && key <= data[high]) {
        // 1. 보간 위치 계산
        int pos = low + ((key - data[low]) * (high - low)) / (data[high] - data[low]);

        // 2. 계산된 위치의 값과 키 비교
        if (data[pos] == key) {
            return pos;  // 키를 발견
        }
        // 3. 키가 더 크면 오른쪽 부분 탐색
        else if (data[pos] < key) {
            low = pos + 1;
        }
        // 4. 키가 더 작으면 왼쪽 부분 탐색
        else {
            high = pos - 1;
        }
    }

    // 탐색 실패
    return -1;
}

// 테스트용 메인 함수
int main() {
    // 데이터 배열 정의
    int data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int size = sizeof(data) / sizeof(data[0]);
    int key = 50;

    // 보간 탐색 수행
    int result = interpolation_search(data, size, key);

    // 결과 출력
    if (result != -1) {
        printf("Key %d found at index %d.\n", key, result);
    } else {
        printf("Key %d not found.\n", key);
    }

    return 0;
}
