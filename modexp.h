/***************************************
***Use right to left binary method to*** 
***determine the result of ((a^b)%c)****
***************************************/
#ifndef MODEXP_H
#define MODEXP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>


int checkSquareOverflow(int64_t input);
int64_t modExp(int64_t b, int64_t e, int64_t m);

#endif
