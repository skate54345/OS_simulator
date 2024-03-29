#ifndef MAIN_C
#define MAIN_C

#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linkedlist.h"
#include "simtimer.h"
#include "functions.h"
#include "sim02_functions.h"
#include "sim03_functions.h"
#include "sim04_functions.h"


int main(int argc, char **argv)
{
  char config_buffer[10000]; //where new config data is stored
  char string_buffer[100]; //where print output is stored
  FILE *config_file;
  FILE *meta_data_file;
  FILE *log_file;
  char *meta_data_matrix[100][100][100]; //main matrix for meta data
  char version[20];
  char file_path[100];
  char cpu_scheduling_code[10];
  char quantum_time[10];
  char available_memory[100];
  char processor_cycle_time[10];
  char io_cycle_time[10];
  char log_to[10];
  char log_file_path[100];
  int error_code = 0;
  int ending_row;
  char timeArray[20];
  double startTime;
  double endTime;
  int PCBIteration = 0;
//  struct proc process_array[100]; //array of proc (from A to A)
  struct NodeType *headPtr = NULL;
  // data node created, must be released
  struct NodeType *dataPtr
                  = ( struct NodeType * )malloc( sizeof( struct NodeType ) );
  char meta_data_buffer[STD_STR_LEN];
  //check if they provided an argument
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

/* sim01 print statements ////////////////////////////////////////////////
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
*/////////////////////////////////////////////////////////////////////////

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
/* sim01 print statement /////////////////////////////////////////////////
      printf("Meta Data File Dump \n===================\n");
*/////////////////////////////////////////////////////////////////////////
      while (feof(meta_data_file)==0) //until the end of file
        {
          //scan until '(' and stores in pointers component letter
          fscanf(meta_data_file, "%[^(]s", dataPtr->component_letter);
          //skips next char '('
          fscanf(meta_data_file, "%1s", meta_data_buffer);
          //scans until ')' and stores in op string
          fscanf(meta_data_file, "%[10[0-9a-zA-Z ]s", dataPtr->operation_string);
          //skips next char ')'
          fscanf(meta_data_file, "%1s", meta_data_buffer);
          //scans until ';' and stores in cycle time
          fscanf(meta_data_file, "%[^;]s", dataPtr->cycle_time);
          //skips next char ';'
          fscanf(meta_data_file, "%1s", meta_data_buffer);
          //dump data

          //fill matrix with old linked list for easier use in sim02
          meta_data_matrix[PCBIteration][row][col] = dataPtr->component_letter;
          meta_data_matrix[PCBIteration][row][col+1] = dataPtr->operation_string;
          meta_data_matrix[PCBIteration][row][col+2] = dataPtr->cycle_time;
          meta_data_matrix[PCBIteration][row][col+3] = "N"; //set to new state
          ending_row = row;

/* sim01 print statements ////////////////////////////////////////////////
          //dump
          printf("The data item component lett
          er is: %s\n",
                                           dataPtr->component_letter);
          printf("The data item operation string is: %s\n",
                                           dataPtr->operation_string);
          printf("The data item cycle time is      : %s\n",
                                           dataPtr->cycle_time);
*/ ///////////////////////////////////////////////////////////////////////

          ++row;
          col=0;
          headPtr = addNode( headPtr, dataPtr );
          dataPtr = headPtr;
          //fixes issue where var shows on next line by checking per character
          fgetc(meta_data_file);
        }

/* SIM04 start (after refactoring)*////////////////////////////////////////////////////////////////


//TODO get correct process
//TODO print stuff at the very end, use sprintf to assign a massive string array
//TODO

      //check for FCFS for old implementation
      if(checkFCFSN(cpu_scheduling_code)==1)
      {
        FCFSN(log_file, ending_row, timeArray, startTime, endTime, log_to, cpu_scheduling_code,
                        processor_cycle_time, available_memory, io_cycle_time,
                        quantum_time, log_file_path, meta_data_matrix);
      }
      else
      {


//start of loop

      //int total_time = stringToInt(processor_cycle_time)*(*meta_data_matrix[PCBIteration][row][2]);
      //int total_io_time = stringToInt(io_cycle_time)*(*meta_data_matrix[PCBIteration][row][2]);
      log_file = fopen(log_file_path,"w+");
      startTime = accessTimer(0,timeArray); //start clock
      //if set to 'File'
      if(log_to[0] != 'F')
      {
        printf("\nTime:  %f, System Start\n", startTime);
      }
      //if set to 'Monitor' or 'Both'
      else
      {
        printf("Writing to file...\n");
        fprintf(log_file, "Time:  %f, System Start\n", startTime);
      }

      endTime = accessTimer(1,timeArray); //stop
      if(log_to[0] != 'F')
      {
        printf("Time:  %f, OS: Begin PCB Creation\n", endTime);
      }
      else
      {
        fprintf(log_file, "Time:  %f, OS: Begin PCB Creation\n", endTime);
      }


///////FCFSP
      //if(checkFCFSN(cpu_scheduling_code==1))
      //{
        //TODO CHECK FOR SCHEDULING CODE WITHIN EACH LETTER

        int running = 0;
        int new_quantum = stringToInt(quantum_time);
        for(row=0; row<ending_row; row++)
        {

          int total_time = 0; //stringToInt(processor_cycle_time)*(*meta_data_matrix[PCBIteration][row][2]);
          int total_io_time = 0; //stringToInt(io_cycle_time)*(*meta_data_matrix[PCBIteration][row][2]);
          char location = *meta_data_matrix[PCBIteration][row][1];
          char type = *meta_data_matrix[PCBIteration][row][0];

            //check for IO process
            if((*meta_data_matrix[PCBIteration][row][0] == 'I' && row != 0) ||
                                (*meta_data_matrix[PCBIteration][row][0] == 'O'
                                && row != 0))
            {
              //TODO load timer with the data and call it

              //set to blocked
              meta_data_matrix[PCBIteration][row][3] = "B";

              startIOProcess(io_cycle_time, log_to, location, type, total_io_time,
                                timeArray, endTime, PCBIteration, log_file);
              char start[20] = {'s','t','a','r','t','\0'};
              start[20] = start[20];

              printf("start\0\n");

              runTimer(total_io_time);
              createThread();
              startIOProcess(io_cycle_time, log_to, location, type, total_io_time,
                                timeArray, endTime, PCBIteration, log_file);

              endTime = accessTimer(1,timeArray);

            }
            else if(*meta_data_matrix[PCBIteration][row][0] == 'M' && row != 0)
            {
              //TODO running MMU

              //TODO potential seg fault of process
            }
            else if(*meta_data_matrix[PCBIteration][row][0] == 'A' && row != 0)
            {
              //quantum_time--;
              //TODO loop up to num cycles or quantum (one cycle at a time)

              //TODO timer

              //TODO check for interrupt

              //TODO interrupt, then move context back process manager

              //TODO call output operation (interrupt)
            }
            startTime = endTime;
            PCBIteration++;
            PCBIteration = 0;

            running = 0;

        }

      fclose(meta_data_file);
      fclose(log_file);
     }
   }
}

#endif // MAIN_C
