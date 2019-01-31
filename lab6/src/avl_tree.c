/**
 * \file
 * \brief Файл с реализацией АВЛ-дерева
 */

#include "avl_tree.h"
#include <stdlib.h>

/**
 *  \brief Возвращает максимум из двух чисел
 *
 * \param a Первое число
 * \param b Второе число
 * \return Наибольшее из двух чисел
 */
static int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

void initialization(struct avl_tree *root, int data)
{
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    root->height = 1;
}

/**
 * \brief Разница между поддеревьями
 *
 * \note
 * Если поддерево пусто, то его высота равна нулю
 *
 * \param tree указатель на дерево в котором необходимо посчитать разницу высот поддеревьев
 * \return Разницу высот поддеревьев в дереве tree
 */
static int diff_subtrees(struct avl_tree *tree)
{
    int height_left = (tree->left != NULL) ? tree->left->height : 0;
    int height_right = (tree->right != NULL) ? tree->right->height : 0;
    return height_left - height_right;
}

/**
 * \brief Высота дерева
 *
 * \param tree указатель на дерево, высоту которого необходимо посчитать
 */
static void calc_height(struct avl_tree *tree)
{
    int height_left = (tree->left != NULL) ? tree->left->height : 0;
    int height_right = (tree->right != NULL) ? tree->right->height : 0;
    tree->height = max_int(height_left, height_right) + 1;
}

/**
 * \brief Левый поворот
 *
 * \param a вершина, вокруг которой необходимо совершить левый поворот
 * \return возвращает вершину, которая оказалась на том месте, на котором раньше находилась вершина a
 */
static struct avl_tree *turn_left(struct avl_tree *a)
{
    struct avl_tree *b = a->right;
    a->right = b->left;
    b->left = a;
    calc_height(a);
    calc_height(b);
    return b;
}

/**
 * \brief Правый поворот
 *
 * \param a вершина, вокруг которой необходимо совершить правый поворот
 * \return возвращает вершину, которая оказалась на том месте, на котором раньше находилась вершина a
 */
static struct avl_tree *turn_right(struct avl_tree *a)
{
    struct avl_tree *b = a->left;
    a->left = b->right;
    b->right = a;
    calc_height(a);
    calc_height(b);
    return b;
}

/**
 * \brief Балансировка дерева
 *
 * Если разница между высотами поддеревьев составила 2, то дерево перестроиться. Если всё в порядке и разница высот менше двух, то дерево никак не изменится
 *
 * @param tree дерево, которое необходимо сбалансировать
 * @return Указатель на сбалансированное дерево
 */
static struct avl_tree *balance(struct avl_tree *tree)
{
    calc_height(tree);
    if (diff_subtrees(tree) == -2) // left - right = -2
    {
        if (diff_subtrees(tree->right) > 0) // tree->right->left->height > tree->right->right->height
        {
            tree->right = turn_right(tree->right);
        }
        return turn_left(tree);
    }

    if (diff_subtrees(tree) == 2) // left - right = 2
    {
        if (diff_subtrees(tree->left) < 0)  // tree->right->left->height < tree->right->right->height
        {
            tree->left = turn_left(tree->left);
        }
        return turn_right(tree);
    }

    return tree;
}

struct avl_tree *insert(struct avl_tree *root, int value)
{
    if (root == NULL)
    {
        struct avl_tree *tmp = malloc(sizeof(struct avl_tree));
        initialization(tmp, value);
        return tmp;
    }
    if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
    else
    {
        root->left = insert(root->left, value);
    }
    return balance(root);
}

void del_tree(struct avl_tree *root)
{
    if (root->left != NULL)
    {
        del_tree(root->left);
    }
    if (root->right != NULL)
    {
        del_tree(root->right);
    }
    free(root);
}
