#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search_substring.h"

static void check_read(int read_len)
{
    if (read_len == 0)
    {
        perror("Cannot read search pattern");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    unsigned char pattern[17];
    check_read(scanf("%16[^\n]s", pattern));
    rabin_karp(pattern);
    return EXIT_SUCCESS;
}
