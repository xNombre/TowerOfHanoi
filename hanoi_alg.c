#include "hanoi_alg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int no_printf(const char *format, ...)
{
    return 0;
}

#if DEBUG
#define pr_debug printf
#else
#define pr_debug no_printf
#endif

/*
 * Spare rods array will always hold no more than (number of rods - 2) entries 
 * Add one more as null-terminator
 */
#define spare_rods_array_size(tower) (sizeof(rod_t *) * (tower->rods - 1))

/*
 * Known recursive algorithm for standard Tower of Hanoi (3 rods)
 * Kept for reference
 */
void __HanoiAlg(HanoiTower_t *tower, unsigned int size, rod_t *a, rod_t *b, rod_t *c)
{
    if (size == 1) {
        MoveElement(a, c);
        DrawHanoi(tower);
    } else {
        __HanoiAlg(tower, size - 1, a, c, b);
        MoveElement(a, c);
        DrawHanoi(tower);
        __HanoiAlg(tower, size - 1, b, a, c);
    }
}

rod_t *pop_rod(rod_t *arr[])
{
    unsigned i = 0;
    rod_t *ret;

    while (arr[i + 1])
        i++;

    ret = arr[i];
    arr[i] = NULL;

    return ret;
}

void push_rod(rod_t *arr[], rod_t *rod)
{
    unsigned i = 0;

    while (arr[i])
        i++;

    arr[i] = rod;
}

unsigned rods_count(rod_t *arr[])
{
    unsigned i = 0;

    while (arr[i + 1])
        i++;

    return i + 1;
}

void print_stack(rod_t *arr[], const char *move_num)
{
    unsigned i = 0;

    pr_debug("Stack: ");
    while (arr[i])
        pr_debug("%d ", arr[i++]->num);

    pr_debug("; %s\n", move_num);
}

/*
 * There is a need to keep track of spare rods for
 * algorithm to function properly thus create a
 * simple-stupid stack-like array for this purpose.
 * 
 * It also has to be copied upon every recursive 
 * call otherwise it wrecks up current iteration.
 */
int HanoiAlg_recursion(HanoiTower_t *tower, unsigned elem_count, rod_t *src, rod_t *dst, rod_t *spare_rods[], unsigned long *moves)
{
    int ret;
    unsigned pivot;
    rod_t *spare;
    rod_t **spare_rods_copy;

    if (elem_count == 1) {
        ret = MoveElement(src, dst);
        pr_debug("Move: %u to %u, ret = %d\n", src->num, dst->num, ret);

        if (ret)
            return ret;

        (*moves)++;
        DrawHanoi(tower);
    } else {
        spare_rods_copy = malloc(spare_rods_array_size(tower));
        if (!spare_rods_copy)
            return -ENOMEM;

        // Until there are enough rods cut elements count in half
        if (rods_count(spare_rods) >= 2)
            pivot = elem_count / 2;
        else
            pivot = elem_count - 1;

        // Move pivot from src to spare rod
        spare = pop_rod(spare_rods);
        push_rod(spare_rods, dst);
        print_stack(spare_rods, "m1");

        memcpy(spare_rods_copy, spare_rods, spare_rods_array_size(tower));
        ret = HanoiAlg_recursion(tower, pivot, src, spare, spare_rods_copy, moves);
        if (ret)
            return ret;

        // Move rest of elements from src to dst rod
        pop_rod(spare_rods);
        print_stack(spare_rods, "m2");

        memcpy(spare_rods_copy, spare_rods, spare_rods_array_size(tower));
        ret = HanoiAlg_recursion(tower, elem_count - pivot, src, dst, spare_rods_copy, moves);
        if (ret)
            return ret;

        // Move pivot to dst rod
        push_rod(spare_rods, src);
        print_stack(spare_rods, "m3");

        memcpy(spare_rods_copy, spare_rods, spare_rods_array_size(tower));
        ret = HanoiAlg_recursion(tower, pivot, spare, dst, spare_rods_copy, moves);
        if (ret)
            return ret;

        free(spare_rods_copy);
    }

    return 0;
}

int HanoiAlg(HanoiTower_t *tower, unsigned long *moves)
{
    int ret;
    rod_t **spare_rods;

    spare_rods = malloc(spare_rods_array_size(tower));
    if (!spare_rods)
        return -ENOMEM;

    memset(spare_rods, 0, spare_rods_array_size(tower));

    // Spare rods are all rods between src and dest
    for (unsigned i = tower->rods - 2; i > 0; i--)
        spare_rods[tower->rods - 2 - i] = tower->rod[i];

    ret = HanoiAlg_recursion(tower, tower->max_size, tower->rod[0], tower->rod[tower->rods - 1], spare_rods, moves);

    free(spare_rods);
    return ret;
}