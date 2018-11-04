#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void swap (int* a, int* b);
void swap (int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void quick_sort (int *array, int left, int right);
static void quick_sort (int *array, int left, int right) // using Hoare partition scheme
{
    if (left < right)
    {
        int pivot = array[left];
        int left_cursor = left - 1;
        int right_cursor = right + 1;

        do
        {
            do
            {
                ++left_cursor;
            }
            while (array[left_cursor] < pivot);

            do
            {
                --right_cursor;
            }
            while (array[right_cursor] > pivot);

            if (left_cursor < right_cursor)
            {
                swap (&array[left_cursor], &array[right_cursor]);
            }
        }
        while (left_cursor < right_cursor);

        quick_sort (array, left, right_cursor);
        quick_sort (array, right_cursor + 1, right);
    }
}

int main(void)
{
    int n;
    scanf ("%d", &n);
    int* array = malloc (sizeof(int) * (size_t)n);
    if (array == NULL)
    {
        errno = ENOMEM;
        perror("No Memory\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; ++i)
    {
        scanf ("%d", &array[i]);
    }
    quick_sort (array, 0, n - 1);
    for (int i = 0; i < n; ++i)
    {
        printf ("%d ", array[i]);
    }
    printf ("\n");
    free (array);
    return 0;
}
