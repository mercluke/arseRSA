#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "primo.h"
#include "inversemod.h"
#include "modexp.h"

int64_t p, q, fi_n, n, e, d;
int64_t pickE(int64_t fi_n);
void genKeys(void);
void printvals(void);
void readArgs(int argc, char **argv);
void readFilepath(char **str, char *message);
char* readLine(FILE* file);
void populate();
void readKeysFromFile(char* keyFile);
void help(void);
int encrypt(void);
int decrypt(void);
int (*modeFunc)(void);
FILE* input;
FILE* output;

char *inFile, *outFile;

#endif
