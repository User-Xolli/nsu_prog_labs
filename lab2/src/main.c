#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "next_permutation.h"

#define MAX_SIZE 11
#define ALL_NUMBERS 10

int to_number(char number)
{
    if (isdigit(number))
    {
        return number - '0';
    }
    else
    {
        return -1;
    }
}

static bool bad_input(char *str)
{
    bool number_exist[ALL_NUMBERS] = {false};
    for (size_t i = 0; i < strlen(str); ++i)
    {
        if (!isdigit(str[i]) || number_exist[to_number(str[i])])
        {
            return true;
        }
        number_exist[to_number(str[i])] = true;
    }
    return false;
}

int main(void)
{
    char str[MAX_SIZE];
    int n;
    if (scanf("%10s", str) != 1)
    {
        perror("No input\n");
        return EXIT_FAILURE;
    }
    if (scanf("%d", &n) != 1)
    {
        perror("No input\n");
        return EXIT_FAILURE;
    }
    if (bad_input(str))
    {
        printf("bad input\n");
        return EXIT_SUCCESS;
    }
    for (int i = 0; i < n && next_permutation(str); ++i)
    {
        printf("%s\n", str);
    }
    return EXIT_SUCCESS;
}
