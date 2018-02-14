#ifndef MAIN_TEST_C
#define MAIN_TEST_C

// header definitions
#include "linkedlist.h"
#include "linkedlist.c"


int main( int argc, char **argv )
   {
    struct NodeType *workingPtr, *headPtr = NULL;
    // data node created, must be released
    struct NodeType *dataPtr
                    = ( struct NodeType * )malloc( sizeof( struct NodeType ) );
    int resultCode;
    char fileName[ STD_STR_LEN ];

    // add data value
    strcpy( dataPtr->name, "Johnson, Robert" );
    dataPtr->idNum = 603667;
    dataPtr->gpa = 2.844077875;
    dataPtr->gender = 'M';
    headPtr = addNode( headPtr, dataPtr );

    // add data value
    strcpy( dataPtr->name, "Elliott, Cayley" );
    dataPtr->idNum = 135658;
    dataPtr->gpa = 2.978848017;
    dataPtr->gender = 'F';
    headPtr = addNode( headPtr, dataPtr );

    // add data value
    strcpy( dataPtr->name, "Reyes, Connor" );
    dataPtr->idNum = 191261;
    dataPtr->gpa = 3.295578577;
    dataPtr->gender = 'M';
    headPtr = addNode( headPtr, dataPtr );

    // add data value
    strcpy( dataPtr->name, "Sanchez, Susan" );
    dataPtr->idNum = 154838;
    dataPtr->gpa = 2.063213296;
    dataPtr->gender = 'F';
    headPtr = addNode( headPtr, dataPtr );

    // add data value
    strcpy( dataPtr->name, "Penn, Frederick" );
    dataPtr->idNum = 819367;
    dataPtr->gpa = 2.828974752;
    dataPtr->gender = 'M';
    headPtr = addNode( headPtr, dataPtr );

    // display linked list
    workingPtr = headPtr;

    while( workingPtr != NULL )
       {
        printf( "Name: %s; \tID: %d; \tGPA: %4.2f\n",
                        workingPtr->name, workingPtr->idNum, workingPtr->gpa );

        workingPtr = workingPtr->next;
       }

    // pointer is returned with node data, memory must be released
    workingPtr = findNodeByName( headPtr, "Penn, Frederick" );
    printf( "Found by Name:\n\t Name: %s; ID: %d; GPA: %4.2f\n",
                        workingPtr->name, workingPtr->idNum, workingPtr->gpa );
    free( workingPtr );

    // pointer is returned with node data, memory must be released
    workingPtr = findNodeByID( headPtr, 191261 );
    printf( "Found by Student ID:\n\t Name: %s; ID: %d; GPA: %4.2f\n",
                        workingPtr->name, workingPtr->idNum, workingPtr->gpa );
    free( workingPtr );

    // head pointer passed as reference in case it is changed inside function
    // pointer is returned with node data, memory must be released
    workingPtr = removeNodeByID( &headPtr, 135658 );
    printf( "Removed by Student ID:\n\t Name: %s; ID: %d; GPA: %4.2f\n",
                        workingPtr->name, workingPtr->idNum, workingPtr->gpa );
    free( workingPtr );

    // display linked list
    workingPtr = headPtr;

    while( workingPtr != NULL )
       {
        printf( "Name: %s; \tID: %d; \tGPA: %4.2f\n",
                        workingPtr->name, workingPtr->idNum, workingPtr->gpa );

        workingPtr = workingPtr->next;
       }

    // clear list
    headPtr = clearList( headPtr );

    // clear data in data pointer node
    free( dataPtr );

    // check number of arguments found on command line
    if( argc > 1 )
       {
        // copy file name in from command line
        strcpy( fileName, argv[ 1 ] );

        // upload data from file given in command line
        resultCode = getDataFromFile( &headPtr, fileName  );

        // check for successful data upload
        if( resultCode == END_FILE_FOUND_MSG )
           {
            workingPtr = headPtr;

            while( workingPtr != NULL )
               {
                printf( "Name: %s; \tID: %d; \tGPA: %4.2f\n",
                       workingPtr->name, workingPtr->idNum, workingPtr->gpa );

                workingPtr = workingPtr->next;
               }

            clearList( headPtr );
           }
       }

    else
       {
        printf( "File name not found, " );
        printf( "must be placed as a command line argument\n" );
       }

    return 0;
   }

#endif // MAIN_TEST_C
