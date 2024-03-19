#include <stdio.h>
#include <time.h>
//20! 의 팩토리얼을 구하기 과제. 

long factorial_rec(long n){ //20의 팩토리얼 값은 int의 값을 넘는다.
    
    //따라서 long으로 선언한다. long으로 팩토리얼을 계산하기 위한 재귀함수.
    if (n <= 1) return 1;
        else return n * factorial_rec(n-1);//이렇게 함수내에서 또 함수를 호출한다. 이것이 재귀함수다.
        //팩토리얼은 5!= 5*4*3*2*1 이니 n-1로 연산을 하면된다. 
    
}
long factorial_iter(long n){ 
    //팩토리얼을 구하기 위한 for문. 
    long result = 1; //20팩토리얼은 int의 값을 넘으니 long으로 선언한다.
    for(int i=1; i<=n; i++){
        result  *=i; //long으로 선언한 result에 20까지 늘어나는 i값을 곱하여 저장.
    }
    
    return result; //그리고 result 값을 반환한다.
    
    
}



int main(){
    clock_t start_iter,stop_iter; //각자 실행 시간을 재기위한 clock.
    //iter=for문 용.
    double duration_iter; //실행시간을 계산하기위한 (for문용 )duration.
    double duration_rec; //실행시간을 계산하기 위한 (재귀함수 용)duration.
    clock_t start_rec,stop_rec;
    //rec= 재귀함수용.
    start_iter = clock();
    //for문의 실행시간 측정시작.
    //for문에 20 값 넣기.
    long result_iter = factorial_iter(20);
    start_rec = clock();
    //재귀 함수 문의 실행시간 측정 시작.
    //재귀 함수에 20 값 넣기.
    long result_rec=factorial_rec(20);
    printf("Factorial Interative result: %ld\n",result_iter);
    //팩토리얼의 결과값(for)문 출력.
    stop_iter = clock();//for문 실행시간 측정 종료.
    duration_iter= (double)(stop_iter-start_iter)/CLOCKS_PER_SEC; //실행시간 계산문.
    printf("time %f.\n",duration_iter);//for문 실행시간 출력.
    printf("Factorial Recursive result:%ld\n",result_rec);
    //재귀함수 결과 출력.
    stop_rec = clock(); //재귀함수문 실행시간 종료.문
    duration_rec = (double)(stop_rec-start_rec)/CLOCKS_PER_SEC; //실행시간 계산문.
    printf("time %f.\n",duration_rec); //재귀함수의 실행시간 출력.
    
    
    

    
    
    




    return 0;
}