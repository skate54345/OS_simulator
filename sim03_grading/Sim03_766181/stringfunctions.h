/* 
 Header file for linkedlist.c
 We will be using standard names for our string functions
 This is to improve readability and comprehension
 Reference for functions was provided by the Public Domain Standard String Header
*/

// Precompiler directive, to eliminate multiple compiles of h file
#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

// header files
#include <stdio.h>  // I/O
#include <stdlib.h>  // malloc
typedef enum Boolean { False, True } Boolean;

// function prototypes

char *( strcat ) ( char * restrict string1, const char * restrict string2 );
char *( strchr ) ( const char *string, int target );
int   ( strcmp ) ( const char *string1, const char *string2);
char *( strcpy ) ( char * string1, const char * string2 );
size_t  strlen   ( const char *string );
char *( strtok ) ( char * restrict string, const char * restrict deliminator );
size_t   strspan    ( const char *string1, const char *string2 );
size_t strcspan ( const char *string1, const char *string2 );
void reverse( char *str );
char* intToString(int num, char* str, int base);
int stringToInt( char * str );
#endif // STRING_FUNCTIONS_H


