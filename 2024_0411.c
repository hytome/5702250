#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
 
#define MAX_STACK_SIZE 5

typedef int element;
typedef struct Stacktype {
	// element data[];
	element *data;
	int capacity;
	int top;
} StackType;


// create : 이미 만들었음, StackType의 변수를 선언하면 만들어짐
// delete : 할수 없음

// init 
void init(StackType* sptr) {
	
	sptr->top = -1;
	sptr->data = (element *)malloc(sptr->capacity * sizeof(element));
}

// is_full
int is_full(StackType *sptr) {
	return (sptr->top == sptr->capacity - 1);
}

int is_empty(StackType *sptr) {
	return (sptr->top == -1);
}

// push
void push(StackType *sptr, element item) {

	if (is_full(sptr)) {
        
        sptr->capacity *= 2;
		sptr->data = (element*)realloc(sptr->data, sptr->capacity * sizeof(element));
		
	}
	else {
		sptr->data[++(sptr->top)] = item;
	}
}

element pop(StackType *sptr) {
	element r;
	if (is_empty(sptr)) {
		fprintf(stderr, "스택공백 에러.\n");
		return -1;
	}
	else {
		// r = sptr->stack[sptr->top];
		// sptr->top = sptr->top - 1;
		// return r;
		
		return (sptr->data[(sptr->top)--]);
	}
}

element peek(StackType * sptr) {
	
	element r;
	if (is_empty(sptr)) {
		fprintf(stderr, "stack is empty1\n");
		return -1;
	}
	else {
		// r = stack[top];
		// top = top - 1;
		// return r;
		return (sptr->data[sptr->top]);
	}
}
void printf_stack(StackType * sptr){
    if(is_empty(sptr)){
        printf("Stack is empty\n");
        return;
    }else{ 
		printf("stack elements: ");
		for(int i=1; i<= sptr->top ; i++){
        printf("%d\n",sptr->data[i]);
    }
    printf("\n");
}
}

int main() {

	StackType sptr;
	int rand_num;
	

	srand(time(NULL));

	

	init(&sptr);
    for(int i=0; i<=30; i++){
		rand_num = rand() % 100 + 1 ;
		int data;
		printf("current rand_num:%d \n", rand_num);
			if (rand_num % 2 == 0) {
				push(&sptr, rand_num);
				printf_stack(&sptr);
				printf("Push Stack S %d\n", rand_num);
				
			}
			else {
				printf("pop Stack S %d\n",rand_num);
				printf_stack(&sptr);
				data=pop(&sptr);
			
	}

		

}
 		
return 0;
}