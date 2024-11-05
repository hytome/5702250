#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "heap.h"

HeapType* create_heap() {
	return (HeapType*)malloc(sizeof(HeapType));
}
void init_heap(HeapType* h) {
	h->heap_size = 0;
}
void destroy_heap(HeapType* h) {
	free(h);
}

void insert_max_heap(HeapType* h, heap_element item) {

	int i = h->heap_size + 1;

	while ((i > 1) && h->heap[i / 2].key < item.key) {
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
	(h->heap_size)++;
}

void insert_min_heap(HeapType* h, heap_element item) {

	int i = h->heap_size + 1;

	while ((i > 1) && h->heap[i / 2].key > item.key) {
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
	(h->heap_size)++;
}

heap_element delete_max_heap(HeapType* h) {
	int parent, child;
	heap_element item, temp;

	item = h->heap[1];
	temp = h->heap[h->heap_size];
	(h->heap_size)--;

	for (parent = 1, child = 2; child <= h->heap_size; parent = child, child *= 2) {
		if ((child < h->heap_size) &&
			(h->heap[child].key < h->heap[child + 1].key)) child++;
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
	}

	h->heap[parent] = temp;
	return item;
}

heap_element delete_min_heap(HeapType* h) {
	int parent, child;
	heap_element item, temp;

	//if (h->heap_size < 1) return ((heap_element) NULL);

	item = h->heap[1];
	temp = h->heap[h->heap_size];
	(h->heap_size)--;

	for (parent = 1, child = 2; child <= h->heap_size; parent = child, child *= 2) {
		if ((child < h->heap_size) &&
			(h->heap[child].key > h->heap[child + 1].key)) child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
	}

	h->heap[parent] = temp;
	return item;
}

void print_heap(HeapType* h) {

	if (h->heap_size == 0) {
		printf(" Heap Empty !!!\n");
		return;
	}

	printf("\n**** Heap **** \n");
	int level = 1;
	printf(" Level %02d: ", level);
	for (int i = 1; i <= h->heap_size; i++) {
		if (level != (((int)log2((double)(i))) + 1)) {
			level++;
			printf("\n Level %02d: ", level+1);
		}
		printf(" [%02d]{%02d<%d,%d>} ", i, h->heap[i].key, h->heap[i].start, h->heap[i].end);

	}
	printf("\n\n");
}