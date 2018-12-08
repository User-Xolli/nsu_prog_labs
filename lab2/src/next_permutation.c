#include <string.h>

#include "next_permutation.h"

#define NOT_MODIIFICATION 1 << 30

void swap(char *a, char *b)
{
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(char *str)
{
    size_t len = strlen(str);
    for (size_t i = 0; 2 * i < strlen(str); ++i)
    {
        swap(&str[i], &str[len - i - 1]);
    }
}

bool next_permutation(char *str)
{
    size_t index_smaller = NOT_MODIIFICATION;
    for (size_t i = strlen(str) - 1; i > 0; --i)
    {
        if (str[i - 1] < str[i])
        {
            index_smaller = i - 1;
            break;
        }
    }
    if (index_smaller == NOT_MODIIFICATION)
    {
        return false;
    }
    size_t index_min = 0;
    char min = '9';
    for (size_t i = strlen(str) - 1; i > index_smaller; --i)
    {
        if (str[i] <= min && str[i] > str[index_smaller])
        {
            min = str[i];
            index_min = i;
        }
    }
    swap(&str[index_smaller], &str[index_min]);
    reverse(str + index_smaller + 1);
    return true;
}
