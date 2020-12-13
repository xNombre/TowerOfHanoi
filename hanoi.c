#include "hanoi.h"
#include <stdio.h>
#include <stdlib.h>

int AddElement(rod_t *rod, unsigned int size);
int InitializeTower(HanoiTower_t **tower_ptr, unsigned int elem_count, unsigned int rod_count)
{
    int ret = 0;
    unsigned i;
    rod_t *rod;
    HanoiTower_t *tower;

    *tower_ptr = (HanoiTower_t *)malloc(sizeof(HanoiTower_t) + rod_count * sizeof(rod_t *));
    if (!*tower_ptr)
        return -ENOMEM;

    tower = *tower_ptr;

    tower->max_size = elem_count;
    tower->rods = rod_count;

    for (i = 0; i < rod_count; i++) {
        rod = (rod_t *)malloc(sizeof(rod_t));
        if (!rod)
            goto err_rod_malloc;

        rod->head = NULL;
        rod->last = NULL;
        rod->num = i + 1;
        tower->rod[i] = rod;
    }

    while (elem_count && !ret)
        ret = AddElement(tower->rod[0], elem_count--);

    return ret;

err_rod_malloc:
    // Free rods that were created before err
    i = 0;
    while (tower->rod[i])
        free(tower->rod[i++]);
    free(tower);
    return -ENOMEM;
}

void FreeTower(HanoiTower_t *tower)
{
    rod_t *rod;

    for (int i = 0; i < tower->rods; i++) {
        rod = tower->rod[i];

        if (rod->head) {
            element_t *elem = rod->head;
            while (elem) {
                element_t *to_free = elem;
                elem = elem->next;
                free(to_free);
            }
        }
        free(rod);
    }

    free(tower);
}

int MoveElement(rod_t *src, rod_t *dst)
{
    element_t *prev;

    // Sanity checks
    if (!src || !src->head || !dst)
        return -ENOELEM;

    if (src == dst)
        return 0;

    // Larger element can't be placed on smaller one
    if (dst->head && dst->last->size < src->last->size)
        return -EBADMOVE;

    if (!dst->head) {
        dst->last = src->last;
        dst->head = src->last;
    } else {
        dst->last = src->last;
        prev = dst->head;
        while (prev->next)
            prev = prev->next;
        prev->next = src->last;
    }

    prev = src->head;
    if (prev->next) {
        while (prev->next != src->last)
            prev = prev->next;
        prev->next = NULL;
        src->last = prev;
    } else {
        src->head = NULL;
        src->last = NULL;
    }

    return 0;
}

int AddElement(rod_t *rod, unsigned int size)
{
    element_t *elem;

    elem = (element_t *)malloc(sizeof(element_t));
    if (!elem)
        return -ENOMEM;

    elem->size = size;
    elem->next = NULL;

    if (!rod->head)
        rod->head = elem;
    else
        rod->last->next = elem;

    rod->last = elem;

    return 0;
}

#define separator(n)                     \
    for (unsigned int i = 0; i < n; i++) \
        printf(" ");
#define element(n)                       \
    for (unsigned int i = 0; i < n; i++) \
        printf("=");

void DrawHanoi(HanoiTower_t *tower)
{
    unsigned size = tower->max_size;
    unsigned len, i, j, elem_count;
    unsigned long cnt;
    element_t *elem;

    separator(1);

    for (i = 0; i < tower->rods; i++) {
        separator(size);
        printf("^");
        separator(size);
    }
    printf("\n");

    for (i = 0; i < size; i++) {
        separator(1);
        for (j = 0; j < tower->rods; j++) {
            elem = tower->rod[j]->head;
            elem_count = 0;
            if (elem) {
                elem_count++;
                while (elem->next) {
                    elem_count++;
                    elem = elem->next;
                }
            }

            if ((long)(size - elem_count) - 1 < (long)i) {
                elem = tower->rod[j]->head;
                for (cnt = abs((long)i - (long)size + 1); cnt > 0; cnt--)
                    elem = elem->next;

                len = elem->size;
                separator(size - len);
                element(len * 2 + 1);
                separator(size - len);
            } else {
                separator(size);
                printf("|");
                separator(size);
            }
        }
        printf("\n");
    }

    printf("<");
    for (i = 0; i < size * tower->rods * 2 + tower->rods; i++)
        printf("=");
    printf(">\n\n");
}