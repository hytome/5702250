#include <stdio.h>
#define SIZE 100

typedef int element;

typedef struct
{
  element data[SIZE];
  int top; 
} StackType;

// 초기화
void init(StackType *S)
{
  S->top = -1;
}

// 에러 체크 함수
int is_empty(StackType *S)
{
  return S->top == -1;
}

int is_full(StackType *S)
{
  return S->top == SIZE - 1;
}

// 삽입
void push(StackType *S, element e)
{
  if (is_full(S))
    printf("Overflow\n");
  else
  {
    S->top++;
    S->data[S->top] = e;
  }
}

// 삭제
element pop(StackType *S)
{
  if (is_empty(S))
  {
    printf("Empty\n");
    return -1;
  }
  else
  {
    element e = S->data[S->top];
    S->top--;
    return e;
  }
}

// 조회
element peek(StackType *S)
{
  if (is_empty(S))
  {
    printf("Empty\n");
    return -1;
  }
  else
  {
    return S->data[S->top];
  }
}

void print(StackType *S)
{
  for (int i = 0; i <= S->top; i++)
  {
    printf("%c ", S->data[i]);
  }
  printf("\n");
}

int main()
{
  StackType S;
  init(&S);

  pop(&S);
  push(&S, 'a');
  push(&S, 'b');
  push(&S, 'c');
  print(&S);
  element p = pop(&S);
  printf("%c\n", p);
  print(&S);
}