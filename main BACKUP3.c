#ifndef MAIN_C
#define MAIN_C

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "functions.h"

int main(void)
{

  char config_buffer[1000]; //where new config data is stored
  //char meta_data_buffer[1000]; //where new config data is stored
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
  int  iterator=0;

  struct NodeType *workingPtr, *headPtr = NULL;
  // data node created, must be released
  struct NodeType *dataPtr
                  = ( struct NodeType * )malloc( sizeof( struct NodeType ) );
  int resultCode;
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

  //runTimer(100);

  //starts the config file scan
  while (feof(config_file)==0) //until the end of file
  {
    fscanf(config_file, "%s", config_buffer); //stores text in config_buffer array

    //version section
    if (*config_buffer == 'V') //finds the first (and only) V to skip initial line
    {
      skipString(config_file,version,1);
      //file path section
      //file path is listed next so cycle through the strings: 'testfile2.mdf', 'File', and 'Path:'
      skipString(config_file,file_path,3);//this stores the file path data in "file_path"

      //CPU scheduling code section
      //skip 'Scheduling' 'Code: '
      skipString(config_file,cpu_scheduling_code,4);

      //quantum time section
      //skip 'cycles' and store in variable
      skipString(config_file,quantum_time,4);

      //memory section section
      skipString(config_file,available_memory,4);

      //cpu cycle time section
      skipString(config_file,processor_cycle_time,5);

      //IO cycle time section
      skipString(config_file,io_cycle_time,5);

      //log to section
      skipString(config_file,log_to,3);

      //log file path section
      skipString(config_file,log_file_path,4);
    }
  }

  //TODO make these into functions in other file

  //version number section
  //trim version number
  for (iterator=1; iterator<sizeof(version);iterator++)
  {
    version[iterator] = '\0';
  }

  //convert to int and check version number
  if (rangeCheck(atoi (version), 0, 10) != 1)
  {
    printf("Invalid version number\nExiting program\n");
    fclose(config_file);
    fclose(meta_data_file);
    exit(0);
  }

  //quantum time check
  if (rangeCheck(atoi (quantum_time), 0, 100) != 1)
  {
    printf("Invalid quantum time cycle\nExiting program\n");
    fclose(config_file);
    fclose(meta_data_file);
    exit(0);
  }

  //memory check
  if (rangeCheck(atoi (available_memory), 0, 1048576) != 1)
  {
    printf("Invalid memory input\nExiting program\n");
    fclose(config_file);
    fclose(meta_data_file);
    exit(0);
  }

  if (rangeCheck(atoi (processor_cycle_time), 1, 1000) != 1)
  {
    printf("Invalid CPU cycle time\nExiting program\n");
    fclose(config_file);
    fclose(meta_data_file);
    exit(0);
  }

  if (rangeCheck(atoi (io_cycle_time), 1, 10000) != 1)
  {
    printf("Invalid I/O cycle time\nExiting program\n");
    fclose(config_file);
    fclose(meta_data_file);
    exit(0);
  }


  if(cpu_scheduling_code[0] == 'N' && cpu_scheduling_code[1] == 'O') //if NONE is encountered
  {
    //clear array
    for (iterator=0; iterator<sizeof(cpu_scheduling_code);iterator++)
    {
      cpu_scheduling_code[iterator] = '\0';
    }
    //write new code
    cpu_scheduling_code[0] = 'F';
    cpu_scheduling_code[1] = 'C';
    cpu_scheduling_code[2] = 'N';
    cpu_scheduling_code[3] = 'F';
    cpu_scheduling_code[4] = '-';
    cpu_scheduling_code[5] = 'N';
    //"FCNF-N";
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
  printf("\nTime for configuration upload: X microseconds\n");



  //starts the meta data scan

  //skip first line
  skipString(meta_data_file, meta_data_buffer, 4);
  printf("Config File Dump \n================\n");
  while (feof(meta_data_file)==0) //until the end of file
  {
    //scans until '(' and stores in pointers component letter
    fscanf(meta_data_file, "%[^(]s", dataPtr->component_letter);
    //printf("%s",dataPtr->component_letter);
    fscanf(meta_data_file, "%1s", meta_data_buffer);//skips next char '('
    //scans until ')' and stores in op string
    fscanf(meta_data_file, "%[10[0-9a-zA-Z ]s", dataPtr->operation_string);
    //printf("%s",dataPtr->operation_string);
    fscanf(meta_data_file, "%1s", meta_data_buffer);//skips next char ')'
    //scans until ';' and stores in cycle time
    fscanf(meta_data_file, "%[^;]s", dataPtr->cycle_time);
    fscanf(meta_data_file, "%1s", meta_data_buffer);//skips next char ';'
    //printf("%s",dataPtr->cycle_time);
    //strcpy(dataPtr->name, meta_data_buffer);
    //dump data
    printf("The data item component letter is:%s\n", dataPtr->component_letter);
    printf("The data item operation string is: %s\n", dataPtr->operation_string);
    printf("The data item cycle time is      : %s\n", dataPtr->cycle_time);
    headPtr = addNode( headPtr, dataPtr );
    printf("\n");
  }
  printf("\n");
  headPtr = clearList( headPtr );
  fclose(config_file);
  fclose(meta_data_file);
  return 0;
}

#endif   // MAIN_C
