#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//리스트를 이용한 과일 출력 프로그램. 
typedef struct ListNode {
    char data[50];
    struct ListNode *link;
} ListNode; //노드 형태 구성 

void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
} //에러가 발생할시 메세지와 함께 프로그램 종료를 위한 기능 

ListNode* insert_last(ListNode *head, char *value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    //새로운 노드의 동적 할당을 위한 선언.
    ListNode *last = head;
    //리스트의 마지막 노드를 찾기 위한 기능.
    strcpy(p->data, value);
    //그렇게 복사한 값을 노드에 넣어줌.
    p->link = NULL;
    //마지막 노드의 링크는 NULL.
    if (head == NULL) { //그러나 만약 리스트가 비어있는경우 
        return p; //새로운 노드를 리스트의 첫번째 노드로 반환. 
    }
    while (last->link != NULL) {// 리스트의 마지막 노드를 찾기 위해 반복.
        last = last->link;
    }
    last->link = p; //새로운 노드를 리스트의 마지막에 추가.
    return head; //리스트의 헤드 반환.
}

ListNode* delete_node(ListNode *head, char *value, ListNode **deleted_head) {
    ListNode *p = head, *prev = NULL;
    //초기화.
    while (p != NULL && strcmp(p->data, value) != 0) {
        prev = p; //삭제할 노드를 찾기위한 리스트 순회문.
        p = p->link;
    }
    if (p == NULL) {
        printf("해당 과일이 없습니다.\n");
        return head;
    }
    //삭제할 노드가 리스트의 첫번째면.
    if (prev == NULL) {
        head = p->link; 
    } else {
        prev->link = p->link;
    }
    //그렇게 삭제된 노드를 리스트에 추가.
    p->link = *deleted_head;
    *deleted_head = p;
    printf("과일이 삭제되었습니다.\n");
    return head;
}
//출력을 위한 함수문들 
void print_list(ListNode *head) {
    for (ListNode *p = head; p != NULL; p = p->link) {
        printf("%s->", p->data);
    }
    printf("NULL\n");
}

void print_deleted_list(ListNode *head) {
    if (head == NULL) {
        printf("삭제된 과일이 없습니다.\n");
    } else {
        printf("삭제된 과일 목록:\n");
        for (ListNode *p = head; p != NULL; p = p->link) {
            printf("%s\n", p->data);
        }
    }
}

int main() {
    ListNode *head = NULL;
    ListNode *deleted_head = NULL;
    int choice;
    char value[50];

    char *initial_fruits[] = {"Mango", "Orange", "Apple", "Grape", "Cherry", "Plum", "Guava", "Raspberry", "Banana", "Peach"};
    //최초 과일 값 배열 선언.
    for (int i = 0; i < 10; i++) {
        head = insert_last(head, initial_fruits[i]);
    }

    while (1) { //반복문 안에 메뉴를 넣어 값을 계속 받아올 수  있도록 구현.
        printf("\n메뉴:\n");
        printf("1. 과일 추가\n");
        printf("2. 과일 삭제\n");
        printf("3. 삭제된 과일 목록 출력\n");
        printf("4. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("추가할 과일 이름: ");
                scanf("%s", value);
                ListNode *p = head;
                int exists = 0;
                while (p != NULL) {
                    if (strcmp(p->data, value) == 0) {
                        exists = 1;
                        break;
                    }
                    p = p->link;
                }
                if (exists) {
                    printf("이미 존재하는 과일입니다.\n");
                } else {
                    head = insert_last(head, value);
                    printf("과일이 추가되었습니다.\n");
                }
                break;
            case 2:
                printf("삭제할 과일 이름: ");
                scanf("%s", value);
                head = delete_node(head, value, &deleted_head);
                break;
            case 3:
                print_deleted_list(deleted_head);
                break;
            case 4:
                exit(0);
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
    return 0;
}