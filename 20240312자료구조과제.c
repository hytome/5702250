#include<stdio.h>

int main(){
   int result = 0; //소수의 합을 저장하기 위한 기능.
   int i = 0, j = 0;   

   for(i = 2; i <= 100; i++){ //먼저 i가 2부터100 까지 돌아갈 for문 
      for(j = 2; j < i; j++){  // 그다음 j가 i-1까지 (=가 없으니까!) 돌아갈 for문 
         if(i % j == 0)        //만약 i와 j의 나눈후 나머지 값이 0이면.
            break;             //멈춘다. (break.)(이러면 j로 돌아가는 for문이 종료된다.)
      }
      if(i == j) {//그렇게 앞쪽 for문(j로 돌아가는거)에서 나온후 i와 j의 값이 같을경우 소수니까.
         printf("%d ",i); // i의 값을 출력하고. 

         result += i; // 그 i 값을 소수의 합에 저장할 기능인 result에 넣어간다.
      }   
      
   }
   
   printf("\n 1부터 100까지의 소수의 합은 %d 입니다.", result ); //for(i로 돌아가는것) 마저 빠져나온후 
   //100까지의 소수의 합을 출력한다.
   printf("\n");    

   return 0;
}