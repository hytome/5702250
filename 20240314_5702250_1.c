#include <stdio.h>
#include <time.h>
int main(){
    clock_t start,stop;//time 헤더 파일을 사용하여 clock start,stop.
    //시작과 종료를 선언하기 위한 기능.
    double duration; //수행시간을 계산하기 위한 기능을 위해 double 선언.
    start = clock();  
    //시간 측정 시작.
   int result = 0; //소수의 합을 저장하기 위한 기능.
   int i = 0, j = 0;   
    
   for(i = 2; i <= 100; i++){ //먼저 i가 2부터100 까지 돌아갈 for문 
   
      for(j = 2; j < i; j++){  // 그다음 j가 i-1까지 (=가 없으니까!) 돌아갈 for문 
         if(i % j == 0)        //만약 i와 j의 나눈후 나머지 값이 0이면.
            break;             //멈춘다. (break.)(이러면 j로 돌아가는 for문이 종료된다.)
            //ex)5일경우에 2,,3,,4로 나누는것.
      }
      if(i == j) {//그렇게 앞쪽 for문(j로 돌아가는거)에서 나온후 i와 j의 값이 같을경우 소수니까.
      //ex)i=5,j=5;
         printf("%d ",i); // i의 값을 출력하고. 

         result += i; // 그 i 값을 소수의 합에 저장할 기능인 result에 넣어간다.
      }   
      
   }
   printf("\n");
   stop = clock();
   //for 문 종료후 clock stop.
   duration = (double)(stop-start)/CLOCKS_PER_SEC;
   //초 단위로 변환.
    

   printf("수행시간은 %f 초 입니다.\n",duration);
   
   printf("\n 1부터 100까지의 소수의 합은 %d 입니다.", result ); //for(i로 돌아가는것) 마저 빠져나온후 
   //100까지의 소수의 합을 출력한다.
   printf("\n");    

   return 0;
}