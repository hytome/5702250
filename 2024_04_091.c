#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef int element;
element stack[MAX_STACK_SIZE];//1차원 배열 
int top = -1; //가장 위의 원소를 가리킬 top변수. 
//초기값은 비어있어야 하니 -1.

//공백상태:empty검출 함수.
int is_empty(){
    return (top == -1);
    printf("stack is empty\n");
}
//full:스택의 오버플로우를 방지하기 위한 함수. 포화상태 검출 .
int is_full(){
    return (top == (MAX_STACK_SIZE -1));
}   
//삽입 함수.
void push(element item){
    if(is_full()){
        fprintf(stderr,"스택 포화 에러!\n"); 
        //이걸 측정하기 위한 is_full;
        return;
    }else stack[++top] = item;
    
}

element pop(){
    //pop:쌓인 스텍값을 방출(삭제하는 함수.)
    if(is_empty()){
        fprintf(stderr,"스택 공백 에러\n");
        exit(1);
    } else return stack[top--];
}

element peek(){  
    //peek= 삭제는 하지 않고 보기만 하는 연산.
    if(is_empty()){
        fprintf(stderr,"스택 공백 에러\n");
        exit(1);
    } else return stack[top];
}

int main(){
    push(1);
    push(2);
    push(3);
    printf("%d\n",pop());
    printf("%d\n",pop());
    printf("%d\n",pop());

    return 0;
}