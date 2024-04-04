#include <stdio.h>

void swap(int *px, int * py){ //서로 서로 값 바꾸는 기능을 가능하게 하는 함수.
    int tmp; //서로의 값을 바꾸게 하기 위한 빈공간.
    tmp = *px; //tmp에 px의 주소값을 지정.  
    //1.먼저 tmp의 공간에 px의 값을 넣는다.
    *px = *py; //px의 주소 값에 py의 주소 값을 지정.
    //2.그다음 px의 주소에 py값을 넣는다.
    *py = tmp; //*py의 주소값에. tmp를 지정.
    //3.마지막으로 px의 값이 들어가 있는 tmp의 위치에 py의 포인터를 지정시킨다.
    //이렇게 되면 빈공간 tmp를 이용하여 px와 py의 값을 서로 바꿀수 있다.

}
int main(){
    int a=1;
    int b=2;

    printf("swap before: a=%d b=%d \n",a,b);
    //swap을 호출하기전. 
    swap(&a,&b);
    //여기서 중요한건 a와 b의 값을 넣은게 아니다!!! 
    //a와 b의 주소 값을 포인터로 지정 가르키는 거다!!!
    printf("swap 호출 후 : a=%d ,b=%d\n",a,b);
    return 0;
}