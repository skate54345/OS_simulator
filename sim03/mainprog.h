// Header file for proggen.c

// Precompiler directive, to eliminate multiple compiles of h file
#ifndef MAINPROG_H
#define MAINPROG_H

// Header files
#include <stdio.h>

// Global Constants

extern const int STD_STR_LEN;
extern const int MAX_STR_LEN;
extern const char NULL_CHAR;
extern const int NUM_CONFIG_ITEMS;

typedef enum { False, True } Boolean;

struct OpCodeData
   {
    char componentLtr;

    char operationStr[ 80 ];

    int cycleTime;

    struct OpCodeData *next;
   };

// function prototypes

void displayByText( int configCode );
void displayErrorByText( int errorCode );
void metaDataFileDump( struct OpCodeData *currentPtr );
void configFileDump( int *configArr, char *mdfFilePath, char *logFilePath );

#endif // MAINPROG_H
