#include <stdio.h>
#include <time.h>


double power_iter(double a, double b){
    //재곱값을 계산하기 위한 반복문 (for)문 방식.
    double result= 1; //결과값 저장을 위해 선언.  
    for(int i=0; i<b; i++){
        result = result *a;
        //result 값에 a를 곱하는걸 b까지 반복. 그리고 그합을 계속 result에 저장.
    }
    return result;
    //그리고 result 반환.
}

double power_rec(double a, double b){
    double result_rec = 1;
    if(b == 0){ //b가 0일경우. 
        return 1;//더이상 제곱할 값이 없으니 1반환.
    }else{
        return result_rec = a * power_rec(a,b-1);
        //재귀로 호출 rec(13,21)...rec(13,20)...이렇게 
        //a*Power_rec(13,21)...(13,20)..
        //result_rec에 값 넣고 반환.

    }
} 


int main(){
    clock_t start_iter,stop_iter; //for문으로 돌리는 반복문의 실행시간 측정.
    clock_t start_rec,stop_rec; //재귀함수로 돌리는 함수의 실행시간 측정.
    
    double time_iter; //for문으로 돌리는 반복문의 실행시간을 저장할곳.
    double time_rec;  //재귀함수로 돌리는 함수의 실행시간을 저장할곳.

    start_iter = clock(); //for문으로 돌리는 반복문의 실행시간 측정 시작.
    double result_iter = power_iter(13,21); //for문으로 돌아가는 함수에 13과 21의 값 삽입
    printf("Power Interative result: %f\n",result_iter); //그 결과 출력.
    stop_iter = clock();//for문으로 돌리는 반복문의 실행시간 측정 종료.
    time_iter =(double)(stop_iter-start_iter)/CLOCKS_PER_SEC; //time_iter에 실행시간 측정과 종료를 초로 바꾸어 계산후 저장. 
    printf("Time: %f\n",time_iter); //계산한 실행시간을 출력.

    start_rec = clock(); //재귀함수 로 돌아가는 함수의 실행시간 측정 시작.
    double result_rec = power_rec(13,21); //재귀 함수로 돌아가는 함수에 13과 21의 값 삽입.
    printf("Power Recursive result:  %f \n",result_rec);
    stop_rec = clock(); //재귀함수 로 돌아가는 함수의 실행시간 측정 종료.
    time_rec = (double)(stop_rec-start_rec)/CLOCKS_PER_SEC;
    printf("Time: %f \n",time_rec);




    return 0;
}