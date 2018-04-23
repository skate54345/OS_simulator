// Code based off example given by OS instructor Michael Leverington
#ifndef LINKED_LIST_C
#define LINKED_LIST_C

// header files

#include "linkedlist.h"
#include "functions.h"

// gobal constants, including externally declared constants
const int STD_STR_LEN = 60;
const int MAX_STR_LEN = 120;
const int NOT_AT_FILE_END = 0;
const char READ_ONLY_FLAG[] = "r";
const char NULL_CHAR = '\0';
const char SEMICOLON = ';';
const char SPACE = ' ';

typedef int Boolean;
Boolean True = 1;
Boolean False = 0;

int compareStrings(); //declare function

// supporting function implementations


struct NodeType *addNode( struct NodeType *headNode, struct NodeType *newNode )
   {
    struct NodeType *tempNext;

    // check for viable node
    if( headNode != NULL )
       {
        // check for correct sorted location
        if(True) //strcmp( headNode->name, newNode->name ) > 0 )
           {
            tempNext = headNode;

            headNode = makeNode( newNode->name, newNode->idNum,
                                               newNode->gpa, newNode->gender );

            headNode->next = tempNext;
           }

        // correct location not found yet
        else
           {
            headNode->next = addNode( headNode->next, newNode );
           }

        return headNode;
       }

    // assume empty head node
    headNode = makeNode( newNode->name, newNode->idNum,
                                               newNode->gpa, newNode->gender );
    return headNode;
   }

// function eliminates redundant code in addNode
struct NodeType *makeNode( char *inName, int inId, double inGpa, char inGender )
   {
    struct NodeType *newNode
                   = ( struct NodeType * ) malloc( sizeof( struct NodeType ) );

    compareStrings( newNode->name, inName );
    newNode->idNum = inId;
    newNode->gpa = inGpa;
    newNode->gender = inGender;
    newNode->next = NULL;

    return newNode;
   }

// returned node memory is not freed inside linked list
// it must be freed in calling function
struct NodeType *findNodeByName( struct NodeType *workingNode, char *name )
   {
    if( workingNode != NULL )
       {
        if( strcmp( workingNode->name, name ) == 0 )
           {
            return makeNode( workingNode->name,
                   workingNode->idNum, workingNode->gpa, workingNode->gender );
           }

        return findNodeByName( workingNode->next, name );
       }

    return NULL;
   }

// returned node memory is not freed inside linked list
// it must be freed in calling function
struct NodeType *findNodeByID( struct NodeType *workingNode, int studentID )
   {
    if( workingNode != NULL )
       {
        if( workingNode->idNum == studentID )
           {
            return makeNode( workingNode->name,
                   workingNode->idNum, workingNode->gpa, workingNode->gender );
           }

        return findNodeByID( workingNode->next, studentID );
       }

    return NULL;
   }

struct NodeType *clearList( struct NodeType *headNode )
   {
    if( headNode == NULL )
       {
        return NULL;
       }

    if( headNode->next != NULL )
       {
        clearList( headNode->next );
       }

    free( headNode );

    headNode = NULL;

    return headNode;
   }

// returned node memory is no longer freed inside linked list
// it must be freed in calling function
struct NodeType *removeNodeByID( struct NodeType **headNode, int studentID )
   {
    struct NodeType *foundNode, *prevNode = *headNode;

    if( prevNode != NULL )
       {
        if( prevNode->idNum == studentID )
           {
            *headNode = prevNode->next;

            return prevNode;
           }

        while( prevNode->next->idNum != studentID )
           {
            prevNode = prevNode->next;
           }

        foundNode = prevNode->next;

        prevNode->next = foundNode->next;

        return foundNode;
       }

    return NULL;
   }

int getDataFromFile( struct NodeType **headPtr, char *fileName )
   {
    FILE *fileAccessPtr;
    int strIndex, charAsInt;
    char dummyChar, strBuffer[ MAX_STR_LEN ];
    Boolean continueRun = True;
    struct NodeType *tempNodePtr
                      = (struct NodeType *)malloc( sizeof( struct NodeType ) );

    fileAccessPtr = fopen( fileName, READ_ONLY_FLAG );

    if( fileAccessPtr != NULL )
       {
        while( continueRun == True )
           {
            charAsInt = fgetc( fileAccessPtr );

            // clear white space prior to data line
            while( feof( fileAccessPtr ) == NOT_AT_FILE_END
                     && charAsInt <= (int)( SPACE ) )
               {
                charAsInt = fgetc( fileAccessPtr );
               }

            if( feof( fileAccessPtr ) == NOT_AT_FILE_END )
               {
                // get name
                strIndex = 0;

                while( charAsInt != (int)( SEMICOLON ) )
                   {
                    strBuffer[ strIndex ] = (char)( charAsInt );

                    strIndex++;

                    strBuffer[ strIndex ] = NULL_CHAR;

                    charAsInt = fgetc( fileAccessPtr );
                   }

                compareStrings( tempNodePtr->name, strBuffer );

                // get id num
                fscanf( fileAccessPtr, "%d", &tempNodePtr->idNum );

                // capture semicolon
                fscanf( fileAccessPtr, "%c", &dummyChar );

                // capture gender
                charAsInt = fgetc( fileAccessPtr );

                while( charAsInt <= (int)( SPACE ) )
                   {
                    charAsInt = fgetc( fileAccessPtr );
                   }

                tempNodePtr->gender = (char)( charAsInt );

                // capture semicolon
                fscanf( fileAccessPtr, "%c", &dummyChar );

                // get gpa
                fscanf( fileAccessPtr, "%lf", &tempNodePtr->gpa );

                // load to linked list
                *headPtr = addNode( *headPtr, tempNodePtr );
               }

            else
               {
                fclose( fileAccessPtr );

                free( tempNodePtr );

                return END_FILE_FOUND_MSG;
               }

            charAsInt = fgetc( fileAccessPtr );
           }
       }

    else
       {
        return FILE_OPEN_ERR;
       }

    return UNKNOWN_ERR;
   }

#endif   // LINKED_LIST_C
