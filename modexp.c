/***************************************
***Use right to left binary method to*** 
***determine the result of ((a^b)%c)****
***************************************/
#include "modexp.h"


/*******************************
Calculates remainder of b^e % m

Note: given an m > sqrt(2^63-1)
this method will fail.  However, 
the assignment specification 
only requires support for values
'with length less than 10 digits'
As such, this method conforms to
specifications.

This implimentation uses the 
'Right to Left' binary method
as opposed to the 'Left to Right'
method described in the book.
This was an arbitrary choice made
purely because this method was 
slightly more intuitive for me 
to understand.
********************************/
int64_t modExp(int64_t base, int64_t exponent, int64_t modulous)
{
	int64_t result = 1;

	/*Assert that (m-1)^2 will not overflow*/
	if(checkSquareOverflow(modulous-1))
	{
		return -1;
	}

	/*b^e % m == (b%m)^e % m*/
	base = base%modulous;

	while(exponent > 0)
	{
		//check least significant bit
		if(exponent % 2)
		{
			result = (result*base)%modulous;
		}
		//Shift to address next bit
		exponent >>= 1;
		base = (base*base)%modulous;
	}



	return result;
}


/************************************
returns true if input^2 will overflow
************************************/
int checkSquareOverflow(int64_t input){
	static int64_t sqrtLLongMax = 0;

	/*cache for next time*/
	if(sqrtLLongMax == 0)
	{
		sqrtLLongMax = sqrt(LLONG_MAX);
	}

	return (input > sqrtLLongMax);
}
