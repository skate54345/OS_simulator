// Header file for linkedlist.c

// Precompiler directive, to eliminate multiple compiles of h file
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// header files
#include "stringfunctions.h"
#include <sys/time.h>

#include <math.h>

// Global Constants
extern const int STD_STR_LEN;
extern const int MAX_STR_LEN;
extern const char RADIX_POINT;
extern const char SPACE;

// Message codes for file access
enum MESSAGE_CODES { UNKNOWN_ERR = -1000, FILE_OPEN_ERR, 
                   INCOMPLETE_FILE_ERR, NO_ERROR_MSG = 0, 
                   END_FILE_FOUND_MSG, INCORRECT_DATA, INCORRECT_NAME };
enum TIMER_CTRL_CODES { ZERO_TIMER, LAP_TIMER, STOP_TIMER };

// global constants, forward declaration

// struct declaration
struct ConfigNodeType
   {
    char name[ 60 ]; // hard-coded STD_STR_LEN since it is not declared yet
    double selectionNum;
    char selectionName[ 60 ];

    struct ConfigNodeType *next;
   };

struct MetaNodeType
   {
    char component;
    int cycleTime;
    char operation[ 60 ];
    

    struct MetaNodeType *next;
   };

// function prototypes
void removeWhiteSpace( FILE * filePtr, int * charAsInt );

// Config node functions
struct ConfigNodeType *addConfigNode( struct ConfigNodeType *headNode, 
                                       struct ConfigNodeType *newNode );
struct ConfigNodeType *clearConfigList( struct ConfigNodeType *headNode );
struct ConfigNodeType *makeConfigNode( char *inName, double inSelectionNum, 
                                            char *inSelectionName );
struct ConfigNodeType *findConfigNodeByName( struct ConfigNodeType *workingNode, 
                                                    char *name );
struct ConfigNodeType *removeConfigNodeByName( struct ConfigNodeType **workingNode, 
                                                      char *name );
char * getString( FILE *filePtr, char *stringBuffer, int * charAsInt, int strIndex );
int getConfigDataFromFile( struct ConfigNodeType **headPtr, char *fileName );

//Meta File functions
struct MetaNodeType *addMetaNode( struct MetaNodeType *headNode, 
                                         struct MetaNodeType *newNode );
struct MetaNodeType *clearMetaList( struct MetaNodeType *headNode );
struct MetaNodeType *makeMetaNode( char inComponent, 
                                        char *inOperation, int inCycleTime );
struct MetaNodeType *findMetaNodeByCompOperat( struct MetaNodeType *workingNode, 
                                                      char component, char *operation );
struct MetaNodeType *removeMetaNodeByCompOper( struct MetaNodeType **workingNode, 
                                                      char component, char *operation );
char *getMetaString( FILE *filePtr, char *strBuffer, int * charAsInt, int strIndex );
int getMetaDataFromFile( struct MetaNodeType **headPtr, char *fileName );

// Timer Prototypes

void * runTimer( void * milliSeconds );
double accessTimer( int controlCode, char *timeStr );
double processTime( double startSec, double endSec, 
                           double startUSec, double endUSec, char *timeStr );
void timeToString( int secTime, int uSecTime, char *timeStr );


#endif // LINKED_LIST_H


