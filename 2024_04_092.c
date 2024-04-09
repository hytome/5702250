#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_STACK_SIZE 5;

typedef 

int main(){
    StackType EvenStack;
    StackType Oddstack; initi_stack(&EvenStack);
    init_stack(&0ddStack);
    int i = 0;
    int number = 0;
    srand( (unsigned) time (NULL)) ;
    while (i<10){
        number = rand() % 100;
        if(number % 2 == 0){
            push&EvenStack; number);
        }else{
            push&OddStack, number);
        }
            i++;}
    printstack(&EvenStack);
    printstack(&0ddStack);
}