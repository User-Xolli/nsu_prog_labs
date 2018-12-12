#include <stddef.h>
#include "ring_buffer.h"

void write(struct RingBuffer *buff, const unsigned char *str, size_t len_str)
{
    for (unsigned int i = 0; i < len_str; ++i)
    {
        buff->data[buff->write_count & buff->mask] = str[i];
        ++buff->write_count;
    }
}

unsigned char get_elem(const struct RingBuffer *buff, size_t i)
{
    return buff->data[i & buff->mask];
}

void constructor(struct RingBuffer *buff)
{
    buff->write_count = 0;
    buff->mask = SIZE - 1;
}
