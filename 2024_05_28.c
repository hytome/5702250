#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LinkedList;

void initList(LinkedList *list) {
    list->head = NULL;
}

void addFirst(LinkedList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

void addLast(LinkedList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void deleteFirst(LinkedList *list) {
    if (list->head != NULL) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

void deleteLast(LinkedList *list) {
    if (list->head != NULL) {
        if (list->head->next == NULL) {
            free(list->head);
            list->head = NULL;
        } else {
            Node *current = list->head;
            while (current->next->next != NULL) {
                current = current->next;
            }
            free(current->next);
            current->next = NULL;
        }
    }
}

void printList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("(head)\n");
}

void freeList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

int main() {
    LinkedList list;
    initList(&list);
    int choice, data;

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
                addFirst(&list, data);
                break;
            case 2:
                printf("숫자 입력: ");
                scanf("%d", &data);
                addLast(&list, data);
                break;
            case 3:
                deleteFirst(&list);
                break;
            case 4:
                deleteLast(&list);
                break;
            case 5:
                printList(&list);
                break;
            case 6:
                freeList(&list);
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}