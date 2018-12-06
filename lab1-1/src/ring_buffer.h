#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#define K 5
#define SIZE (1 << K)

struct RingBuffer
{
    unsigned int write_count;
    unsigned int mask; //mask = 2^k - 1
    unsigned char data[SIZE];
};

void write(struct RingBuffer *buff, const unsigned char *str, unsigned int len_str);
unsigned char get_elem(const struct RingBuffer *buff, unsigned int i);
void constructor(struct RingBuffer *buff);

#endif
