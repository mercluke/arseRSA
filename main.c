#include "main.h"

int main(int argc, char **argv)
{
	/************************
	***Seed rand only once***
	*************************/
	seed();

	n = 0;
	inFile = outFile = NULL;
	modeFunc = NULL;

	readArgs(argc-1, argv+1);

	populate();

	/**************************
	***Attempt to open files***
	**************************/
	input = fopen(inFile, "rb");
	if(!input)
	{
		printf("Problem opening %s for reading\n\n", inFile);
		help();
	}
	output = fopen(outFile, "wbcat");
	if(!output)
	{
		printf("Problem opening %s for writing\n\n", outFile);
		help();
	}


	/****************************
	***Perform {En,De}cryption***
	****************************/
	while(modeFunc() != EOF);

	printf( "Operation complete!\n");
	
	return 0;
}

/*************************************************
*** Encyption and Decryption are both the same ***
*** Operation, however encryption reads in 2 *****
*** bytes and writes out 4 bytes, decryption *****
*** reads in 4 bytes and writes out 2 bytes ******
*************************************************/
int encrypt(void)
{
	int c, i;
	int64_t plaintext = 0;
	int64_t ciphertext;
	int retVal = 0;

	for(i = 0; i < 2; i++)
	{
		c = fgetc(input);
		if(c == EOF)
		{
			retVal = EOF;
			break;
		}
		else
		{
			plaintext += c << (1-i)*8;
		}
	}

	if(plaintext != 0)
	{
		ciphertext = modExp(plaintext, e, n);

		for(i = 0; i < 4; i++)
		{
			char c;
			c = ciphertext >> (3-i)*8;
			fputc(c, output);
		}
	}

	//close files when done
	if(retVal == EOF)
	{
		fclose(input);
		fclose(output);
	}

	return retVal;
}


int decrypt(void)
{
	int c, i;
	int64_t plaintext;
	int64_t ciphertext = 0;
	int retVal = 0;

	for(i = 0; i < 4; i++)
	{
		c = fgetc(input);
		if(c == EOF)
		{
			retVal = EOF;
			break;
		}
		else
		{
			ciphertext += c << (3-i)*8;
		}
	}

	if(ciphertext != 0)
	{
		plaintext = modExp(ciphertext, d, n);

		for(i = 0; i < 2; i++)
		{
			char c;
			c = plaintext >> (1-i)*8;
			if(c != 0)
			{
				fputc(c, output);
			}
		}
	}

	//close files when done
	if(retVal == EOF)
	{
		fclose(input);
		fclose(output);
	}

	return retVal;

}


/*******************************
*** Parse command line flags ***
*******************************/
void readArgs(int argc, char **argv)
{
	while(argc > 0)
	{
		switch(argv[0][1])
		{
			//Key file
			case 'k':
				readKeysFromFile(argv[1]);
				argv+=2;
				argc-=2;
			break;

			//Input file
			case 'i':
				inFile = argv[1];
				argv+=2;
				argc-=2;
			break;

			//Output file
			case 'o':
				outFile = argv[1];
				argv+=2;
				argc-=2;
			break;

			//Help
			case 'h':
				help();
			break;

			// case 'd':
			// case 'D':
			// 	modeFunc = decrypt;
			// 	argc--;
			// 	argv++;
			// break;

			// case 'e':
			// case 'E':
			// 	modeFunc = decrypt;
			// 	argc--;
			// 	argv++;
			// break;

			default:
			break;
		}
	}
}

/**************************************
*** Read specified keyfile for keys ***
**************************************/
void readKeysFromFile(char* keyFile)
{
	FILE* keys;

	keys = fopen(keyFile, "rb");

	if(!(keys && (fscanf(keys, "%lld %lld %lld\n", &e,&d,&n) == 3)))
	{
		printf("Problem occured openening keyfile\n\n");
		help();
	}
	else
	{
		fclose(keys);
	}
}


void populate(void)
{

	/*************************
	*** Check if keys have ***
	*** been assigned yet ****
	*** else generate some ***
	*************************/
	if(!n)
	{
		genKeys();
	}


	if(!inFile)
	{
		readFilepath(&inFile, "input file:\n");
	}

	if(!outFile)
	{
		readFilepath(&outFile, "output file:\n");
	}

	/*************************************
	*** Choose whether to {en,de}crypt ***
	*************************************/
	if(!modeFunc)
	{
		char mode;
		printf("Do you want to [E]ncrypt or [D]ecrypt?\n");
		scanf("%c", &mode);

		switch (mode)
		{
			case 'e':
			case 'E':
				modeFunc = encrypt;
			break;
			case 'd':
			case 'D':
				modeFunc = decrypt;
			break;
			default:
				help();
				exit(EXIT_FAILURE);
			break;
		}
	}
}

/*****************************
*** Little helper function ***
*****************************/
void readFilepath(char** str, char *const message)
{
	printf("%s", message);
	*str = readLine(stdin);
}

void genKeys(void)
{
	FILE* keys;

	/******************************
	In the rare case that p == q***
	n would be trivial to factorise
	******************************/
	p = getPrime();
	do
	{
		q = getPrime();
	}
	while(p == q);


	fi_n = (p-1)*(q-1);
	n = p*q;

	

	e = pickE(fi_n);
	d = findModularInverse(e,fi_n);

	printvals();

	keys = fopen("keys.txt", "wb");
	if(keys)
	{
		fprintf(keys, "%lld %lld %lld\n", e,d,n);
		fclose(keys);
		printf("Keys have been saved in \'keys.txt\'\n");
	}
	else
	{
		printf("Error saving keys to \'keys.txt\'\n");
	}
}


/**************************************
*** Method is not needed, just here ***
***** so I could check it worked ******
**************************************/
void printvals(void)
{
	printf( "p:\t\t%lld\n"
			"q:\t\t%lld\n"
			"n:\t\t%lld\n"
			"fi_n:\t\t%lld\n",
			p,q,n,fi_n);

	printf( "e:\t\t%lld\n"
			"d:\t\t%lld\n",
			e,d);


	printf( "Test that keys work\n"
			"letter:\t\t%i\n"
			"encrypted:\t%lld\n"
			"decrypted:\t%i\n", 'a',
			modExp(13, e, n),
			(char)modExp(modExp(13, e, n), d, n));
}


/**********************************
*** Choose an 'E' given fi of n ***
**********************************/
int64_t pickE(int64_t fi_n)
{
	int64_t e;

	do
	{
		e = rand()%fi_n;
	}
	while(findGCD(e, fi_n) != 1);

	return e;
}

/*******************************
*** Print help text for user ***
*******************************/
void help(void)
{
	printf( "usage: [option] filename\n"
						"-o output file\n"
						"-i input file\n"
						"-k key file\n\n");
	exit(EXIT_FAILURE);
}


/**********************************************
*** Some really old code of mine to read in ***
**** a line of unknown length from a file *****
**********************************************/
char* readLine(FILE* file)
{
    /*starter length for line buffer size*/
    int lineBufferLength = 20;
    /*current line position*/
    int count = 0;
    /*create some space for the linebuffer to store text until eol*/
    char* lineBuffer = (char*)malloc(sizeof(char)*lineBufferLength);
    /*read first character on line*/
    int currCh = fgetc(file);

    /*until either end of line or end of file*/
    while(currCh != '\n' && currCh != EOF)
    {
        if(currCh != '\r') /*windows blahblahblah*/
        {
            /*double size of line buffer if too short...*/
            if(count == lineBufferLength-1)
            {
                lineBufferLength *= 2;
                lineBuffer = (char*)realloc(lineBuffer, lineBufferLength);
            }
            
            /*need to typecast to char because we are
            storing as int in order to check for eof*/
            lineBuffer[count] = (char)currCh;
            count++;
        }
        /*move to next character*/
       currCh = fgetc(file);
    }   

    /*terminate the string*/
    lineBuffer[count] = '\0';
    
    /*free any extra space at the end of the string*/
    lineBuffer = (char*)realloc(lineBuffer, (sizeof(char)*++count));
    
    return lineBuffer;
}

