#include <stdio.h>
#include <time.h>
//20! 의 팩토리얼을 구하기 과제. 

long factorial_rec(long n){ //20의 팩토리얼 값은 int의 값을 넘는다.
    
    //따라서 long으로 선언한다. long으로 팩토리얼을 계산하기 위한 재귀함수.
    if (n <= 1) return 1;
        else return n * factorial_rec(n-1);//이렇게 함수내에서 또 함수를 호출한다.
    
}
long factorial_iter(long n){ 
    //팩토리얼을 구하기 위한 for문. 
    long result;
    for(int i=1; i<n; i++){
        result  *=i;
    }
    
    return result;
    
    
}



int main(){
    clock_t start_iter,stop_iter; //각자 실행 시간을 재기위한 clock.
    double duration_iter;
    double duration_rec;
    clock_t start_rec,stop_rec;
    start_iter = clock();
    //for문에 20 값 넣기.
    long result_iter = factorial_iter(20);
    start_rec = clock();
    //재귀 함수에 20 값 넣기.
    long result_rec=factorial_rec(20);
    printf("Factorial Interative result: %ld\n",result_iter);
    stop_iter = clock();//for문 실행시간 종료.
    duration_iter= (double)(stop_iter-start_iter)/CLOCKS_PER_SEC; //실행시간 계산문.
    printf("time %f.\n",duration_iter);
    printf("Factorial Recursive result:%ld\n",result_rec);
    stop_rec = clock(); //재귀함수문 실행시간 종료.문
    duration_rec = (double)(stop_rec-start_rec)/CLOCKS_PER_SEC; //실행시간 계산문.
    printf("time %f.\n",duration_rec);
    
    
    

    
    
    




    return 0;
}
