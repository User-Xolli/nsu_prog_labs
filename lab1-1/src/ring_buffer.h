#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>

#define K 9
#define SIZE (1 << K)

struct RingBuffer
{
    unsigned int write_count;
    unsigned int mask; //mask = 2^k - 1
    unsigned char data[SIZE];
};

void write(struct RingBuffer *buff, const unsigned char *str, size_t len_str);
unsigned char get_elem(const struct RingBuffer *buff, size_t i);
void constructor(struct RingBuffer *buff);

#endif
