/*******************************************
***Methods to pick a random number with a***
*****99.99999997% chance of being prime*****
********************************************/
#include "primo.h"

int likelyPrime(int64_t input)
{
	int64_t random;
	int64_t exponent;
	int64_t expmod;
	int isPrime = 1;
	int i;
	
	seed();

	/***********************************
	Each iteration halves the likelyhood
	that 'input' is not prime. 
	***********************************/
	for(i = 0; i < T; i++)
	{
		random = (rand()%input)+1;
		exponent = (input-1)/2;

		expmod = modExp(random, exponent, input);
		

		if(!(expmod == 1 || expmod == (input-1)))
		{
			isPrime = 0;
			break;
		}
	}

	return isPrime;
}

int64_t getPrime(void)
{
	int64_t primeNum;

	do 
	{
		primeNum = (rand()%9000)+1000;
	}
	while(!likelyPrime(primeNum));

	return primeNum;
}
