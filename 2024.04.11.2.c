#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_STACK_SIZE 5 //스택 사이즈  설정.
//배열을 동적 메모리 할당으로 지정해 스택 프로그램을 짜보자. 
typedef int element;
typedef struct {
    element *data; //data는 포인터로 정의 된다.
    int capacity; //현재 스택의 크기. 
    int top;
}StackType; //stackType 구조체.

//스택 생성 함수. 
//배열의 시작점 주소를 가져와 계산을 하는게 훨씬 더 좋은 프로그램이기에.
//포인터를 사용한다 에요.
void inin_stack(StackType * s){
    s->top=-1; //스택의 top 값 .초기화 해야하니 -1.
    s->capacity =  1; //현재 스택의 크기.
    s->data = (element *) malloc(s->capacity * sizeof(element));

   
}

//공백 상태 검출 함수
int is_empty(StackType *s){
    //공백 상태일 경우 top의 -1;
    return (s -> top == -1 );
}

//포화 상태 검출 함수.
int is_full(StackType *s){
    //포화 상태일시 스택의 크기를 -1 
    return (s->top==(s->capacity -1));
}
 //이제 푸쉬 함수를 구현해 보자에요. 
void push(StackType *s, element item){
    if(is_full(s)){ //포화 상태인 경우.
        s->capacity *=2; 
        //공간이 부족한 경우 메모리를 두배로 뻥튀기.
        s->data = (element *)realloc(s->data,s->capacity * sizeof(element));
        //relloc로 현재 내용은 유지하면서 주어진 크기로 동적 메모리를 다시 할당한다.
    } //포화상태가 아닐경우 
    s->data[++(s->top)]=item;
}
//이제 스택에서 삭제를 하는 pop함수를 구현해 보자에요.
element pop(StackType *s){
    
    if(is_empty(s)){
        //텅 비었을 경우.
        fprintf(stderr,"스택이 텅비었습니다. \n");
        return -1; //프로그램 종료.
        }else{
           
            return s->data[(s->top)--];
            //텅 비지 않았을경우 top으로 선입 후출.
        }
    }


    void printf_stack(StackType * s){
    if(is_empty(s)){
        printf("Stack is empty\n");
        return;
    }else{ 
		printf("stack elements: ");
		for(int i=0; i<=s->top ; i++){
        printf("%d ",s->data[i]);
    }
    printf("\n");
}
}
int main(){
    StackType s;
    
    inin_stack(&s); //주소값으로 설정
    int rand_num;
    
    srand(time(NULL));
    
    for(int i=0; i<=30; i++){
	    rand_num = rand() % 100 + 1 ;
	    printf("current _rand_num: %d \n", rand_num);
	    if (rand_num % 2 == 0) {
		    push(&s, rand_num);
		    printf("Push Stack S %d\n", rand_num);
            printf_stack(&s);
	    }else {
                printf("Pop Stack S %d\n", rand_num);
                printf_stack(&s);
                rand_num = pop(&s);
			   
	}
         
}
return 0;
}