#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
 
#define MAX_STACK_SIZE 10

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
void init(StackType* sptr, int ofs) {
	sptr->data = (element *)malloc(sizeof(StackType) * ofs);
	sptr->top = -1;
	sptr->capacity = ofs;
}

// is_full
int is_full( StackType *sptr) {
	if (sptr->top == sptr->capacity - 1) {
		sptr->capacity = sptr->capacity * 2;
		sptr->data = (element*)realloc(sptr->data, sptr->capacity * sizeof(element));
	}
}

int is_empty(StackType *sptr) {
	return (sptr->top == -1);
}

// push
void push(StackType *sptr, element item) {

	if (is_full(sptr)) {
		fprintf(stderr, "Stack is full\n");
		return;
	}
	else {
		sptr->top = sptr->top + 1;
		sptr->data[sptr->top] = item;
	}
}

element pop(StackType *sptr) {
	element r;
	if (is_empty(sptr)) {
		fprintf(stderr, "stack is empty\n");
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
		fprintf(stderr, "stack is empty\n");
		return -1;
	}
	else {
		// r = stack[top];
		// top = top - 1;
		// return r;
		return (sptr->data[sptr->top]);
	}
}

int main() {

	StackType s;
	int rand_num;
	int numOfStack;

	srand(time(NULL));

	printf("How many element Stack has?");
	scanf("%d", &numOfStack,4);

	init(&s, numOfStack);
    for(int i=0; i<=30; i++){
	rand_num = rand() % 100 + 1 ;
	printf("%d \n", rand_num);
	if (rand_num % 2 == 0) {
		push(&s, rand_num);
		printf("Push Stack S %d\n", rand_num);
	}
	else {
			rand_num = pop(&s);
			printf("Pop Stack S %d\n", rand_num);
	}

	

}

return 0;
}