// Program Information ////////////////////////////////////////////////////////
/**
 * @file maintest.c
 *
 * @brief driver for sim projects
 *
 * @author Justin Kincaid
 *
 * @details demonstrates working configparse and pmdlist
 *
 * @version 0.1 01/27/2018
 *
 * @Note Requires configparse.h and pmdlist.h

 *
 *
 */
#include "configparse.h"
#include "pmdlist.h"

int testConfigParse(char *configFilePath){

  int resultCode;
  struct ConfigFile *tempConfigFile
                    = (struct ConfigFile *)malloc( sizeof( struct ConfigFile ) );

  //one function to rule them all
  resultCode = getConfigDataFromFile(tempConfigFile,configFilePath);

  const char *logFileDefinitionMain[] =
  {
    "Start Simulator Configuration File",
    "Version/Phase:",
    "File Path:",
    "CPU Scheduling Code:",
    "Quantum Time (cycles):",
    "Memory Available (KB):",
    "Processor Cycle Time (msec):",
    "I/O Cycle Time (msec):",
    "Log To:",
    "Log File Path:",
    "End Simulator Configuration File."
  };

  if(resultCode == NO_ERROR_MSG || resultCode == END_FILE_FOUND_MSG){
    int displayCount=0;

    printf("\n%s                    \n", logFileDefinitionMain[displayCount++]);
    printf("%-30s                    : %i\n", logFileDefinitionMain[displayCount++], tempConfigFile->version);
    printf("%-30s                    : %s\n", logFileDefinitionMain[displayCount++], tempConfigFile->filePath);
    printf("%-30s                    : %i\n", logFileDefinitionMain[displayCount++], tempConfigFile->cpuScheduleCode);
    printf("%-30s                    : %i\n", logFileDefinitionMain[displayCount++], tempConfigFile->quantumTime);
    printf("%-30s                    : %i\n", logFileDefinitionMain[displayCount++], tempConfigFile->memoryAvail);
    printf("%-30s                    : %i\n", logFileDefinitionMain[displayCount++], tempConfigFile->processorCycleTime_msec);
    printf("%-30s                    : %i\n", logFileDefinitionMain[displayCount++], tempConfigFile->ioCycleTime_msec);
    printf("%-30s                    : %s\n", logFileDefinitionMain[displayCount++], tempConfigFile->logTo);
    printf("%-30s                    : %s\n", logFileDefinitionMain[displayCount++], tempConfigFile->logFilePath);
    printf("%-30s                 \n", logFileDefinitionMain[displayCount++]);



  }
  else
  {
    printf("\nERROR MESSAGE RECIEVED CONFIG PARSE : %d --> %s\n", resultCode, configFilePath);
    free(tempConfigFile);
    return resultCode;
  }

  free(tempConfigFile);

  return NO_ERROR_MSG;


}

int testMetaDataParse(char *metaDataFilePath)
{
  struct ProgramMetaDataNode *workingPtr, *headPtr = NULL;

  int resultCode;

  //one function to rule them all
  resultCode = getDataFromFile(&headPtr,metaDataFilePath);

  //printf("\nERROR CODE FROM MDFP %d --> %s\n", resultCode, metaDataFilePath);
  if(!resultCode)
  {
    workingPtr = headPtr;

    while( workingPtr != NULL )
       {
        printf( "\nThe data item component letter is: %c\n"\
                  "The data item operation string is: %s\n"\
                  "The data item cycle time is      : %i\n",
                        workingPtr->commandLetter, workingPtr->operationString, workingPtr->cycleTime );

        workingPtr = workingPtr->next;
       }

  }
  else
  {
    printf("ERROR MESSAGE RECIEVED METADATAPARSE: %d --> %s\n", resultCode, metaDataFilePath);
    headPtr = clearList(headPtr);
    free(headPtr);
    return resultCode;
  }

  headPtr = clearList(headPtr);
  free(workingPtr);
  free(headPtr);
  return NO_ERROR_MSG;

}


int main( int argc, char **argv )
   {


     if(argv[1] == NULL || argv[2] == NULL)
     {

        char *badConfig1 = "bad_processorcycletime.cnf";
        char *badConfig2 = "bad_cpuschedulingcode.cnf";
        char *goodConfig1 = "config1.cnf";
        char *goodConfig2 = "config2.cnf";
        char *goodConfig3 = "config3.cnf";

        char *badMetaDataFile1 = "bad_bracket.mdf";
        char *badMetaDataFile2 = "bad_commandcode.mdf";
        char *goodMetaDataFile1 = "testfile1.mdf";
        char *goodMetaDataFile2 = "testfile2.mdf";
        char *goodMetaDataFile3 = "testfile3.mdf";


        printf("BEGINING BAD TEST 01 SIM01\n\n");

        testConfigParse(badConfig1);
        printf("\n");

        testMetaDataParse(badMetaDataFile1);
        printf("\n");

        printf("BEGINING BAD TEST 01 SIM01\n\n");

        testConfigParse(badConfig2);
        printf("\n");

        testMetaDataParse(badMetaDataFile2);
        printf("\n");

        printf("BEGINING GOOD TEST 01 SIM01\n\n");

        testConfigParse(goodConfig1);
        printf("\n");

        testMetaDataParse(goodMetaDataFile1);
        printf("\n");

        printf("BEGINING GOOD TEST 02 SIM01\n\n");

        testConfigParse(goodConfig2);
        printf("\n");

        testMetaDataParse(goodMetaDataFile2);
        printf("\n");

        printf("BEGINING GOOD TEST 03 SIM01\n\n");

        testConfigParse(goodConfig3);
        printf("\n");

        testMetaDataParse(goodMetaDataFile3);
        printf("\n");

      }
      else if (argv[1] != NULL && argv[2] != NULL)
      {

        printf("BEGINING CONFIG TEST SIM01: %s\n\n", argv[1]);
        testConfigParse(argv[1]);

        printf("BEGINING METADATA TEST SIM01: %s\n\n", argv[2]);
        testMetaDataParse(argv[2]);

      }
      else
      {
        printf("\nERROR INCORRECT PARAMETERS\n");
      }




    return 0;
  }
