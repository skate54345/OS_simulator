// Program Information ////////////////////////////////////////////////////////
/**
 * @file configparse.h
 *
 * @brief parses sim config creates nice struct for config file
 *
 * @author Justin Kincaid
 *
 * @details
 *
 * @version 0.1 01/27/2018
 *
 *
 *
 */
// header files
#include <stdio.h>  // I/O
#include <stdlib.h>  // malloc
#include <string.h>  // string management






// Message codes for file access

enum SCHEDULING_CODES { NONE, FCFSN, SJFN, SRTFP, FCFSP, RRP};
// char CPU_SCHEDULING_CODES[6][10] = {"NONE", "FCFS-N", "SJF-N", "SRTF-P", "FCFS-P", "RR-P"};

// struct declaration
struct ConfigFile
   {
     int version;
     char filePath[2048];
     int cpuScheduleCode;
     int quantumTime;
     int memoryAvail;
     int processorCycleTime_msec;
     int ioCycleTime_msec;
     char logTo[2048];
     char logFilePath[2048];


   };


   // function prototypes
int parseAndPackConfig(struct ConfigFile *cFileStruct, char *fileLineStr,char *configValueStr, int configFileIndex);

int getConfigDataFromFile( struct ConfigFile *cFileStruct, char *fileName );
