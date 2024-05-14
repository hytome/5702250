#include<stdio.h>
#include<stdlib.h>
#define MAX_LIST_SIZE 100

typedef int element; //항목의 정의.

typedef struct{
    element array[MAX_LIST_SIZE]; //배열 정의.
    int size; //현재 리스트에 저장된 항목들의 갯수.
    int insert_count; // 삽입 횟수를 추적
    int delete_count; // 삭제 횟수를 추적
}ArrayListType;

//오류처리 함수
void error(char *message){
    fprintf(stderr,"%s\n",message);
    exit(1);
}

//리스트 초기화 함수
void init(ArrayListType *L){
    L->size = 0;
    L->insert_count = 0; // 삽입 카운터 초기화
    L->delete_count = 0; // 삭제 카운터 초기화
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
    L->insert_count++; // 삽입 카운터 증가
}



void insert(ArrayListType *L, int index, element item){
    if(!is_full(L)&&(index >= 0 && index <= L->size)){
        for(int i=(L->size-1); i>=index; i--){
            L->array[i+1] = L->array[i];
        }
        L->array[index] = item;
        L->size++;
        L->insert_count++; // 삽입 카운터 증가
    }
}

element delete(ArrayListType *L, int index){
    element item;
    if(index < 0 || index >= L->size){
        error("index error");
    }
    item = L->array[index];
    for(int i=index; i<L->size-1; i++){
        L->array[i] = L->array[i+1];
    }
    L->size--;
    L->delete_count++; // 삭제 카운터 증가
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
    insert_last(&list, 40);
    print_list(&list);
    delete(&list, 0);
    print_list(&list);
    printf("Insert operations: %d\n", list.insert_count);
    printf("Delete operations: %d\n", list.delete_count);
    return 0;
}