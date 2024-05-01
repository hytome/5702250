#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int top;
    unsigned capacity;
    char* array;
} StackType;

StackType* createStack(unsigned capacity) {
    StackType* stack = (StackType*) malloc(sizeof(StackType));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(StackType* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(StackType* stack) {
    return stack->top == -1;
}

void push(StackType* stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

char pop(StackType* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

char peek(StackType* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top];
}

int isOperand(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
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

void infixToPostfix(char* exp) {
    int i, k;
    StackType* stack = createStack(strlen(exp));
    if(!stack)
        return;

    for (i = 0, k = -1; exp[i]; ++i) {
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
        else if (exp[i] == '(')
            push(stack, exp[i]);
        else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return;
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

    exp[++k] = '\0';
    printf("%s", exp);
    free(stack->array);
    free(stack);
}

int evaluatePostfix(char* exp) {
    StackType* stack = createStack(strlen(exp));
    if (!stack) return -1;

    for (int i = 0; exp[i]; ++i) {
        if (isdigit(exp[i])) {
            push(stack, exp[i] - '0'); // 숫자라면 스택으로 푸시!
        } else {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i]) {
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2 / val1); break;
            }
        }
    }
    return pop(stack); // 최종 pop 결과를 반환.
}

int main() {
    
    int choice;
    char postfixExp[100] = ""; 
    char exp[100] = ""; 
    int result;
    char input[100];
    printf("기능을 선택해 주세요 \n");
    while(1) {
        printf("\n1. 중위 표기 수식 입력\n2. 후위 표기식으로 변환\n3. 수식 계산\n4. 프로그램 종료\n선택: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &choice);

        switch(choice) {
            case 1:
                printf("중위 표기 수식을 입력하세요: ");
                fgets(exp, sizeof(exp), stdin);
                exp[strcspn(exp, "\n")] = 0; // 개행 문자 제거
                printf("중위 표기법: %s\n", exp);
                break;
            case 2:
                if(strlen(exp) == 0) {
                    printf("먼저 중위 표기 수식을 입력해주세요.\n");
                    break;
                }
                strcpy(postfixExp, exp);
                infixToPostfix(postfixExp);
                printf("\n후위 표기법: %s\n", postfixExp);
                break;
            case 3:
                if(strlen(postfixExp) == 0) {
                    printf("먼저 후위 표기식으로 변환해주세요.\n");
                    break;
                }
                result = evaluatePostfix(postfixExp);
                printf("\n수식의 값: %d\n", result);
                break;
            case 4:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 입력해주세요.\n");
        }
    }
    return 0;
}