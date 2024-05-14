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
    L->insert_count = 0; // 삽입 카운터 (횟수) 초기화 기능입니다.
    L->delete_count = 0; // 삭제 카운터 (횟수) 초기화 기능입니다.
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

//리스트 출력 하기 위한 함수 
void print_list(ArrayListType *L){
    for(int i=0; i<L->size; i++){
        printf("%d-> ",L->array[i]);
        //가독성을 위해 -> 를 추가했습니다.
    }
    printf("NULL\n");
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
        L->insert_count++; // 삽입 카운터 를 증가시킵니다.
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
    L->delete_count++; // 삭제 카운터 증가 시킵니다.
    return item;
}

int main(){
    ArrayListType list;
    init(&list);
    int command, index, value;
    int move_count; // 데이터 이동 횟수를 저장할 변수 기능 입니다.

    while (1) {
        printf("\n메뉴\n");
        printf("(1) 리스트에 추가\n");
        printf("(2) 리스트에 삭제\n");
        printf("(3) 리스트를 출력\n");
        printf("(0) 프로그램 종료\n");
        printf("선택: ");
        scanf("%d", &command);

        switch (command) {
            case 1: // 삽입할 위치와 값을 입력하는 기능.
                printf("삽입할 위치와 값을 입력하세요: ");
                //삽입할 위치와 값을 한번에 이루어지도록 통일 시켰음.
                scanf("%d %d", &index, &value);
                move_count = 0;
                if (!is_full(&list) && (index >= 0 && index <= list.size)) {
                    for (int i = list.size - 1; i >= index; i--) {
                        list.array[i + 1] = list.array[i];
                        move_count++;
                    }
                    list.array[index] = value;
                    list.size++;
                    list.insert_count++;
                    printf("삽입 완료 \n");
                    printf("데이터 이동 횟수: %d\n", move_count);
                } else {
                    printf("리스트가 가득 찼거나 잘못된 인덱스입니다.\n");
                }
                break;
            case 2: // 배열의 삭제를 위한 기능.
                printf("삭제할 위치를 입력하세요: ");
                scanf("%d", &index);
                move_count = 0;
                if (index < 0 || index >= list.size) {
                    printf("잘못된 인덱스입니다.\n");
                } else {
                    element item = list.array[index];
                    for (int i = index; i < list.size - 1; i++) {
                        list.array[i] = list.array[i + 1];
                        move_count++;
                    }
                    list.size--;
                    list.delete_count++;
                    printf("삭제된 항목: %d\n", item);
                    printf("데이터 이동 횟수: %d\n", move_count);
                }
                break;
            case 3: // 프로그램 출력기능 case.
                print_list(&list);
                break;
            case 0: // 프로그램 종료 기능 case.
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 명령입니다. 다시 입력해주세요.\n");
        }
        
    }
    return 0;
}