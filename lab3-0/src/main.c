#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "BinaryHeap.h"

int main(void)
{
    unsigned int n;
    scanf("%u", &n);
    struct BinaryHeap heap;
    heap.size = n;
    heap.data = malloc(sizeof(*heap.data) * n);
    if (heap.data == NULL)
    {
        errno = ENOMEM;
        perror("No memory");
        return EXIT_FAILURE;
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        scanf("%d", &(heap.data[i]));
    }
    build_heap(&heap);
    for (unsigned int i = 0; i < n; ++i)
    {
        printf("%d ", del_root(&heap));
    }
    printf("\n");
    free(heap.data);
    return EXIT_SUCCESS;
}
