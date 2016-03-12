#ifndef SEED_H
#define SEED_H

/*******************************************
***Ensure rand() is only ever seeded once***
*******************************************/

#include <stdlib.h>
#include <time.h>

void seed(void);

#endif
