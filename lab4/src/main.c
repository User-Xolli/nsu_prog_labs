/**
 * \file
 * \brief Файл с пользовательским вводом и вызовом функции вычисляющей введённое выражение
 */

#include <stdlib.h>
#include <stdio.h>

#include "calculator.h"

#define MAX_LEN 1001 ///< Максимальная допустимая длина ввода

int main(void)
{
    char main_expression[MAX_LEN] = {0};
    fread(main_expression, sizeof(char), MAX_LEN, stdin);
    printf("%d\n", calculator(main_expression));
    return EXIT_SUCCESS;
}

/**
 * \mainpage Лабораторная работа №4, НГУ ФИТ 1 курс
 * \author Xolli
 * \date 22.12.2018
 * \version 4
 *
 * Моя первая в жизни документация)
 */
