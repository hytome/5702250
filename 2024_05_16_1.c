#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct ListNode{
    element data;
    struct ListNode *link;
}ListNode;

// 오류처리 함수
void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode* insert_first(ListNode *head, int value){
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode* insert(ListNode *head, ListNode *pre, element value, int *link_count){
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    (*link_count)++;
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

ListNode* delete(ListNode *head, ListNode *pre, int *link_count){
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    (*link_count)++;
    return head;
}

void print_list(ListNode *head){
    for(ListNode *p = head; p != NULL; p = p->link){
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

int main(){
    ListNode *head = NULL;
    int choice, value, position;
    ListNode *pre;
    int link_count;

    while(1){
        printf("\n메뉴:\n");
        printf("1. 삽입 (맨 앞)\n");
        printf("2. 삽입 (특정 위치)\n");
        printf("3. 삭제 (맨 앞)\n");
        printf("4. 삭제 (특정 위치)\n");
        printf("5. 출력\n");
        printf("6. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("삽입할 값: ");
                scanf("%d", &value);
                head = insert_first(head, value);
                break;
            case 2:
                printf("삽입할 값: ");
                scanf("%d", &value);
                printf("삽입할 위치 (0부터 시작): ");
                scanf("%d", &position);
                pre = head;
                link_count = 0;
                for(int i = 0; i < position - 1 && pre != NULL; i++){
                    pre = pre->link;
                    link_count++;
                }
                if(pre != NULL){
                    head = insert(head, pre, value, &link_count);
                    printf("링크를 따라 이동한 횟수: %d\n", link_count);
                } else {
                    printf("잘못된 위치입니다.\n");
                }
                break;
            case 3:
                head = delete_first(head);
                break;
            case 4:
                printf("삭제할 위치 (0부터 시작): ");
                scanf("%d", &position);
                pre = head;
                link_count = 0;
                for(int i = 0; i < position - 1 && pre != NULL; i++){
                    pre = pre->link;
                    link_count++;
                }
                if(pre != NULL && pre->link != NULL){
                    head = delete(head, pre, &link_count);
                    printf("링크를 따라 이동한 횟수: %d\n", link_count);
                } else {
                    printf("잘못된 위치입니다.\n");
                }
                break;
            case 5:
                print_list(head);
                break;
            case 6:
                exit(0);
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
    return 0;
}