#include<stdio.h>
#include<string.h>

#define SIZE 16 // SIZE = 2^k


struct Ring_Buffer
{
    int write_count;
    int mask; //mask = 2^k - 1
    char data[SIZE];
};

void write(struct Ring_Buffer *buff, const char *value, const int *len_value)
{
    for (int i = 0; i < *len_value; ++i)
    {
        buff->data[buff->write_count & buff->mask] = value[i];
        ++buff->write_count;
    }
}

char get_elem(const struct Ring_Buffer *buff, const int i)
{
    return buff->data[i & buff->mask];
}


int main()
{
    char pattern[16];
    scanf("%[^\n]%*c", pattern);
    int len = (int) strlen(pattern);
    int p[256]; //table of shifts
    for (int i = 0; i < 256; ++i)
    {
        p[i] = len;
    }
    int *d = p + 128; //table shifts with negative number

    for (int i = 0; i + 1 < len; ++i)
    {
        if (d[(int) pattern[i]] > len - i - 1)
        {
            d[(int) pattern[i]] = len - i - 1; //constructing table of shifts
        }
    }

    struct Ring_Buffer buffer;
    buffer.write_count = 0;
    buffer.mask = SIZE - 1;

    int pos = len - 1; //position of pattern`s last symbol in text

    char symbols[16]; //part text
    int read_symb_count = (int) fread(symbols, sizeof(char), (size_t) (pos - buffer.write_count) + 1, stdin);
    write(&buffer, symbols, &read_symb_count);

    while (read_symb_count != 0 && pos < buffer.write_count)
    {
        read_symb_count = (int) fread(symbols, sizeof(char), (size_t) (pos - buffer.write_count) + 1, stdin);
        write(&buffer, symbols, &read_symb_count);

        int concurrences = 0;

        while (get_elem(&buffer, pos - concurrences) == pattern[len - concurrences - 1] && len - concurrences - 1 >= 0)
        {
            printf("%d ", pos - concurrences + 1);
            ++concurrences;
        }
        if (concurrences != len)
        {
            printf("%d ", pos - concurrences + 1);
        }
        pos += d[(int) get_elem(&buffer, pos)];

        read_symb_count = (int) fread(symbols, sizeof(char), (size_t) (pos - buffer.write_count) + 1, stdin);
        write(&buffer, symbols, &read_symb_count);
    }
    printf("\n");
    return 0;
}
