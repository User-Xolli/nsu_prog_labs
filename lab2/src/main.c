#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "next_permutation.h"
#include "number_string.h"

#define MAX_SIZE 11

static bool bad_input(char *str)
{
    bool number_exist[MAX_SIZE] = {false};
    for (int i = 0; i < (int)strlen(str); ++i)
    {
        if (!is_number(str[i]) || number_exist[to_number(str[i])])
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
