#pragma once

/*
 *       ^       ^       ^
 *      ===      |       |     < last
 *       .       .       .     < head->next->...->next
 *     =====     |       |     < head->next
 *    =======    |       |     < head
 *  <=========================>
 */

typedef struct element
{
    unsigned int size;
    struct element *next;
} element_t;

typedef struct rod
{
    element_t *head;
    element_t *last;
    unsigned int num;
} rod_t;

typedef struct HanoiTower
{
    unsigned int max_size;
    unsigned int rods;
    rod_t *rod[];
} HanoiTower_t;

enum
{
    ENOMEM = 1,
    EBADMOVE,
    ENOELEM,
};

int InitializeTower(HanoiTower_t **tower, unsigned int elem_count, unsigned int rod_count);
void FreeTower(HanoiTower_t *tower);

int MoveElement(rod_t *src, rod_t *dst);

void DrawHanoi(HanoiTower_t *tower);