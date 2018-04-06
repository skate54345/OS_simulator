// Header file for linkedlist.c
// Code modified from example given by OS instructor Michael Leverington

// Precompiler directive, to eliminate multiple compiles of h file
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// header files
#define GNU_SOURCE
#include <stdio.h>  // I/O
#include <stdlib.h>  // malloc
#include <string.h>  // string management

// Global Constants
extern const int STD_STR_LEN;
extern const int MAX_STR_LEN;

// Message codes for file access
enum MESSAGE_CODES { UNKNOWN_ERR = -1000, FILE_OPEN_ERR,
                   INCOMPLETE_FILE_ERR, NO_ERROR_MSG = 0,
                   END_FILE_FOUND_MSG };

// global constants, forward declaration

// struct declaration
struct NodeType
   {
    char component_letter[40];
    char operation_string[40];
    char cycle_time[40];
    int process_num[40];
    char end[20];
    char name[ 60 ]; // hard-coded STD_STR_LEN since it is not declared yet
    int idNum;
    double gpa;
    char gender;

    struct NodeType *next;
   };

// function prototypes

struct NodeType *addNode( struct NodeType *headNode, struct NodeType *newNode );
struct NodeType *clearList( struct NodeType *headNode );
struct NodeType *makeNode( char *inName, int inId, double inGpa, char inGender );
struct NodeType *findNodeByName( struct NodeType *workingNode, char *name );
struct NodeType *findNodeByID( struct NodeType *workingNode, int studentID );
struct NodeType *removeNodeByID( struct NodeType **workingNode, int studentID );
int getDataFromFile( struct NodeType **headPtr, char *fileName );

#endif // LINKED_LIST_H
