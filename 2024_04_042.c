#include <stdio.h>
//배열의 포인터. 배열을 만약 포인터로 지정시키면 어떻게 작동할까?
//바로 배열의 가장 첫번쨰 값을 포인터로 지정할수 있게된다. 그점을 이용하여 
//배열의 값을 더하는 코드를 짜보자에요.

#define SIZE 6 
//배열수 쉽게 지정할수 있는 메크로.
//int sumOfArray(int *sptr , int *eptr){
 //int sum = 0 
 //while(sptr<=eptr){ sum= sum+(*sptr); sptr ++;}
 //또다른 방법 while문. 1.
 //배열의 시작과 끝이 같아질떄 까지 sum에 값을 ++ 이러면 배열의 총 합값이 sum에 저장.
 //for (int i = 0; (sptr+ i) <= eptr; i++)
 //또다른 방법 for문 2.
 //sum = sum+sptr[i];
 
//}

void get_intergers(int list[]){
    //배열의 값을 입력받고 저장한 값을 반환하는 기능이다에요~
    printf("6개의 정수를 입력하세요: ");
    for(int i=0;  i< SIZE; ++i){
        scanf("%d",&list[i]);
    }
}

int cal_sum(int list[]){ //배열의 지정된 값을 모두 더하기 위한 기능.
    int sum = 0; //배열의 모든 요소를 합칠값.
    for(int i=0; i<SIZE; ++i){
        sum+= *(list +i); //sum에 배열 요소를 하나씩 더해가는 요소.
        //*:포인터.
    }
    return sum; //그리고 sum을 반환.
}

int main(){
    //int iptr;
    //int iptr = *iarray;
    //iarray[20]=......
    int list[SIZE]; //배열의 길이를 앞서 선언한 메크로로 6으로 만듬.
    get_intergers(list);
    printf("합: %d\n",cal_sum(list));
  //printf("sumof iarray = %d\n",sumOfArray(iarray,iarray+19));
    return 0;
    //for(iptr = &iArray[0]; iptr<= &iArray[19]; iptr++)
    //또다른 for문 방식. 포인터로 지정해 가져와서. 주소값으로.
    //sum = sum+(*iptr);
}