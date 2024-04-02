#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) (((a)>(b))?(a):(b))
//a와 b값을 비교하기위한 메크로 함수. Q:a와 b중 누가더큰가?
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
}polynomial;

polynomial poly_mult1(polynomial A, polynomial B) {
	polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;    
	C.degree = MAX(A.degree, B.degree);
    //앞서 선언한 메크로 함수를 c.dgree에. 누가 더 큰지 비교.
    int i,j; //for문 용. i,j.
    C.degree=A.degree+B.degree; 
    for(i = 0; i < MAX_DEGREE; i++){
      C.coef[i] = 0;
   }
    for(i=0;i<=degree_a;i++){
        for(j=0; j<=degree_b;j++){
            C.coef[i+j]+=A.coef[i]*B.coef[j]; //각자 배열의 곱한 값을 
			//c.coef에 저장.
    }
    }
 return C;
    }

void print_poly(polynomial p) {
	for (int i = p.degree;i > 0;i--)
		printf("%3.1f x^%d + ", p.coef[p.degree - i], i);
	printf("%3.1f \n", p.coef[p.degree]);
}

int main(void) {
	// 구조체 배열을 미리 선언
	polynomial a = { 6,{7,0,0,5,9,0,1} };
	polynomial b = { 3,{5,2,1,10} }; 
	polynomial c;

	print_poly(a);
	print_poly(b);
	c = poly_mult1(a, b);
	printf("-----------------------------------------------------\n");
	print_poly(c);

	return 0;
}