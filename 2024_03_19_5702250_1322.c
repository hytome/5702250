#include <stdio.h>
#include <time.h>


long power_iter(long a, long b){
    //재곱값을 계산하기 위한 반복문 (for)문 방식.
    long result= 1;  
    for(int i=0; i<=b; i++){
        result= result*a;
    }
    return result;
}

long power_rec(long a, long b){
    long result_rec = 1;
    if(b == 0){
        return a; //왜 이값을 0이나 1로하면 값이 이상해지는거지?
        //심지어 13의 21같은 큰값이 아니면 또 제데로 제곱값을 방출한다!
    }else{
        return result_rec = a * power_rec(a,b-1);
    }
} 


int main(){
    clock_t start_iter,stop_iter; //for문으로 돌리는 반복문의 실행시간 측정.
    clock_t start_rec,stop_rec; //재귀함수로 돌리는 함수의 실행시간 측정.
    
    double time_iter; //for문으로 돌리는 반복문의 실행시간을 저장할곳.
    double time_rec;  //재귀함수로 돌리는 함수의 실행시간을 저장할곳.

    start_iter = clock(); //for문으로 돌리는 반복문의 실행시간 측정 시작.
    long result_iter = power_iter(13,21); //for문으로 돌아가는 함수에 13과 21의 값 삽입
    printf("for문으로 계산한 13 21의 제곱값은 %ld입니다. \n",result_iter); //그 결과 출력.
    stop_iter = clock();//for문으로 돌리는 반복문의 실행시간 측정 종료.
    time_iter =(double)(stop_iter-start_iter)/CLOCKS_PER_SEC; //time_iter에 실행시간 측정과 종료를 초로 바꾸어 계산후 저장. 
    printf("측정시간은 %f 입니다.\n",time_iter); //계산한 실행시간을 출력.

    start_rec = clock(); //재귀함수 로 돌아가는 함수의 실행시간 측정 시작.
    long result_rec = power_rec(13,21); //재귀 함수로 돌아가는 함수에 13과 21의 값 삽입.
    printf("재귀함수로 계산한 13 21의 제곱값은 %ld 입니다. \n",result_rec);
    stop_rec = clock(); //재귀함수 로 돌아가는 함수의 실행시간 측정 종료.
    time_rec = (double)(stop_rec-start_rec)/CLOCKS_PER_SEC;
    printf("측정시간은 %f 입니다.",time_rec);




    return 0;
}