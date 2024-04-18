#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int top;
    unsigned capacity;
    char* array; // 스택의 배열을 char 타입으로 변경
} Stack;

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*) malloc(stack->capacity * sizeof(char)); // char 타입으로 메모리 할당
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char item) { // item 타입을 char로 변경
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

char pop(Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

char peek(Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top];
}

int isOperand(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); // 숫자도 피연산자로 처리
}

int Prec(char ch) {
    switch (ch) {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }
    return -1;
}

int infixToPostfix(char* exp) {
    int i, k;
    Stack* stack = createStack(strlen(exp));
    if(!stack)
        return -1;

    for (i = 0, k = -1; exp[i]; ++i) {
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
        else if (exp[i] == '(')
            push(stack, exp[i]);
        else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1;
            else
                pop(stack);
        } else {
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
    }

    while (!isEmpty(stack))
        exp[++k] = pop(stack);

    exp[++k] = pop(stack);

    exp[++k] = '\0'; // 문자열의 끝을 나타내는 널 문자 추가
    printf("%s", exp);
    free(stack->array);
    free(stack);
    return 0;
}

int main() {
    char exp[] = "(2+3)*4+9";
    printf("중위 표기법: %s\n", exp);
    printf("후위 표기법: ");
    infixToPostfix(exp);
    return 0;
}