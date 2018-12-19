#include <stdlib.h>
#include <stdio.h>

#include "calculator.h"

#define MAX_LEN 1001

int main(void)
{
    char main_expression[MAX_LEN] = {0};
    fread(main_expression, sizeof(char), MAX_LEN, stdin);
    printf("%d\n", calculator(main_expression));
    return EXIT_SUCCESS;
}
