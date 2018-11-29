#include "next_permutation.h"

void swap(char *a, char *b);
void swap(char *a, char *b)
{
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(char *str);
void reverse(char *str)
{
    int len = (int)strlen(str);
    for (int i = 0; 2 * i < (int)strlen(str); ++i)
    {
        swap(&str[i], &str[len - i - 1]);
    }
}

bool next_permutation(char *str);
bool next_permutation(char *str)
{
    int index_smaller = -1;
    for (int i = (int)(strlen(str) - 1); i > 0; --i)
    {
        if (str[i - 1] < str[i])
        {
            index_smaller = i - 1;
            break;
        }
    }
    if (index_smaller == -1)
    {
        return false;
    }
    int index_min = 0;
    char min = '9';
    for (int i = (int)(strlen(str) - 1); i > index_smaller; --i)
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
