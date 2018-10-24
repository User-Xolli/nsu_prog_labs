#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <stdbool.h>

struct BinaryHeap // root's index = 0
{
    unsigned int size;
    int* data;
};

void build_heap (struct BinaryHeap *heap); // arbitrary array to binary heap
int del_root (struct BinaryHeap *heap); // return root's value

#endif
