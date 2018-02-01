#ifndef MAIN_C
#define MAIN_C

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "functions.h"

int main(void)
{
  char config_buffer[10000]; //where new config data is stored
  FILE *config_file;
  FILE *meta_data_file;
  meta_data_file = fopen("testfile2.mdf","r");
  config_file = fopen("config1.cnf","r");

  char version[20];
  char file_path[100];
  char cpu_scheduling_code[10];
  char quantum_time[10];
  char available_memory[100];
  char processor_cycle_time[10];
  char io_cycle_time[10];
  char log_to[10];
  char log_file_path[100];
  int  error_code = 0;

  struct NodeType *headPtr = NULL;
  // data node created, must be released
  struct NodeType *dataPtr
                  = ( struct NodeType * )malloc( sizeof( struct NodeType ) );
  char meta_data_buffer[ STD_STR_LEN ];

  //checks if file exists
  if (!config_file)
  {
    printf("No config file found\nExiting program\n");
    return 0;
  }

  if (!meta_data_file)
  {
    printf("No meta data file found\nExiting program\n");
    return 0;
  }


    //starts the meta data scan
    getMetaData(meta_data_file);
    printf("Meta Data File Dump \n=============\n");
    while (feof(meta_data_file)==0) //until the end of file
      {
        //scans until '(' and stores in pointers component letter
        fscanf(meta_data_file, "%[^(]s", dataPtr->component_letter);
        fscanf(meta_data_file, "%1s", meta_data_buffer);//skips next char '('
        //scans until ')' and stores in op string
        fscanf(meta_data_file, "%[10[0-9a-zA-Z ]s", dataPtr->operation_string);
        fscanf(meta_data_file, "%1s", meta_data_buffer);//skips next char ')'
        //scans until ';' and stores in cycle time
        fscanf(meta_data_file, "%[^;]s", dataPtr->cycle_time);
        fscanf(meta_data_file, "%1s", meta_data_buffer);//skips next char ';'
        //dump data
        printf("The data item component letter is:%s\n", dataPtr->component_letter);
        printf("The data item operation string is: %s\n", dataPtr->operation_string);
        printf("The data item cycle time is      : %s\n", dataPtr->cycle_time);
        headPtr = addNode( headPtr, dataPtr );
        printf("\n");
      }
    printf("\n");
    headPtr = clearList( headPtr );
    fclose(meta_data_file);


  //starts the config file scan
  error_code = getConfig(config_file, config_buffer, version, file_path,
                  cpu_scheduling_code, quantum_time, available_memory,
                  processor_cycle_time, io_cycle_time, log_to, log_file_path);

  if(error_code == 1)
  {
    printf("Invalid version number\nExiting program\n");
    fclose(config_file);
    exit(0);
  }
  else if (error_code == 2)
  {
    printf("Invalid quantum time cycle\nExiting program\n");
    fclose(config_file);
    exit(0);
  }
  else if(error_code == 3)
  {
    printf("Invalid memory input\nExiting program\n");
    fclose(config_file);
    exit(0);
  }
  else if(error_code == 4)
  {
    printf("Invalid CPU cycle time\nExiting program\n");
    fclose(config_file);
    exit(0);
  }
  else if(error_code == 5)
  {
    printf("Invalid I/O cycle time\nExiting program\n");
    fclose(config_file);
    exit(0);
  }

  printf("Config File Dump \n================\n");
  printf("Version                  : %s \n", version);
  printf("File Path                : %s \n", file_path);
  printf("CPU Scheduling Code      : %s \n", cpu_scheduling_code);
  printf("Quantum Time (in cycles) : %s \n", quantum_time);
  printf("Memory Available (in KB) : %s \n", available_memory);
  printf("Processor Cycle Time     : %s \n", processor_cycle_time);
  printf("I/O Cycle Time           : %s \n", io_cycle_time);
  printf("Log to                   : %s \n", log_to);
  printf("Log File Path            : %s \n", log_file_path);

}

#endif   // MAIN_C
