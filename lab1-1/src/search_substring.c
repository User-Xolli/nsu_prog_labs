#include "search_substring.h"

#define BASE 3

static int power(int a, int b)
{
    if (b <= 0)
    {
        return 1;
    }
    if (b % 2 == 0)
    {
        int tmp = power(a, b / 2);
        return tmp * tmp;
    }
    else
    {
        return power(a, b - 1) * a;
    }
}

static int hash(unsigned char *str)
//hash(str[0],...,str[N-1]) = sum((str[i] % base) * (base^i))
{
    int h = 0;
    for (int i = (int)strlen(str) - 1; i >= 0; --i)
    {
        h *= BASE;
        h += str[i] % BASE;
    }
    return h;
}

static int hash_with_new_symb(int symb, int hash_str, int len_str)
{
    int pow_base = power(BASE, len_str - 1);
    hash_str /= BASE;
    hash_str += pow_base * (symb % BASE);
    return hash_str;
}

void rabin_karp(unsigned char *pattern)
{
    unsigned int len = strlen(pattern);

    int hash_pattern = hash(pattern);
    printf("%d\n", hash_pattern);

    unsigned char begin_text[17];
    if (fread(begin_text, sizeof(char), (size_t)len, stdin) < len)
    {
        return;
    }
    begin_text[len] = '\0';

    struct RingBuffer buffer;
    constructor(&buffer);
    write(&buffer, begin_text, len);
    int hash_text = hash(begin_text);

    unsigned int pos = len; // current symbol's number
    unsigned int read_symbols_count = len;
    while (read_symbols_count != 0 && pos <= buffer.write_count)
    {
        if (hash_text == hash_pattern)
        {
            for (unsigned int i = pos - len; i < pos; ++i)
            {
                printf("%u ", i);
                if (get_elem(&buffer, i) != pattern[i + len - pos])
                {
                    break;
                }
            }
        }

        if (pos >= buffer.write_count)
        {
            unsigned char symbols[17];
            read_symbols_count = fread(symbols, sizeof(char), (size_t)len, stdin);
            write(&buffer, symbols, read_symbols_count);
        }

        unsigned char symbol = get_elem(&buffer, pos);
        hash_text = hash_with_new_symb(symbol, hash_text, len);
        ++pos;
    }
    printf("\n");
}
