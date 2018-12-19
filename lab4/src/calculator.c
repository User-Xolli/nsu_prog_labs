#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <iso646.h> // for using or and

#include "calculator.h"

#define BASE 10

#define NUMBER 0
#define MINUS 1
#define PLUS 2
#define MULTIPLICATION 3
#define DIVISION 4
#define OPEN_BRACKET 5
#define CLOSE_BRACKET 6
#define END 7

struct Lexem
{
    int type;
    int value;
};

static void syntax_error(void)
{
    printf("syntax error\n");
    exit(EXIT_SUCCESS);
}

static void division_zero(void)
{
    printf("division by zero\n");
    exit(EXIT_SUCCESS);
}

static bool valid_haracter(char symbol)
{
    return isdigit(symbol) or symbol == '+' or symbol == '-' or symbol == '/' or
           symbol == '*' or symbol == '(' or symbol == ')';
}

static int todigit(char number)
{
    return number - '0';
}

static void next_lexem(struct Lexem *current, char **element_expression)
{
    while (**element_expression == ' ')
    {
        ++(*element_expression);
    }

    if (**element_expression == '\0' or **element_expression == '\n')
    {
        current->type = END;
        return;
    }

    if (!valid_haracter(**element_expression))
    {
        syntax_error();
    }

    if (**element_expression == '+')
    {
        current->type = PLUS;
        ++(*element_expression);
        return;
    }
    if (**element_expression == '-')
    {
        current->type = MINUS;
        ++(*element_expression);
        return;
    }
    if (**element_expression == '*')
    {
        current->type = MULTIPLICATION;
        ++(*element_expression);
        return;
    }
    if (**element_expression == '/')
    {
        current->type = DIVISION;
        ++(*element_expression);
        return;
    }
    if (**element_expression == '(')
    {
        current->type = OPEN_BRACKET;
        ++(*element_expression);
        return;
    }
    if (**element_expression == ')')
    {
        current->type = CLOSE_BRACKET;
        ++(*element_expression);
        return;
    }

    current->value = 0;
    while (isdigit(**element_expression))
    {
        current->value *= BASE;
        current->value += todigit(**element_expression);
        ++(*element_expression);
    }
    current->type = NUMBER;
}

static int expression(struct Lexem *current, char **element_expression);

static int multiplier(struct Lexem *current, char **element_expression)
{
    int ans = 0;
    if (current->type == NUMBER)
    {
        ans = current->value;
        next_lexem(current, element_expression);
    }
    else if (current->type == OPEN_BRACKET)
    {
        next_lexem(current, element_expression);
        ans = expression(current, element_expression);
        if (current->type != CLOSE_BRACKET)
        {
            syntax_error();
        }
        else
        {
            next_lexem(current, element_expression);
        }
    }
    else
    {
        syntax_error();
    }
    return ans;
}

static int summand(struct Lexem *current, char **element_expression)
{
    int ans = multiplier(current, element_expression);
    while (current->type == MULTIPLICATION or current->type == DIVISION)
    {
        if (current->type == MULTIPLICATION)
        {
            next_lexem(current, element_expression);
            ans *= multiplier(current, element_expression);
        }
        else
        {
            next_lexem(current, element_expression);
            int divider = multiplier(current, element_expression);
            if (divider != 0)
            {
                ans /= divider;
            }
            else
            {
                division_zero();
            }
        }
    }
    return ans;
}

static int expression(struct Lexem *current, char **element_expression)
{
    int ans = summand(current, element_expression);
    while (current->type == PLUS or current->type == MINUS)
    {
        if (current->type == PLUS)
        {
            next_lexem(current, element_expression);
            ans += summand(current, element_expression);
        }
        else
        {
            next_lexem(current, element_expression);
            ans -= summand(current, element_expression);
        }
    }
    return ans;

}

int calculator(char *main_expression)
{
    struct Lexem current;
    next_lexem(&current, &main_expression);
    int ans = expression(&current, &main_expression);
    if (current.type != END)
    {
        syntax_error();
    }
    return ans;
}
