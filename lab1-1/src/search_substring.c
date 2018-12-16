#include <string.h>
#include <stdio.h>

#include "ring_buffer.h"
#include "search_substring.h"

#define BASE 3
#define MAX_LEN_PATTERN 16
#define LEN_READING_PART (1 << 8)

static size_t power(size_t a, size_t b)
{
    if (b == 0)
    {
        return 1;
    }
    if (b % 2 == 0)
    {
        size_t tmp = power(a, b / 2);
        return tmp * tmp;
    }
    else
    {
        return power(a, b - 1) * a;
    }
}

/**
    * Hash function:
    * hash(str[0],...,str[N-1]) = sum((str[i] % base) * (base^i))
    */
static int hash(const unsigned char *str)
{
    int h = 0;
    for (int i = (int)strlen((const char *)str) - 1; i >= 0; --i)
    {
        h *= BASE;
        h += str[i] % BASE;
    }
    return h;
}

static int hash_with_new_symb(int symbol, int hash_str, size_t len_str)
{
    size_t pow_base = power(BASE, len_str - 1);
    hash_str /= BASE;
    hash_str += pow_base * (symbol % BASE);
    return hash_str;
}

static void comparison(int hash_pattern, int hash_string, const unsigned char *pattern,
        struct RingBuffer *string, size_t pos)
{
    size_t len = strlen((const char *)pattern);
    if (hash_string == hash_pattern)
    {
        for (size_t i = pos - len; i < pos; ++i)
        {
            printf("%Iu ", i); // "%zu" doesn't work for Windows
            if (get_elem(string, i) != pattern[i + len - pos])
            {
                break;
            }
        }
    }
}

void rabin_karp(const unsigned char *pattern)
{
    size_t len = strlen((const char *)pattern);

    int hash_pattern = hash(pattern);
    printf("%d\n", hash_pattern);

    unsigned char begin_text[MAX_LEN_PATTERN + 1] = {0};
    if (fread(begin_text, sizeof(unsigned char), len, stdin) < len)
    {
        return;
    }

    struct RingBuffer buffer;
    constructor(&buffer);
    write(&buffer, begin_text, len);
    int hash_text = hash(begin_text);

    size_t pos = len; // current symbol's number
    size_t read_symbols_count = len;
    while (read_symbols_count != 0 && pos <= buffer.write_count)
    {

        comparison(hash_pattern, hash_text, pattern, &buffer, pos);

        if (pos >= buffer.write_count)
        {
            unsigned char symbols[LEN_READING_PART + 1];
            read_symbols_count = fread(symbols, sizeof(char), LEN_READING_PART, stdin);
            write(&buffer, symbols, read_symbols_count);
        }

        unsigned char symbol = get_elem(&buffer, pos);
        hash_text = hash_with_new_symb(symbol, hash_text, len);
        ++pos;
    }
    printf("\n");
}
