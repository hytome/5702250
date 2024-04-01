#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) (((a)>(b))?(a):(b))
//a와 b값을 비교하기위한 메크로 함수. Q:a와 b중 누가더큰가?
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
}polynomial;

polynomial poly_add1(polynomial A, polynomial B) {
	polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;    
	C.degree = MAX(A.degree, B.degree);
    //앞서 선언한 메크로 함수를 c.dgree에.

	while (Apos <= A.degree && Bpos <= B.degree) {
        //apos,bpos애들이 앞서 선언한 a.dgree, b.dgree에 도달할떄 까지 돌아갈 
        //while 문.
		if (degree_a > degree_b) {
            //a가 더 클경우.
			C.coef[Cpos++] = A.coef[Apos++];
            //c와 a값을 각자 증가. ++
			degree_a--;
            //degree a값을 감소.
		}
		else if (degree_a == degree_b) {
            //a와 b의 두값이 같을경우.
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--;degree_b--;
		}
		else {
            //b값이 더 큰경우.
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
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
	polynomial a = { 5,{3,6,0,0,0,10} };//a가 총  5개니까.
	polynomial b = { 4,{7,0,5,0,1} }; //b가 총 4개니까.
	polynomial c;

	print_poly(a);
	print_poly(b);
	c = poly_add1(a, b);
	printf("-----------------------------------------------------\n");
	print_poly(c);

	return 0;
}