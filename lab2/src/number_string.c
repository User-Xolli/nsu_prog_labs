#include "number_string.h"

bool is_number(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

int to_number(char number)
{
    if (is_number(number))
    {
        return number - '0';
    } else
    {
        return -1;
    }
}
