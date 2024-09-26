#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 200

typedef struct{
    int key;
}element;

typedef struct{
    element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;

//생성함수
HeapType* create(){
    return (HeapType*)malloc(sizeof(HeapType));

}

//초기화 함수
void init(HeapType* h){
    h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item){
    int i;
    i = ++(h->heap_size);
    //트리를 거슬러 올라가면서 부모 노드와 비교하는 과정.
    while((i!=1)&&(item.key>h->heap[i/2].key)){
        h->heap[i] = h->heap[i/2];
        i/=2;
        //i가 루트노드가 아니고, 새로운 노드의 키값이 부모노드의 키값보다 크면 위치를 바꿈.
    }
    h->heap[i] = item;
    //새로운 노드를  삽입.
}

//힙 삭제 함수 
element delete_max_heap(HeapType* h){
    int parent, child;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while(child<=h->heap_size){
        if((child<h->heap_size)&&(h->heap[child].key)<h->heap[child+1].key){
            child++;
        }
        if(temp.key>=h->heap[child].key){
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child*=2;   
    }
    h->heap[parent] = temp;
    return item;
}

int main(){
    element e1 = {10}, e2 = {5}, e3 = {30};
    element e4, e5, e6;
    HeapType* heap = create();
    init(heap);
    insert_max_heap(heap, e1);
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);
    e4 = delete_max_heap(heap);
    printf("<%d>\n", e4.key);
    e5 = delete_max_heap(heap);
    printf("<%d>\n", e5.key);
    e6 = delete_max_heap(heap);
    printf("<%d>\n", e6.key);
    free(heap);
    return 0;
}