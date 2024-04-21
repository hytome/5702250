#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int top;
    int *arr; 
    int capacity; 
} Stack;

void initStack(Stack *s, int capacity) {
    s->top = -1;
    s->capacity = capacity;
    s->arr = (int*)malloc(capacity * sizeof(int)); 
    if (s->arr == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == s->capacity - 1;
}

void push(Stack *s, int element) {
    if (isFull(s)) {
        printf("스택이 가득 차버렸숩니다 \n");
        return;
    }
    s->arr[++s->top] = element;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("스택 이 텅텅 비었숩니다. \n");
        return -1;
    }
    return s->arr[s->top--];
}

void freeStack(Stack *s) {
    free(s->arr); // 동적 할당된 메모리 해제
}

int operate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int evaluatePostfix(char* expression) {
    Stack s;
    initStack(&s, 100); 
    int i, a, b;

    for (i = 0; expression[i]; ++i) {
        if (expression[i] == ' ' || expression[i] == '\t')
            continue;

        else if (isdigit(expression[i])) {
            int num = 0;
            while (isdigit(expression[i])) {
                num = num * 10 + (int)(expression[i] - '0');
                i++;
            }
            i--;
            push(&s, num);
        }
        else {
            b = pop(&s);
            a = pop(&s);
            push(&s, operate(a, b, expression[i]));
        }
    }
    int result = pop(&s);
    freeStack(&s); 
    return result;
}

int main() {
    char expression[100];
    printf("postfix Expression: ");
    fgets(expression, 100, stdin);
    expression[strcspn(expression, "\n")] = 0; 

    printf("result: %d\n", evaluatePostfix(expression));
    return 0;
}