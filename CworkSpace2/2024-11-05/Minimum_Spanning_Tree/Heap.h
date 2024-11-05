#pragma once

#define MAX_ELEMENT 100

typedef struct {
	int key;
	int start, end;
} heap_element;

typedef struct {
	heap_element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

extern HeapType* create_heap();
extern void init_heap(HeapType* h);
extern void destroy_heap(HeapType* h);
extern void insert_max_heap(HeapType* h, heap_element item);
extern heap_element delete_max_heap(HeapType* h);
extern void insert_min_heap(HeapType* h, heap_element item);
extern heap_element delete_min_heap(HeapType* h);
extern void print_heap(HeapType* h);