#define MAX_TERMS 101
#include <stdio.h>
#include <stdlib.h> 
//차곡차곡 쌓는 방식.
struct {
    float coef; // 계수
    int expon; // 지수(차수)
} terms[MAX_TERMS] = {
    { 7.0, 6 }, { 5.0, 2 }, { 9.0, 3 }, { 1.0, 0 },
    { 5.0, 3 }, { 2.0, 1 }, { 1.0, 0 }, {10.0 0}
};


void poly_multiply(int As, int Ae, int Bs, int Be, int* Cs, int* Ce)
{
    /*
    배열의 영역
    - 입력 데이터 영역      - 0~6
    - 다항식 계산 결과 영역 - 7~18
    - 지수 종류 딕셔너리?   - 19 ~ 19+x X= 지수의 개수
    - 실제 계산 출력 영역   - 19 + x ~ 19 + 2x
    */


    int calcOffset = 0;        // 다항식 
    int Ac = Ae - As + 1;    // A 항의 개수, 3 - 0 + 1 = 4
    int Bc = Be - Bs + 1;    // B 항의 개수, 6 - 4 + 1 = 3

    // 다항식 계산 영역 calcOffset 계산
    if (Ae < Be) {
        calcOffset = Be + 1;
    }
    else {
        calcOffset = Ae + 1;
    }

    // 다항식 계산 처리
    int count = 0;
    for (int i = As; i <= Ae; i++) {
        for (int j = Bs; j <= Be; j++) {
            int currentIndex = calcOffset + count;
            terms[currentIndex].coef = terms[i].coef * terms[j].coef;
            terms[currentIndex].expon = terms[i].expon + terms[j].expon;

            count++;
        }
    }

    // 다항식 계산 영역을 순회하면서 지수의 종류를 저장
    int calcCount = Ac * Bc;
    int exponOffset = calcOffset + calcCount;
    for (int i = 0; i < calcCount; i++) {
        AddExpon(exponOffset, exponOffset + calcCount, terms[calcOffset + i].expon);
    }

    // 지수 정렬
    BubbleSort(terms, exponOffset, exponOffset + calcCount);

    // 마지막 지수 Index 찾기
    int printOffset = exponOffset + calcCount;
    for (int i = exponOffset; i <= exponOffset + calcCount; i++) {
        if (terms[i].expon == 0) {
            printOffset = i + 1;
            break;
        }
    }

    // 지수 개수를 구하고, 지수마다 계수의 합을 구한다.
    int exponCount = printOffset - exponOffset;
    count = 0;
    for (int i = exponOffset; i <= exponOffset + exponCount; i++) {
        // 결과 위치에 지수 저장
        int currentPrintIndex = printOffset + count;
        terms[currentPrintIndex].expon = terms[i].expon;

        for (int j = calcOffset; j <= calcOffset + calcCount; j++) {
            // 지수가 같다면 계수를 합합니다.
            if (terms[currentPrintIndex].expon == terms[j].expon) {
                terms[currentPrintIndex].coef += terms[j].coef;
            }
        }

        count++;
    }

    // 결과 Offset 저장
    *Cs = printOffset;
    *Ce = printOffset + exponCount - 1;
}

int AddExpon(int Es, int Ee, int expon) {
    // expon의 기본값이 0이므로 무시
    if (expon <= 0) {
        return;
    }

    // 0보다 큰 경우: 중복 체크 후 없으면 마지막 위치에 추가함.
    int found = 0;
    int lastIndex = Ee;

    for (int i = Es; i <= Ee; i++) {
        if (terms[i].expon == expon) {
            found = 1;
        }

        // lastIndex가 초기 값이면서 지수 영역에 정의하지 않은 첫 위치면 lastIndex
        if (lastIndex == Ee && terms[i].expon == 0) {
            lastIndex = i;
        }
    }

    if (found == 0) {
        terms[lastIndex].expon = expon;
    }
}

int BubbleSort(int arr[], int start, int end) { //버블정렬.
    int i, j, temp;
    for (i = start; i < end; i++) {
        for (j = start; j < end - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print_poly(int s, int e)
{
    for (int i = s; i < e; i++)
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
    printf("%3.1fx^%d\n", terms[e].coef, terms[e].expon); //마지막 상수항 출력
}

int main() {
    int As = 0, Ae = 3, Bs = 4, Be = 7, Cs, Ce;
    poly_multiply(As, Ae, Bs, Be, &Cs, &Ce);
    print_poly(As, Ae);
    print_poly(Bs, Be);
    printf("----------------------------------------------------------------------------- \n");
    print_poly(Cs, Ce);
}