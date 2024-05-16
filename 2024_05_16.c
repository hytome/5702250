#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct ListNode{
    element data;
    struct ListNode *link;
}ListNode;

//오류처리 함수
void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode* insert_first(ListNode *head, int value){
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head; //헤드포인터의 변경된 값을 복사.
    head = p; //헤드포인터  변경
    return head; //변경된 헤드포인터 반환
}
//노드 pre뒤에 새로운 노드 삽입.
ListNode* insert(ListNode *head, ListNode *pre, element value){
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link; //pre->link 
    pre->link = p;
    return head;
}

ListNode* delete_first(ListNode *head){
    ListNode *removed;
    if(head == NULL){
        return NULL;
    }
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}
//pre가 가르키는 노드의 다음 노드를 삭제한다.
ListNode* delete(ListNode *head, ListNode *pre){
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

void print_list(ListNode *head){
    for(ListNode *p = head; p != NULL; p = p->link){
        printf("%d->", p->data);
    }
    printf("NULL\n");
} 
//그 화살표 출력을 위한 기능.

int main(){
    ListNode *head = NULL;
    for(int i =0; i<5; i++){
        head = insert_first(head, i);
        //insert_first()가 반환된 헤드포인트를 head에 삽입한다.
        print_list(head);
        //그리고 출력.
    }
    for(int i=0; i<5; i++){
        head = delete_first(head);
        print_list(head);  
    }
    return 0;
}

