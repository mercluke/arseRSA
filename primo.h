/*******************************************
***Methods to pick a random number with a***
*****99.99999997% chance of being prime*****
********************************************/
#ifndef PRIMO_H
#define PRIMO_H

#include "modexp.h"
#include "seed.h"
#include <stdlib.h>
#include <stdint.h>

int likelyPrime(int64_t input);
int64_t getPrime(void);

/*Number of iterations for primeCheck*/
#define T 25

#endif
