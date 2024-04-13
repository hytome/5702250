#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 5

typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

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
        fprintf(stderr,"stack is full!\n"); 
        //이걸 측정하기 위한 is_full;
        return;
    }else stack[++top] = item;
    
}

element pop(){
    //pop:쌓인 스텍값을 방출(삭제하는 함수.)
    if(is_empty()){
        fprintf(stderr,"stack is empty\n");
        return -1;
    } else return stack[top--];
}

element peek(){  
    //peek= 삭제는 하지 않고 보기만 하는 연산.
    if(is_empty()){
        fprintf(stderr,"stack is empty\n");
        exit(1);
    } else return stack[top];
}
void printf_stack(){
    if(is_empty()){
        printf("Stack is empty\n");
        return;
    }
    printf("stack elements : ");
    for(int i=0; i<= top; i++){
        printf("%d ",stack[i]);
    }
    printf("\n");
}
int main(){
    srand(time(NULL));
    for (int i=0; i<=30; i++){
        int rand_num = rand() %100+ 1;
        int data;
        printf("curent rand num:%d \n",rand_num);
    
            if((rand_num%2)==0){
                push(rand_num);
                printf("push:%d\n",rand_num);
                printf_stack();

            }else{
                printf("pop:%d\n",rand_num);
                printf_stack();
                data=pop();

            
                

    }
    }



}