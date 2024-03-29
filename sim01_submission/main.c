#ifndef MAIN_C
#define MAIN_C

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "functions.h"

int main(int argc, char **argv)
{
  char config_buffer[10000]; //where new config data is stored
  FILE *config_file;
  FILE *meta_data_file;
  char *meta_data_matrix[1000][1000];

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
  struct NodeType *workingPtr = NULL;
  // data node created, must be released
  struct NodeType *dataPtr
                  = ( struct NodeType * )malloc( sizeof( struct NodeType ) );
  char meta_data_buffer[ STD_STR_LEN ];

  if (argc >= 2)
  {
      config_file = fopen(argv[1],"r");
  }
  else
  {
    printf("Invalid argument(s)\nExiting program\n");
    return 0;
  }

  //checks if file exists
  if (!config_file)
  {
    printf("No config file found\nExiting program\n");
    return 0;
  }

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

  printf("\nConfig File Dump \n================\n");
  printf("Version                  : %s \n", version);
  printf("File Path                : %s \n", file_path);
  printf("CPU Scheduling Code      : %s \n", cpu_scheduling_code);
  printf("Quantum Time (in cycles) : %s \n", quantum_time);
  printf("Memory Available (in KB) : %s \n", available_memory);
  printf("Processor Cycle Time     : %s \n", processor_cycle_time);
  printf("I/O Cycle Time           : %s \n", io_cycle_time);
  printf("Log to                   : %s \n", log_to);
  printf("Log File Path            : %s \n\n", log_file_path);


    //starts the meta data scan
    meta_data_file = fopen(file_path,"r");
    int row = 0;
    int col = 0;
    if (!meta_data_file)
    {
      printf("'%s' not found\nExiting program\n", file_path);
      return 0;
    }
    else
    {
      getMetaData(meta_data_file);
      printf("Meta Data File Dump \n=============\n");
      while (feof(meta_data_file)==0) //until the end of file
        {
          //scan until '(' and stores in pointers component letter
          fscanf(meta_data_file, "%[^(]s", dataPtr->component_letter);
          //skips next char '('
          fscanf(meta_data_file, "%1s", meta_data_buffer);
          //scans until ')' and stores in op string
          fscanf(meta_data_file, "%[10[0-9a-zA-Z ]s",
                                           dataPtr->operation_string);
          //skips next char ')'
          fscanf(meta_data_file, "%1s", meta_data_buffer);
          //scans until ';' and stores in cycle time
          fscanf(meta_data_file, "%[^;]s", dataPtr->cycle_time);
          //skips next char ';'
          fscanf(meta_data_file, "%1s", meta_data_buffer);
          //dump data

          //separate matrix for convenience
          meta_data_matrix[row][col] = dataPtr->component_letter;
          meta_data_matrix[row][col+1] = dataPtr->operation_string;
          meta_data_matrix[row][col+2] = dataPtr->cycle_time;

          ++row;
          col=0;

          printf("The data item component letter is: %s\n",
                                           dataPtr->component_letter);
          printf("The data item operation string is: %s\n",
                                           dataPtr->operation_string);
          printf("The data item cycle time is      : %s\n",
                                           dataPtr->cycle_time);
          headPtr = addNode( headPtr, dataPtr );
          dataPtr = headPtr;
          printf("\n");
          //fixes issue where var shows on next line by checking per character
          fgetc(meta_data_file);

          // printf("meta data: %s \n",meta_data_matrix[row][col]);
          // printf("meta data: %s \n",meta_data_matrix[row][col+1]);
          // printf("meta data: %s \n",meta_data_matrix[row][col+2]);
        }
    //  headPtr = clearList( headPtr );
      //
      printf("%s\n",meta_data_matrix[0][1]);

      fclose(meta_data_file);
    }
}


#endif   // MAIN_C
