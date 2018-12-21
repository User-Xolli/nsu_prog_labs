/**
 * \file
 * \brief Файл с реализацией калькулятора
 *
 * Как работает данный калькулятор?\n
 * В арифметическом выражении есть три типа составляющих - выражение, слагаемое, множитель\n
 * Выражение это сумма слагаемых\n
 * Слагаемое это произведение множителей\n
 * Множитель это число либо выражение в скобках\n
 * Данный калькуятор рекурсивно вычисляет значение арифметического выражения
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <iso646.h> // for using "or" & "and"

#include "calculator.h"

#define BASE 10 ///< Основание системы счисления чисел в вычисляемом арифметическом выражении

/// Набор типов лексем
enum Type_Literal
{
    NUMBER, ///< Число
    MINUS, ///< операция -
    PLUS, ///< операция +
    MULTIPLICATION, ///< операция *
    DIVISION, ///< операция /
    OPEN_BRACKET, ///< открытая скобка
    CLOSE_BRACKET, ///< закрытая скобка
    END ///< конец строки (/0 либо /n)
};

/**
 * \brief Лексемы - это то, из чего состоят арифметические выражения
 *
 * Лексемами арифметического выражения являются арифметические операции и числа\n
 * \note
 * Одно число - одна лексема\n
 * Одна цифра это не лексема
 */
struct Lexem
{
    int type; ///< Равен одному из значений из Type_Literal
    int value; ///< Это поле осмысленно только когда type = NUMBER
};

/**
 * \brief Вызывается если арифметическое выражение некорректно
 *
 * В результате работа всей программы завершается
 */
static void syntax_error(void)
{
    printf("syntax error\n");
    exit(EXIT_SUCCESS);
}

/**
 * \brief Вызывается в случае деления на ноль
 *
 * В результате работа всей программы завершается
 */
static void division_zero(void)
{
    printf("division by zero\n");
    exit(EXIT_SUCCESS);
}

/**
 * \brief Проверяет валидность символа в арифметическом выражении
 *
 * \param[in] symbol символ из арифметического выражения
 * \return Является ли символ допустимым для арифметического выражения
 */
static bool valid_character(char symbol)
{
    return isdigit(symbol) or symbol == '+' or symbol == '-' or symbol == '/' or
           symbol == '*' or symbol == '(' or symbol == ')';
}

/**
 * \brief Перевод цифры из char в int
 *
 * \param[in] number символ цифры которую необходимо перевести в int
 * \return цифра в типе int
 */
static int todigit(char number)
{
    return number - '0';
}

/**
 * \brief Совершает переход к следующей лексеме
 *
 * \param[out] current указатель на текущую лексему\n
 * \param[in,out] element_expression указатель на символ следующий за лексемой на которую указывает current
 */
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

    if (!valid_character(**element_expression))
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

/**
 * \brief Вычисляет значение множителя
 *
 * \param[in,out] current указатель на текущую лексему\n
 * \param[in,out] element_expression указатель на символ следующий за началом лексемы на которую указывает current\n
 * \return Значение множителя которое начинается с лексемы на которую указывает current
 */
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

/**
 * \brief Вычисляет значение слагаемого
 *
 * \param[in,out] current указатель на текущую лексему\n
 * \param[in,out] element_expression указатель на символ следующий за началом лексемы на которую указывает current\n
 * \return Значение слагаемого которое начинается с лексемы на которую указывает current
 */
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

/**
 * \brief Вычисляет значение выражения
 *
 * \param[in,out] current указатель на текущую лексему\n
 * \param[in,out] element_expression указатель на символ следующий за началом лексемы на которую указывает current\n
 * \return Значение выражения которое начинается с лексемы на которую указывает current
 */
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
