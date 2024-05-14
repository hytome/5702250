#include<stdio.h>
#include<stdlib.h>
#define MAX_LIST_SIZE 100

typedef int element; //항목의 정의.

typedef struct{
    element array[MAX_LIST_SIZE]; //배열 정의.
    int size; //현재 리스트에 저장된 항목들의 갯수.

}ArrayListType;

//오류처리 함수
void error(char *message){
    fprintf(stderr,"%s\n",message);
    exit(1);
}

//리스트 초기화 함수
void init(ArrayListType *L){
    L->size = 0;
}

//리스트가 비어 있으면 1, 아니면 0 반환.
int is_empty(ArrayListType *L){
    return L->size == 0;
}

//is_full  가득 찼을 경우.
int is_full(ArrayListType *L){
    return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType *L, int index){
    if(index < 0 || index >= L->size){
        error("index error");
    }
    return L->array[index];
}

//리스트 출력 
void print_list(ArrayListType *L){
    for(int i=0; i<L->size; i++){
        printf("%d-> ",L->array[i]);
    }
    printf("\n");
}

void insert_last(ArrayListType *L, element item){
    if(L->size >= MAX_LIST_SIZE){
        error("리스트 오버 플로우.");
    }
    L->array[L->size++] = item;
}

void insert(ArrayListType *L, int index, element item){
    if(L->size >= MAX_LIST_SIZE){
        error("overflow");
    }
    for(int i=L->size; i>index; i--){
        L->array[i] = L->array[i-1];
    }
    L->array[index] = item;
    L->size++;
}

element delete(ArrayListType *L, int index){
    element item = L->array[index];
    for(int i=index; i<L->size-1; i++){
        L->array[i] = L->array[i+1];
    }
    L->size--;
    return item;
}

int main(){
    ArrayListType list;
    init(&list);
    insert(&list, 0, 10);
    print_list(&list);
    insert(&list, 0, 20);
    print_list(&list);
    insert(&list, 0, 30);
    print_list(&list);
    insert(&list, 0, 40);
    print_list(&list);
    delete(&list, 0);
    print_list(&list);
    return 0;
}

