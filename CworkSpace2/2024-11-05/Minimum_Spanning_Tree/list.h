#pragma once

typedef struct {
	int number;
	int weight;
} element;

typedef struct DListNode {	// 이중연결 노드 타입
	element vertex;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

extern void init_Dlist(DListNode* phead);
extern void print_Dlist(DListNode* phead);
extern void insert_Dlist(DListNode* before, element data);
extern void delete_Dlist(DListNode* head, DListNode* removed);
extern DListNode* search_Dlist(DListNode* head, element data);