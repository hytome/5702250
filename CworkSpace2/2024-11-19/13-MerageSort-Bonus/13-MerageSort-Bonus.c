#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100       // 정렬할 배열의 크기 정의
#define TRIALS 1       // 테스트 반복 횟수 (현재는 1회로 고정)

int is_seeded = 0;     // 난수 초기화 여부를 체크하는 변수

// 랜덤한 숫자로 배열을 초기화하는 함수
void generateRandomNumber(int array[]) {
    if (!is_seeded) {
        srand(time(NULL));  // 현재 시간을 시드로 설정하여 매번 다른 난수 생성
        is_seeded = 1;      // 시드가 한 번만 설정되도록 체크
    }
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999까지의 난수를 배열에 저장
    }
}

// 한 배열의 데이터를 다른 배열에 복사하는 함수
void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];  // 소스 배열의 데이터를 대상 배열에 복사
    }
}

// 배열의 모든 요소를 출력하는 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]);  // 배열의 각 요소를 3자리 정렬로 출력
    }
    printf("\n");  // 출력 후 줄 바꿈
}

// 배열의 일부만 출력하는 함수 (특정 라운드에 호출)
void printPartialArray(int array[], int rounds) {
    if (rounds % 10 == 0) {  // 10번 라운드마다 배열 상태를 출력
        printf("라운드 %d - 배열 상태:\n", rounds);

        // 배열의 처음 10개 요소 출력
        for (int i = 0; i < 10; i++) {
            printf("%3d ", array[i]);
        }
        printf("| ");

        // 배열 중앙 근처의 10개 요소 출력
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) {
            printf("%3d ", array[i]);
        }
        printf("\n\n");  // 두 줄 띄우기
    }
}

// 병합 정렬에서 두 배열을 병합하는 함수
void merge(int array[], int left, int mid, int right, int *comparisons, int *moves, int *rounds) {
    //정복의 시작 부분.
    int n1 = mid - left + 1;  // 왼쪽 부분 배열의 크기 계산 즉 중간 부터 왼쪽 끝까지 왼쪽 배열의 크기.
    int n2 = right - mid;     // 오른쪽 부분 배열의 크기 계산 즉 중간 부터 오른쪽 끝까지 오른쪽 배열의 크기.
    int L[n1], R[n2];         // 임시 배열을 사용해 왼쪽(L)과 오른쪽(R)을 나눔

    // 임시 왼쪽 배열 복사
    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];  // 왼쪽 배열 데이터를 임시 배열 L에 저장
        (*moves)++;             // 이동 횟수 증가
    }
    // 임시 오른쪽 배열 복사
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];  // 오른쪽 배열 데이터를 임시 배열 R에 저장
        (*moves)++;                // 이동 횟수 증가
    }

    // 병합 과정에서 두 배열을 비교하고 정렬
    // 즉 정복 과정
    int i = 0, j = 0, k = left;    // i: L 배열 인덱스, j: R 배열 인덱스, k: 원본 배열 인덱스
    while (i < n1 && j < n2) {
        (*comparisons)++;  // 비교 횟수 증가
        if (L[i] <= R[j]) {
            array[k] = L[i];  // 왼쪽 배열 값이 작으면 원본 배열에 저장
            i++;
        } else {
            array[k] = R[j];  // 오른쪽 배열 값이 작으면 원본 배열에 저장
            j++;
        }
        k++;
        (*moves)++;  // 이동 횟수 증가
    }
     //-결합 과정. 즉 작은 값 부터 병합 처리.
    // 왼쪽 배열에 남은 요소 처리
    while (i < n1) {
        array[k] = L[i];  // L 배열의 남은 요소를 원본 배열에 추가
        i++;
        k++;
        (*moves)++;  // 이동 횟수 증가
    }

    // 오른쪽 배열에 남은 요소 처리
    while (j < n2) {
        array[k] = R[j];  // R 배열의 남은 요소를 원본 배열에 추가
        j++;
        k++;
        (*moves)++;  // 이동 횟수 증가
    }

    (*rounds)++;  // 라운드 수 증가
    printPartialArray(array, *rounds);  // 병합 후 배열 상태 출력
}

// 반복적 병합 정렬을 수행하는 함수
void iterativeMergeSort(int array[], int size, int *comparisons, int *moves, int *rounds) {
    int currentSize;  // 병합할 부분 배열의 크기
    int leftStart;    // 왼쪽 부분 배열의 시작 인덱스

    // 병합 크기를 1에서 시작해 두 배씩 늘려가며 병합
    // 즉 분할 과정. 
    for (currentSize = 1; currentSize <= size - 1; currentSize = 2 * currentSize) {
        // 병합할 두 부분 배열의 시작 위치 설정
        for (leftStart = 0; leftStart < size - 1; leftStart += 2 * currentSize) {
            int mid = leftStart + currentSize - 1;  // 왼쪽 부분 배열의 끝
            // 즉 중간 지점을 찾는 과정.
            int rightEnd = (leftStart + 2 * currentSize - 1 < size - 1) ? 
                           leftStart + 2 * currentSize - 1 : size - 1;  // 오른쪽 부분 배열의 끝

            merge(array, leftStart, mid, rightEnd, comparisons, moves, rounds);  // 병합 수행
        }
    }
}

// 반복적 병합 정렬을 실행하는 함수
void doIterativeMergeSort(int array[]) {
    int comparisons = 0;  // 비교 횟수 초기화
    int moves = 0;        // 이동 횟수 초기화
    int rounds = 0;       // 병합 단계(라운드) 초기화
    int originalArray[SIZE];  // 원본 배열 복사용

    generateRandomNumber(array);  // 랜덤 배열 생성
    copyArray(array, originalArray, SIZE);  // 배열 복사

    printf("정렬이 안된 난수 배열:\n");
    printArray(originalArray, SIZE);  // 원본 배열 출력

    printf("\n반복적 병합 정렬 진행:\n");
    iterativeMergeSort(originalArray, SIZE, &comparisons, &moves, &rounds);  // 병합 정렬 수행

    printf("\n최종 병합 정렬된 배열:\n");
    printArray(originalArray, SIZE);  // 최종 정렬된 배열 출력

    printf("\nTotal Comparisons: %d\n", comparisons);  // 총 비교 횟수 출력
    printf("Total Moves: %d\n", moves);               // 총 이동 횟수 출력
}

// 메인 함수: 프로그램 실행 시작점
int main() {
    int randomData[SIZE];  // 난수 배열 선언

    printf("Iterative Merge Sort Run:\n");
    doIterativeMergeSort(randomData);  // 병합 정렬 실행

    return 0;  // 프로그램 종료
}
