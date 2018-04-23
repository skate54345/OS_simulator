
#ifndef LINKED_LIST_C
#define LINKED_LIST_C

// header files

#include "util_functions.h"

// gobal constants, including externally declared constants
const int STD_STR_LEN = 60;
const int MAX_STR_LEN = 120;
const int NOT_AT_FILE_END = 0;
const char READ_ONLY_FLAG[] = "r";
const char NULL_CHAR = '\0';
const char NEW_LINE_OPERATOR = '\n';
const char SEMICOLON = ';';
const char COLON = ':';
const char SPACE = ' ';
const char OPEN_PAR = '(';
const char CLOSE_PAR = ')';
const char RADIX_POINT = '.';

// supporting function implementations

// These two functions add to our data structures. 
// One for the config file and the other for the Meta-Data file.
struct ConfigNodeType *addConfigNode( struct ConfigNodeType *headNode, 
                                            struct ConfigNodeType *newNode )
   {

    // check for viable node
    if( headNode != NULL )
    {
        headNode->next = addConfigNode( headNode->next, newNode );
       
        return headNode;
    }
    else
    {
       // assume empty head node
       headNode = makeConfigNode( newNode->name, newNode->selectionNum, newNode->selectionName );
       return headNode;
   }
}

struct MetaNodeType *addMetaNode( struct MetaNodeType *headNode, 
                                         struct MetaNodeType *newNode )
   {
   // struct MetaNodeType *tempNext;

    // check for viable node
    if( headNode != NULL )
    {
        headNode->next = addMetaNode( headNode->next, newNode );

        return headNode;
    }
    else 
    {
        // assume empty head node
        headNode = makeMetaNode( newNode->component, newNode->operation, newNode->cycleTime);
        return headNode;
    }
    
   }
///////////////


//////These two reduce code in addNode
struct ConfigNodeType *makeConfigNode( char *inName, double inSelectionNum, 
                                             char *inSelectionName )
   {
    struct ConfigNodeType *newNode
                   = ( struct ConfigNodeType * ) malloc( sizeof( struct ConfigNodeType ) );

    strcpy( newNode->name, inName );
    newNode->selectionNum = inSelectionNum;
    strcpy( newNode->selectionName, inSelectionName );
    newNode->next = NULL;

    return newNode;
   }

struct MetaNodeType *makeMetaNode( char inComponent, char *inOperation, 
                                                          int inCycleTime )
   {
    struct MetaNodeType *newNode
                   = ( struct MetaNodeType * ) malloc( sizeof( struct MetaNodeType ) );

    strcpy( newNode->operation, inOperation );
    newNode->component = inComponent;
    newNode->cycleTime = inCycleTime;
    newNode->next = NULL;

    return newNode;
   }
//////////////

/////// Node Search functions, the Meta node might not be useful but it's good for redundancy
struct ConfigNodeType *findConfigNodeByName( struct ConfigNodeType *workingNode, char *name )
   {
    if( workingNode != NULL )
       {
        if( strcmp( workingNode->name, name ) == 0 )
           {
            return makeConfigNode( workingNode->name, workingNode->selectionNum, workingNode->selectionName );
           }

        return findConfigNodeByName( workingNode->next, name );
       }

    return NULL;
   }

struct MetaNodeType *findMetaNodeByCompOper( struct MetaNodeType *workingNode, 
                                                    char component, char *operation )
   {
    if( workingNode != NULL )
       {
        if( strcmp( workingNode->operation, operation ) == 0 && workingNode->component == component )
           {
            return makeMetaNode( workingNode->component, 
                                 workingNode->operation, workingNode->cycleTime);
           }

        return findMetaNodeByCompOper( workingNode->next, component, operation );
       }

    return NULL;
   }
/////////////////////////


////////// Two functions that clear the data structure ptr lists
struct ConfigNodeType *clearConfigList( struct ConfigNodeType *headNode )
   {

    if( headNode == NULL )
       {

        return NULL;
       }

    if( headNode->next != NULL )
       {

        clearConfigList( headNode->next );
       }

    free( headNode );

    headNode = NULL;

    return headNode;
   }

struct MetaNodeType *clearMetaList( struct MetaNodeType *headNode )
   {
    if( headNode == NULL )
       {
        return NULL;
       }

    if( headNode->next != NULL )
       {
        clearMetaList( headNode->next );
       }

    free( headNode );

    headNode = NULL;

    return headNode;
   }
//////////////////////////


// Node Removal functions
struct ConfigNodeType *removeConfigNodeByID( struct ConfigNodeType **headNode, char *name )
   {
    struct ConfigNodeType *foundNode, *prevNode = *headNode;

    if( prevNode != NULL )
       {
        if( prevNode->name == name )
           {
            *headNode = prevNode->next;

            return prevNode;	
           }

        while( prevNode->next->name != name )
           {
            prevNode = prevNode->next; 
           }

        foundNode = prevNode->next;

        prevNode->next = foundNode->next;

        return foundNode;
       }

    return NULL;
   }

struct MetaNodeType *removeMetaNodeByCompOper( struct MetaNodeType **headNode, char component, 
                                                      char *operation )
   {
    struct MetaNodeType *foundNode, *prevNode = *headNode;

    if( prevNode != NULL )
       {
        if( prevNode->component == component && prevNode->operation == operation )
           {
            *headNode = prevNode->next;

            return prevNode;	
           }

        while( prevNode->next->component != component && prevNode->next->operation != operation )
           {
            prevNode = prevNode->next; 
           }

        foundNode = prevNode->next;

        prevNode->next = foundNode->next;

        return foundNode;
       }

    return NULL;
   }
/////////////////////////////////////

//////// Supporting function to reduce code in our getData functions
void removeWhiteSpace( FILE * filePtr, int * charAsInt )
{
   *charAsInt = fgetc( filePtr );

   while( feof( filePtr ) == NOT_AT_FILE_END && *charAsInt <= ( int )( SPACE ) )
   {
       *charAsInt = fgetc( filePtr );
   }
   
}
//////////////////////

////////// These two functions get strings up to delimiters, there are two
//////     since the meta file treats parentheses differently
char *getString( FILE *filePtr, char *strBuffer, int * charAsInt, int strIndex )
{
   while( (*charAsInt != ( int )( SEMICOLON ) ) && (*charAsInt != ( int )( COLON ) ) 
        && ( *charAsInt != ( int )( NEW_LINE_OPERATOR )) && ( *charAsInt != ( int )( '.' )))
   {
      
      strBuffer[ strIndex ] = ( char )( *charAsInt );

      strIndex++;

      strBuffer[ strIndex ] = '\0';

      *charAsInt = fgetc( filePtr );

   }

   return strBuffer;

}

char *getMetaString( FILE *filePtr, char *strBuffer, int * charAsInt, int strIndex )
{
   while( ( *charAsInt != ( int )( OPEN_PAR ) ) && (*charAsInt != ( int )( CLOSE_PAR ) ) &&
          ( *charAsInt != ( int )( SEMICOLON ) ) && (*charAsInt != ( int )( COLON ) ) && 
          ( *charAsInt != ( int )( NEW_LINE_OPERATOR )) && ( *charAsInt != ( int )( '.' )))
   {
      
      strBuffer[ strIndex ] = ( char )( *charAsInt );

      strIndex++;

      strBuffer[ strIndex ] = '\0';

      *charAsInt = fgetc( filePtr );

   }

   return strBuffer;

}
/////////////////////////////

/////////Main meat of the program, gets the data from the config file and loads it into a linked list 
//       accessible from where it was called
int getConfigDataFromFile( struct ConfigNodeType **headPtr, char *fileName )
  {
   FILE *fileAccessPtr;
   FILE *testFile;
   int strIndex, charAsInt;
   char dummyChar;
   char *strBuffer = ( char * )malloc( sizeof( char ) * MAX_STR_LEN );
   Boolean continueRun = True;
   struct ConfigNodeType *tempNodePtr = ( struct ConfigNodeType * )malloc( sizeof( struct ConfigNodeType ) );


   fileAccessPtr = fopen( fileName, READ_ONLY_FLAG );

   if( fileAccessPtr != NULL )
   {

     while( continueRun == True )
     {
       if( feof( fileAccessPtr ) == NOT_AT_FILE_END )
       {

         //Read in first line and ignore it, advance header
         removeWhiteSpace( fileAccessPtr, &charAsInt );
         
strIndex = 0;
 
         strBuffer =  getString( fileAccessPtr, strBuffer, &charAsInt, strIndex );
                 
         if( strcmp( strBuffer, "Start Simulator Configuration File" ) == 0 )
         {
            //skip
         }
         else if( strcmp( strBuffer, "Version/Phase" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 

            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );
            // get relevant number
            fscanf( fileAccessPtr, "%lf", &tempNodePtr->selectionNum );
            // enter Sel Name Ele: NULL for this
            strcpy( tempNodePtr->selectionName, "" );
            //Cast as an int as specified
            tempNodePtr->selectionNum = (int)tempNodePtr->selectionNum;
         
            if( tempNodePtr->selectionNum >= 0 && tempNodePtr->selectionNum <= 10 )
            {
               // load to linked list
               *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else
            {
              return INCORRECT_DATA;
            }     
   
         }
         else if( strcmp( strBuffer, "File Path" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 
            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );
            // get relevant number
            tempNodePtr->selectionNum = 0;
            fscanf( fileAccessPtr, "%s", tempNodePtr->selectionName );

            if((testFile =fopen( tempNodePtr->selectionName, READ_ONLY_FLAG )))
            {
               fclose( testFile );
               // load to linked list
               *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else
            {
               return INCORRECT_DATA;
            }

         }
         else if( strcmp( strBuffer, "CPU Scheduling Code" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 
            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );

            // get relevant info
            tempNodePtr->selectionNum = 0;
            fscanf( fileAccessPtr, "%s", tempNodePtr->selectionName );
          
            if( strcmp( tempNodePtr->selectionName, "NONE" ) == 0 )
            {
                strcpy( tempNodePtr->name, "FCFS-N" );
                *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else if( strcmp( tempNodePtr->selectionName, "FCFS-N" ) == 0 || 
                     strcmp( tempNodePtr->selectionName, "SJF-N" ) == 0 || 
                     strcmp( tempNodePtr->selectionName, "SRTF-N" ) == 0 || 
                     strcmp( tempNodePtr->selectionName, "FCFS-N" ) == 0 || 
                     strcmp( tempNodePtr->selectionName, "RR-P" ) == 0 )
            {
               // load to linked list
               *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else
            {
              return INCORRECT_DATA;
            }     
         }
         else if( strcmp( strBuffer, "Quantum Time (cycles)" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 

            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );
            // get relevant number
            fscanf( fileAccessPtr, "%lf", &tempNodePtr->selectionNum );
            // enter Sel Name Ele: NULL for this
            strcpy( tempNodePtr->selectionName, "" );

            if( tempNodePtr->selectionNum >= 0 && tempNodePtr->selectionNum <= 100 )
            {
               // load to linked list
               *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else
            {
              return INCORRECT_DATA;
            }  
         }
         else if( strcmp( strBuffer, "Memory Available (KB)" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 
            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );

            // get relevant info
            fscanf( fileAccessPtr, "%lf", &tempNodePtr->selectionNum );
            strcpy( tempNodePtr->selectionName, "" );

            if( tempNodePtr->selectionNum >= 0 && tempNodePtr->selectionNum <= 1048576 )
            {
               // load to linked list
               *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else
            {
              return INCORRECT_DATA;
            }  
         }
         else if( strcmp( strBuffer, "Processor Cycle Time (msec)" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 
            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );
            // get relevant number
            fscanf( fileAccessPtr, "%lf", &tempNodePtr->selectionNum );
            strcpy( tempNodePtr->selectionName, "" );

            if( tempNodePtr->selectionNum >= 0 && tempNodePtr->selectionNum <= 1000 )
            {
               // load to linked list
               *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else
            {
              return INCORRECT_DATA;
            }  
         }
         else if( strcmp( strBuffer, "I/O Cycle Time (msec)" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 
            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );
            // get relevant info
            fscanf( fileAccessPtr, "%lf", &tempNodePtr->selectionNum );
            strcpy( tempNodePtr->selectionName, "" );

            if( tempNodePtr->selectionNum >= 0 && tempNodePtr->selectionNum <= 10000 )
            {
               // load to linked list
               *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else
            {
              return INCORRECT_DATA;
            }  
         }
         else if( strcmp( strBuffer, "Log To" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 
            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );
            // get relevant info
            tempNodePtr->selectionNum = 0;
            fscanf( fileAccessPtr, "%s", tempNodePtr->selectionName );

            if( strcmp( tempNodePtr->selectionName, "Monitor" ) == 0 || 
                strcmp( tempNodePtr->selectionName, "File" ) == 0 || 
                strcmp( tempNodePtr->selectionName, "Both" ) == 0 )
            {
               // load to linked list
               *headPtr = addConfigNode( *headPtr, tempNodePtr );
            }
            else
            {
              return INCORRECT_DATA;
            }  
         }
         else if( strcmp( strBuffer, "Log File Path" ) == 0 )
         {
            strcpy( tempNodePtr->name, strBuffer ); 
            // capture colon
            fscanf( fileAccessPtr, "%c", &dummyChar );
            // get relevant info
            tempNodePtr->selectionNum = 0;
            fscanf( fileAccessPtr, "%s", tempNodePtr->selectionName );

            // load to linked list
            *headPtr = addConfigNode( *headPtr, tempNodePtr );
         }
         else if( strcmp( strBuffer, "End Simulator Configuration File" ) == 0 )
         {

           fclose( fileAccessPtr );

           free( tempNodePtr ); //This gives an error and crashes the program. 
                                  //Ran out of time so know I have mem not freed.

           return END_FILE_FOUND_MSG;           
         }
         else
         {
            fclose( fileAccessPtr ); 

            return INCORRECT_NAME;
         }


       }
       else
       {
          fclose( fileAccessPtr );

          //free( tempNodePtr ); //This gives an error and crashes the program. 
                                  //Ran out of time so know I have mem not freed.

          return END_FILE_FOUND_MSG;
       }
       
      }
   }
   else
   {
      printf("yo look we didn't open the file\n"); //DEBUG CODE
      return FILE_OPEN_ERR;
   }
   
   return UNKNOWN_ERR;
}
//////////////////////

/////Other big function, this gets a linked list for the Meta-file functions
int getMetaDataFromFile( struct MetaNodeType **headPtr, char *fileName )
   {
    FILE *fileAccessPtr;
   int strIndex, charAsInt;
   Boolean first = True;
   int intResult = 0, len = 0;
   char *strBuffer = ( char * )malloc( sizeof( char ) * MAX_STR_LEN );
   Boolean continueRun = True;
   struct MetaNodeType *tempNodePtr = ( struct MetaNodeType * )malloc( sizeof( struct MetaNodeType ) );


   fileAccessPtr = fopen( fileName, READ_ONLY_FLAG );

   if( fileAccessPtr != NULL )
   {

     while( continueRun == True )
     {

       if( feof( fileAccessPtr ) == NOT_AT_FILE_END )

       {

         //Read in first line and ignore it, advance header
         removeWhiteSpace( fileAccessPtr, &charAsInt );
         strIndex = 0;         

         if( first == True )
         {
            strBuffer =  getString( fileAccessPtr, strBuffer, &charAsInt, strIndex ); 
            first = False;
         }
         else
         {
            strBuffer= getMetaString( fileAccessPtr, strBuffer, &charAsInt, strIndex );
            
            
            if( strcmp( strBuffer, "End Program Meta-Data Code" ) != 0 )
            {
               //Parse the letter, and make sure it's correct
               if( strcmp( strBuffer, "S" ) != 0 && strcmp( strBuffer, "A" ) != 0 &&
                   strcmp( strBuffer, "P" ) != 0 && strcmp( strBuffer, "M" ) != 0 &&
                   strcmp( strBuffer, "I" ) != 0 && strcmp( strBuffer, "O" ) != 0 )
               {
                  fclose( fileAccessPtr );
                 
                 // free( tempNodePtr ); This gives an error and crashes the program. 
                                         //Ran out of time so know I have mem not freed.

                  return INCORRECT_NAME;
               }
               //Copy in component letter
               strcpy(&tempNodePtr->component, ( char *)strBuffer );
               removeWhiteSpace( fileAccessPtr, &charAsInt );
   
               strBuffer= getMetaString( fileAccessPtr, strBuffer, &charAsInt, strIndex );           

               //Copy in operation code
               strcpy( tempNodePtr->operation, strBuffer );
               removeWhiteSpace( fileAccessPtr, &charAsInt );
               strBuffer= getMetaString( fileAccessPtr, strBuffer, &charAsInt, strIndex );
 
               //Copy in relevant number for component
               intResult = 0;
               len = strlen( strBuffer );
               for( int count = 0; count < len; count++ )
               {
                  intResult = intResult * 10 + ( strBuffer[count] - '0' ) ;
               }
               tempNodePtr->cycleTime = intResult;           

               //Parsing to make sure that the right letter goes with the right code
               if( ( ( strcmp( &tempNodePtr->component, "S" ) == 0) && 
                         ( strcmp( tempNodePtr->operation, "start" ) == 0)) )
               {
                   *headPtr = addMetaNode( *headPtr, tempNodePtr );
               }
               else if( ( strcmp( &tempNodePtr->component, "S" ) == 0 && 
                         strcmp( tempNodePtr->operation, "end" ) == 0 ) )
               {
                  // load to linked list

	          *headPtr = addMetaNode( *headPtr, tempNodePtr );
               }
               else if( ( strcmp( &tempNodePtr->component, "A" ) == 0 && 
                         strcmp( tempNodePtr->operation, "start" ) == 0) ||
                   ( strcmp( &tempNodePtr->component, "A" ) == 0 && 
                         strcmp( tempNodePtr->operation, "end" ) == 0) )
               {
                  // load to linked list
	          *headPtr = addMetaNode( *headPtr, tempNodePtr );
               }
               else if( ( strcmp(&tempNodePtr->component, "P" ) == 0 && 
                         strcmp(tempNodePtr->operation, "run" ) == 0) )
               {
                  // load to linked list
	          *headPtr = addMetaNode( *headPtr, tempNodePtr );
               }
               else if( ( strcmp( &tempNodePtr->component, "M" ) == 0 && 
                         strcmp( tempNodePtr->operation, "access" )) ||
                   ( strcmp( &tempNodePtr->component, "M" ) == 0 && 
                         strcmp( tempNodePtr->operation, "allocate" )) ) 
               {
                  // load to linked list
	          *headPtr = addMetaNode( *headPtr, tempNodePtr );
               }
               else if( ( strcmp( &tempNodePtr->component, "I" ) == 0 && 
                         strcmp( tempNodePtr->operation, "hard drive" )) ||
                   ( strcmp( &tempNodePtr->component, "I" ) == 0 && 
                         strcmp( tempNodePtr->operation, "keyboard" )) )
               {
                  // load to linked list
	          *headPtr = addMetaNode( *headPtr, tempNodePtr );
               }
               else if( ( strcmp( &tempNodePtr->component, "O" ) == 0 && 
                         strcmp( tempNodePtr->operation, "hard drive" )) ||
                   ( strcmp( &tempNodePtr->component, "O" ) == 0 && 
                         strcmp( tempNodePtr->operation, "printer" )) ||
                   ( strcmp( &tempNodePtr->component, "O" ) == 0 && 
                         strcmp( tempNodePtr->operation, "monitor" )) )
               {
                  // load to linked list
	          *headPtr = addMetaNode( *headPtr, tempNodePtr );
               }
               else
               {
                 fclose( fileAccessPtr );
                 
                 free( tempNodePtr ); 

                 return INCORRECT_DATA;
               }
	       
            }
            else
            {
               fclose( fileAccessPtr );

               free( tempNodePtr );  

               return END_FILE_FOUND_MSG;
            }
         }

       }
       else
       {
          fclose( fileAccessPtr );

          free( tempNodePtr ); 

          return END_FILE_FOUND_MSG;
       }
       
      }
   }
   else
   {
      printf("yo look we didn't open the file\n"); //DEBUG CODE
      printf("Hey look we didn't open the file\n"); //DEBUG CODE
      return FILE_OPEN_ERR;
   }
   
   return UNKNOWN_ERR;
   }
/////////////////////////

//// Here are the timer functions

void * runTimer( void * milliSeconds )
   {
    struct timeval startTime, endTime;
    int startSec, startUSec, endSec, endUSec;
    int uSecDiff, mSecDiff, secDiff, timeDiff;
    int * milliNew = (int * )milliSeconds;
    int workingMilli = *milliNew;


    gettimeofday( &startTime, NULL );
 
    startSec = startTime.tv_sec;
    startUSec = startTime.tv_usec;

    timeDiff = 0;

    while( timeDiff < workingMilli )
       {
        gettimeofday( &endTime, NULL );

        endSec = endTime.tv_sec;
        endUSec = endTime.tv_usec;
        uSecDiff = endUSec - startUSec;

        if( uSecDiff < 0 )
           {
            uSecDiff = uSecDiff + 1000000;

            endSec = endSec - 1;
           }

        mSecDiff = uSecDiff / 1000;
        secDiff = ( endSec - startSec ) * 1000;
        timeDiff = secDiff + mSecDiff;
       }
   }

double accessTimer( int controlCode, char *timeStr )
   {
    static Boolean running = False;
    static int startSec = 0, endSec = 0, startUSec = 0, endUSec = 0;
    static int lapSec = 0, lapUSec = 0;
    struct timeval startData, lapData, endData;
    double fpTime = 0.0;

    switch( controlCode )
       {
        case ZERO_TIMER:
           gettimeofday( &startData, NULL );
           running = True;

           startSec = startData.tv_sec;
           startUSec = startData.tv_usec;

           fpTime = 0.000000000;
           lapSec = 0.000000000;
           lapUSec = 0.000000000;

           timeToString( lapSec, lapUSec, timeStr ); 
           break;
           
        case LAP_TIMER:
           if( running == True )
              {
               gettimeofday( &lapData, NULL );

               lapSec = lapData.tv_sec;
               lapUSec = lapData.tv_usec;

               fpTime = processTime( startSec, lapSec, 
                                                 startUSec, lapUSec, timeStr );
              }

           else
              {
               fpTime = 0.000000000;
              }
           break;

        case STOP_TIMER:
           if( running == True )
              {
               gettimeofday( &endData, NULL );
               running = False;

               endSec = endData.tv_sec;
               endUSec = endData.tv_usec;

               fpTime = processTime( startSec, endSec, 
                                                 startUSec, endUSec, timeStr );
              }

           // assume timer not running
           else
              {
               fpTime = 0.000000000;
              }
           break;
       }

    return fpTime;
   }

double processTime( double startSec, double endSec, 
                           double startUSec, double endUSec, char *timeStr )
   {
    double secDiff = endSec - startSec;
    double uSecDiff = endUSec - startUSec;
    double fpTime;

    fpTime = (double) secDiff + (double) uSecDiff / 1000000;

    if( uSecDiff < 0 )
       {
        uSecDiff = uSecDiff + 1000000;
        secDiff = secDiff - 1;
       }

    timeToString( secDiff, uSecDiff, timeStr );

    return fpTime;
   }


/* This is a bit of a drawn-out function, but it is written
   to force the time result to always be in the form x.xxxxxxx
   when printed as a string; this will not always be the case
   if the time is presented as a floating point number
*/
void timeToString( int secTime, int uSecTime, char *timeStr )
   {
    int low, high, index = 0;
    char temp;

    while( uSecTime > 0 )
       {
        timeStr[ index ] = (char) ( uSecTime % 10 + '0' );
        uSecTime /= 10;

        index++;
        
       }

    while( index < 6 )
       {
        timeStr[ index ] = '0';

        index++;
       }

    timeStr[ index ] = RADIX_POINT;

    index++;

    if( secTime < 10 ) // single digit in display
       {
        timeStr[ index ] = (char) ( secTime % 10 + '0' );

        index++;

        timeStr[ index ] = SPACE;

        index++;

        secTime = 0;
       }
/*
    if( secTime == 0 )
       {
        timeStr[ index ] = '0';
    
        index++;
       }
*/
    while( secTime > 0 )
       {
        timeStr[ index ] = (char) ( secTime % 10 + '0' );

        secTime /= 10;

        index++;
       }

    timeStr[ index ] = NULL_CHAR;

    low = 0; high = index - 1;

    while( low < high )
       {
        temp = timeStr[ low ];
        timeStr[ low ] = timeStr[ high ];
        timeStr[ high ] = temp;

        low++; high--;
       }
   }


#endif   // LINKED_LIST_C


