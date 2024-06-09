#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

void init(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

void print_dlist(DListNode* phead) {
    DListNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        printf("%d -> ", p->data);
    }
    printf("\n");
}

void insert_first(DListNode* phead, element data) {
    DListNode* new_node = (DListNode*)malloc(sizeof(DListNode));
    new_node->data = data;
    new_node->llink = phead;
    new_node->rlink = phead->rlink;
    phead->rlink->llink = new_node;
    phead->rlink = new_node;
}

void insert_last(DListNode* phead, element data) {
    DListNode* new_node = (DListNode*)malloc(sizeof(DListNode));
    new_node->data = data;
    new_node->rlink = phead;
    new_node->llink = phead->llink;
    phead->llink->rlink = new_node;
    phead->llink = new_node;
}

void delete_first(DListNode* phead) {
    if (phead->rlink != phead) {
        DListNode* removed = phead->rlink;
        phead->rlink = removed->rlink;
        removed->rlink->llink = phead;
        free(removed);
    }
}

void delete_last(DListNode* phead) {
    if (phead->llink != phead) {
        DListNode* removed = phead->llink;
        phead->llink = removed->llink;
        removed->llink->rlink = phead;
        free(removed);
    }
}

int main() {
    DListNode head;
    int choice, data;
    init(&head);

    while (1) {
        printf("메뉴:\n");
        printf("1. 숫자 입력 받아서 리스트 처음에 추가\n");
        printf("2. 숫자 입력 받아서 리스트 마지막에 추가\n");
        printf("3. 리스트 처음 노드 삭제\n");
        printf("4. 리스트 마지막 노드 삭제\n");
        printf("5. 리스트 프린트\n");
        printf("6. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("숫자 입력: ");
                scanf("%d", &data);
                insert_first(&head, data);
                break;
            case 2:
                printf("숫자 입력: ");
                scanf("%d", &data);
                insert_last(&head, data);
                break;
            case 3:
                delete_first(&head);
                break;
            case 4:
                delete_last(&head);
                break;
            case 5:
                print_dlist(&head);
                break;
            case 6:
                exit(0);
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
    return 0;
}