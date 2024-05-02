#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
//스택과 큐의 배열값 모두에게 100을 주기 위해 선언.

typedef struct {
    char data[MAX_LEN];
    int top;
} Stack;

typedef struct {
    char data[MAX_LEN];
    int front, rear;
} Queue;

void initStack(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char item) {
    if (s->top < MAX_LEN - 1) {
        s->data[++s->top] = item;
    }
}

char pop(Stack *s) {
    if (s->top == -1) return '\0';
    return s->data[s->top--];
}

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

void enqueue(Queue *q, char item) {
    if (q->rear < MAX_LEN) {
        q->data[q->rear++] = item;
    }
}

char dequeue(Queue *q) {
    if (q->front == q->rear) return '\0';
    return q->data[q->front++];
}

int isPalindrome(const char *str) {
    Stack s;
    Queue q;
    initStack(&s);
    initQueue(&q);

    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            char ch = tolower(str[i]);
            push(&s, ch);
            enqueue(&q, ch);
        }
    }

    while (s.top != -1) {
        if (pop(&s) != dequeue(&q)) {
            return 0; 
        }
    }
    return 1; 
}

int main() {
    char str[MAX_LEN];
    int choice;

    while (1) { //한번 실행이 아니라 프로그램을 반복해야 하니까 while 문 안에 집어 넣기.
        printf("1. 회문을 입력\n2. 회문을 검사\n3. 프로그램 종료\n");
        printf("메뉴를 선택해주세요~: ");
        scanf("%d", &choice);
        getchar(); // 버퍼 텅텅 용도.

        switch (choice) {
            case 1:
                printf("회문 입력: ");
                fgets(str, MAX_LEN, stdin);
                str[strcspn(str, "\n")] = 0; //문자를 입력받을때 개행 문자 제거 용도.
                break;
            case 2:
                if (isPalindrome(str)) {
                    printf("\"%s\"는 회문이 맞습니다.\n", str);
                } else {
                    printf("\"%s\"는 회문이 아닙니다.\n", str);
                }
                break;
            case 3:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 입력해주세요.\n");
        }
    }
    return 0;
}