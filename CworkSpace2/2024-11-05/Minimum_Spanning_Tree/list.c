#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void init_Dlist(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

void print_Dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf(" |%d(%d)| ", p->vertex.number, p->vertex.weight);
	}
	printf("\n");
}

void insert_Dlist(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->vertex.number = data.number; // vertex
	newnode->vertex.weight = data.weight;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 노드 removed를 삭제한다.
void delete_Dlist(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

DListNode* search_Dlist(DListNode* head, element data) {

	DListNode* node = head->rlink;
	do {
		if (node->vertex.number == data.number) return node;
		else node = node->rlink;
	} while (node != head);
	return (DListNode*)NULL;
}