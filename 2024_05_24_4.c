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
    L->insert_count = 0;
    L->delete_count = 0;
}

//리스트가 비어 있으면 1, 아니면 0 반환.
int is_empty(ArrayListType *L){
    return L->size == 0;
}

//리스트가 가득 찼는지 확인
int is_full(ArrayListType *L){
    return L->size == MAX_LIST_SIZE;
}

//리스트의 특정 위치의 항목을 반환
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
    printf("NULL\n");
}

//리스트의 마지막에 항목 삽입
void insert_last(ArrayListType *L, element item){
    if(is_full(L)){
        error("리스트 오버 플로우.");
    }
    L->array[L->size++] = item;
    L->insert_count++;
}

//리스트의 특정 위치에 항목 삽입
void insert(ArrayListType *L, int index, element item){
    if(!is_full(L) && (index >= 0 && index <= L->size)){
        for(int i=L->size-1; i>=index; i--){
            L->array[i+1] = L->array[i];
        }
        L->array[index] = item;
        L->size++;
        L->insert_count++;
    } else {
        error("리스트 오버 플로우 또는 잘못된 인덱스");
    }
}

//리스트의 특정 위치의 항목 삭제
element delete(ArrayListType *L, int index){
    if(index < 0 || index >= L->size){
        error("index error");
    }
    element item = L->array[index];
    for(int i=index; i<L->size-1; i++){
        L->array[i] = L->array[i+1];
    }
    L->size--;
    L->delete_count++;
    return item;
}

int main(){
    ArrayListType list;
    init(&list);
    int command, index, value;

    while (1) {
        printf("\n메뉴\n");
        printf("(1) 리스트에 추가\n");
        printf("(2) 리스트에 삭제\n");
        printf("(3) 리스트를 출력\n");
        printf("(0) 프로그램 종료\n");
        printf("선택: ");
        scanf("%d", &command);

        switch (command) {
            case 1:
                printf("삽입할 위치와 값을 입력하세요: ");
                scanf("%d %d", &index, &value);
                insert(&list, index, value);
                printf("삽입 완료\n");
                printf("데이터 이동 횟수: %d\n", list.size - index); // 삽입 시 데이터 이동 횟수 출력
                break;
            case 2:
                printf("삭제할 위치를 입력하세요: ");
                scanf("%d", &index);
                element item = delete(&list, index);
                printf("삭제된 항목: %d\n", item);
                printf("데이터 이동 횟수: %d\n", list.size - index); // 삭제 시 데이터 이동 횟수 출력
                break;
            case 3:
                print_list(&list);
                break;
            case 0:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 명령입니다. 다시 입력해주세요.\n");
        }
    }
    return 0;
}