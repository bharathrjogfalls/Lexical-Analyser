#ifndef MAIN
#define MAIN

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// function prototypes

/* lexical_analyser analyses file content */
int lexical_analyser(char * file_name);

int keyword(char * line);

int analyse(char *line);

int identify(char * line);

int isSpecialChar(char c);

int isBracket(char c);

int isOperator(char c);

int isNumber(char* str);

#endif