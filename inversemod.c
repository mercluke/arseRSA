#include "inversemod.h"


/********************************************************
Find modular inverse of 'a' where (a*b)%m == 1***********
Equation adapted from psuedocode retreived from**********
http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
********************************************************/
int64_t findModularInverse(int64_t a, int64_t m)
{
	int64_t newT = 1;
	int64_t tmp;
	int64_t newR = a;
	int64_t r = m;
	int64_t t = 0;

	if(findGCD(a, m) == 1)
	{
		while(newR != 0)
		{
			int64_t quotient = r/newR;
			tmp = t;
			t = newT;
			newT = tmp-(quotient*newT);
			tmp = r;
			r = newR;
			newR = tmp - (quotient*newR);
		}
		if(t < 0)
		{
			t += m;
		}
	}

	return t;
}


/******************************************
Find greatest common divisor of two numbers
******************************************/
int64_t findGCD(int64_t a, int64_t b)
{
	int64_t tmp;

	while(a % b)
	{
		tmp = a;
		a = b;
		b = tmp % a;
	}

	return b;
}
