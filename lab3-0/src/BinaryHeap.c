#include "BinaryHeap.h"

void swap (int* a, int* b);
void swap (int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

unsigned int index_left_child (unsigned int index);
unsigned int index_left_child (unsigned int index)
{
    return 2 * index + 1;
}

unsigned int index_right_child (unsigned int index);
unsigned int index_right_child (unsigned int index)
{
    return 2 * index + 2;
}


int* get_elem (struct BinaryHeap *heap, unsigned int i);
int* get_elem (struct BinaryHeap *heap, unsigned int i)
{
    return &(heap->data[i]);
}

int* left_child (struct BinaryHeap *heap, unsigned int index);
int* left_child (struct BinaryHeap *heap, unsigned int index)
{
    return get_elem (heap, index_left_child(index));
}

int* right_child (struct BinaryHeap *heap, unsigned int index);
int* right_child (struct BinaryHeap *heap, unsigned int index)
{
    return get_elem (heap, index_right_child(index));
}

int* get_first_elem (struct BinaryHeap *heap);
int* get_first_elem (struct BinaryHeap *heap)
{
    return heap->data;
}

int* get_last_elem (struct BinaryHeap *heap);
int* get_last_elem (struct BinaryHeap *heap)
{
    return &heap->data[heap->size - 1];
}

bool has_left_child (struct BinaryHeap *heap, unsigned int index);
bool has_left_child (struct BinaryHeap *heap, unsigned int index)
{
    return index_left_child(index) < heap->size;
}

bool has_right_child (struct BinaryHeap *heap, unsigned int index);
bool has_right_child (struct BinaryHeap *heap, unsigned int index)
{
    return index_right_child(index) < heap->size;
}

void recovery_heap (struct BinaryHeap *heap, unsigned int index);
void recovery_heap (struct BinaryHeap *heap, unsigned int index) // heap's root = index
{
    unsigned int index_min = index;
    if (has_left_child(heap, index) &&
        *left_child (heap, index) < *get_elem (heap, index_min))
    {
        index_min = index_left_child(index);
    }
    if (has_right_child(heap, index) &&
        *right_child(heap, index) < *get_elem (heap, index_min))
    {
        index_min = index_right_child (index);
    }
    if (index_min != index)
    {
        swap (get_elem(heap, index), get_elem(heap, index_min));
        recovery_heap (heap, index_min);
    }
}

void build_heap (struct BinaryHeap *heap) // arbitrary array to binary heap
{
    for (int i = ((int)heap->size - 1) / 2; i >= 0; --i)
    {
        recovery_heap (heap, (unsigned int)i);
    }
}

int del_root (struct BinaryHeap *heap) // return root's value
{
    swap (get_first_elem (heap), get_last_elem (heap));
    --heap->size;
    recovery_heap (heap, 0);
    return *get_elem(heap, heap->size);
}
