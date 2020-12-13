#pragma once

#include "hanoi.h"

/*
 * Frame–Stewart algorithm implementation which is
 * a type of divide-and-conquer algorithm with a
 * standard recursive algorithm at the bottom.
 * 
 * Steps:
 * 1. Divide elements count in half and move 1st half to
 *    rod other than source or destination
 * 2. Without disturbing the rod with 1st half move rest
 *    of the elements from source to destination rod
 * 3. Move 1st half to destination rod
 * 
 * Warning: return != 0 will leak memory, crash immediately!
 */
int HanoiAlg(HanoiTower_t *tower, unsigned long *moves);