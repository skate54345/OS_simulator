// Program Information ////////////////////////////////////////////////////////
/**
 * @file mainfile.c
 *
 * @brief Driver file for the first simulation project
 *
 * @Secret ID Numbeer: 766181
 *
 * @details Drives the program.
 *
 * @version 1.00 (28 September 2018)
 *
 * @Note Structure for this header referenced from Michael Leveringtons SimTimer.h file
 *       String Functions referenced from C standard library
 *       Linkedlist files from the example files provided from BBLearn
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef MAIN_FILE_C
#define MAIN_FILE_C

// Header functions
//#include "util_functions.h"
#include "runsimulation.h"
#include <strings.h>

int main( int argc, char **argv )
{

    struct ConfigNodeType *workingConfigPtr, *tempConfigPtr, *headConfigPtr = ( struct ConfigNodeType * )malloc( sizeof( struct ConfigNodeType ) );
    struct MetaNodeType *workingMetaPtr, *headMetaPtr = ( struct MetaNodeType * )malloc( sizeof( struct MetaNodeType ) );

    int resultCode;
    char configFileName[ STD_STR_LEN ];
    char metaFileName[ STD_STR_LEN ];

   //Upload Configuration File
   // check number of arguments found on command line
    if( argc > 1 )
       {
        // copy file name in from command line
        strcpy( configFileName, argv[ 1 ] );

        // upload data from file given in command line
	resultCode = getConfigDataFromFile( &headConfigPtr, configFileName  );

        // check for successful data upload
        if( resultCode == END_FILE_FOUND_MSG )
         {
            resultCode = 0;
            workingConfigPtr = headConfigPtr;
            //Upload meta file
            tempConfigPtr = findConfigNodeByName( workingConfigPtr, "File Path" );

            strcpy( metaFileName, tempConfigPtr->selectionName );

            resultCode = getMetaDataFromFile( &headMetaPtr, metaFileName );

            if( resultCode == END_FILE_FOUND_MSG )
            {

               workingMetaPtr = headMetaPtr;

               //call run function SIM02 CALL
               runSimulation( workingMetaPtr, workingConfigPtr );

               clearConfigList( headConfigPtr );
               clearMetaList( headMetaPtr );
            }
            else if( resultCode == INCORRECT_NAME )
            {
               printf( "Meta-Data file has an incorrect component letter, ");
               printf( "please check meta-data file.\n");
            }
            else if(resultCode == INCORRECT_DATA )
            {
               printf( "Meta data is not consistent with specifications, ");
               printf("please check Meta-Data file.\n");
            }
         }
         else if( resultCode == INCORRECT_NAME )
         {
            printf( "Config Naming is incorrect, " );
            printf( "please check config file.\n" );
         }
         else if(resultCode == INCORRECT_DATA )
         {
            printf( "Config data is not consistent with specifications, ");
            printf("please check config file.\n");
         }

       }

    else
       {
        printf( "File name not found, " );
        printf( "must be placed as a command line argument\n" );
       }

   clearConfigList( tempConfigPtr );

   return 0;
}





















#endif //MAIN_FILE_C
