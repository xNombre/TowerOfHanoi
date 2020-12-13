// Andrzej Perczak
// PWr 2020

#include "hanoi.h"
#include "hanoi_alg.h"
#include <stdio.h>

int main()
{
    HanoiTower_t *tower = NULL;
    rod_t **tab;
    unsigned element_count, rods, a, b;
    int ret, i;
    char l;

    printf("Element count: ");
    scanf("%ud", &element_count);

    if (element_count == 0) {
        ret = -5;
        goto err;
    }

    printf("Rods count: ");
    scanf("%ud", &rods);

    if (rods == 0) {
        ret = -5;
        goto err;
    }

    ret = InitializeTower(&tower, element_count, rods);
    if (ret)
        goto err;

re1:
    printf("Choose mode auto/manual: (a/m)\n");
    scanf(" %c", &l);

    if (l == 'a') {
        if (rods >= 3) {
            unsigned long moves = 0;
            DrawHanoi(tower);

            ret = HanoiAlg(tower, &moves);
            if (ret)
                goto err;

            printf("Completed with %lu moves!\n", moves);
            FreeTower(tower);

            return 0;
        }
    } else if (l == 'm') {
    re2:
        printf("Choose action move/print/exit: m/p/e\n");
        scanf(" %c", &l);

        switch (l) {
        case 'm':
            printf("Type src and dst rod: ");
            scanf("%u %u", &a, &b);
            if (a > rods || b > rods) {
                ret = -4;
                goto err;
            }

            ret = MoveElement(tower->rod[--a], tower->rod[--b]);
            if (ret)
                goto err;
            break;
        case 'p':
            DrawHanoi(tower);
            break;
        case 'e':
            FreeTower(tower);
            return 0;
            break;
        }
        goto re2;
    }

    goto re1;

err:
    printf("Error: %d", ret);
    return ret;
}