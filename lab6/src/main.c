/**
 * \file
 * \brief Файл с вводом, выводом и построением дерева
 */

#include <stdlib.h>
#include <stdio.h>

#include "avl_tree.h"

int main(void)
{
    int n;
    scanf("%d", &n);
    struct avl_tree *tree = malloc(sizeof(struct avl_tree));
    if (n > 0)
    {
        int tmp;
        scanf("%d", &tmp);
        initialization(tree, tmp);
    }
    else
    {
        printf("0\n");
        free(tree);
        return EXIT_SUCCESS;
    }

    for (int i = 0; i + 1 < n; ++i)
    {
        int tmp;
        scanf("%d", &tmp);
        tree = insert(tree, tmp);
    }
    printf("%d\n", tree->height);
    del_tree(tree);
    return EXIT_SUCCESS;
}

/**
 * \mainpage Лабораторная работа №6, НГУ ФИТ 1 курс
 * \author Xolli
 * \date 31.01.2019
 * \version 1.0
 *
 * Моя вторая в жизни документация)
 */
