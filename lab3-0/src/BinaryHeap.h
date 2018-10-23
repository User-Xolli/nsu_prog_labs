struct BinaryHeap // root's index = 0
{
    unsigned int size;
    int* data;
};


void swap (int* a, int* b);
unsigned int index_left_child (unsigned int index);
unsigned int index_right_child (unsigned int index);
int* get_elem (struct BinaryHeap *heap, unsigned int i);
int* left_child (struct BinaryHeap *heap, unsigned int index);
int* right_child (struct BinaryHeap *heap, unsigned int index);
int* get_first_elem(struct BinaryHeap *heap);
int* get_last_elem(struct BinaryHeap *heap);
int existence_left_child (struct BinaryHeap *heap, unsigned int index);
int existence_right_child (struct BinaryHeap *heap, unsigned int index);
void recovery_heap (struct BinaryHeap *heap, unsigned int index);
void build_heap (struct BinaryHeap *heap);
int del_root (struct BinaryHeap *heap);
