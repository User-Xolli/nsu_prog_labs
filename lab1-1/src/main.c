#include <stdlib.h>
#include <stdio.h>

#include "search_substring.h"

#define MAX_LEN 17
#define PATTERN_READ "%16[^\n]s"

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
    unsigned char pattern[MAX_LEN];
    check_read(scanf(PATTERN_READ, pattern));
    rabin_karp(pattern);
    return EXIT_SUCCESS;
}
