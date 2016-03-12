#include "seed.h"

/*abusing static to ensure rand only seeded once*/
void seed(void)
{
	static char didSeed = 0;

	if(!seed)
	{
		srand(time(NULL));
		didSeed = 1;
	}
}
