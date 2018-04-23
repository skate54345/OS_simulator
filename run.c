#ifndef RUN_C
#define RUN_C

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linkedlist.h"
#include "functions.h"
#include "simtimer.h"
#include "sim02_functions.h"
#include "run.h"


void run(int argc, char **argv)
{
  FILE *config_file;
  FILE *meta_data_file;
  FILE *log_file;

  char *meta_data_matrix[1000][1000];
  char config_buffer[10000]; //where new config data is stored
  char file_out_array[10000];
  char version[20];
  char file_path[100];
  char cpu_scheduling_code[10];
  char quantum_time[10];
  char available_memory[100];
  char processor_cycle_time[10];
  char io_cycle_time[10];
  char log_to[10];
  char log_file_path[100];
  int ending_row;
  int error_code = 0;

  char timeArray[20];
  double startTime;
  double endTime;
  int procIteration = 0;
  int total_time;
  int total_io_time;
  //struct process firstProc;

  struct NodeType *headPtr = NULL;
  // data node created, must be released
  struct NodeType *dataPtr
                  = (struct NodeType *)malloc(sizeof(struct NodeType));
  char meta_data_buffer[STD_STR_LEN];



    if (argc >= 2)
    {
      config_file = fopen(argv[1],"r");
    }
    else
    {
      printf("Invalid argument(s)\nExiting program\n");
      exit(0);
    }

    //checks if file exists
    if (!config_file)
    {
      printf("No config file found\nExiting program\n");
      exit(0);
    }

    //starts the config file scan
    config_file = fopen(argv[1],"r");


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
          fscanf(meta_data_file, "%[10[0-9a-zA-Z ]s",
                                           dataPtr->operation_string);
          //skips next char ')'
          fscanf(meta_data_file, "%1s", meta_data_buffer);
          //scans until ';' and stores in cycle time
          fscanf(meta_data_file, "%[^;]s", dataPtr->cycle_time);
          //skips next char ';'
          fscanf(meta_data_file, "%1s", meta_data_buffer);
          //dump data

          //fill separate matrix for convenience
          meta_data_matrix[row][col] = dataPtr->component_letter;
          meta_data_matrix[row][col+1] = dataPtr->operation_string;
          meta_data_matrix[row][col+2] = dataPtr->cycle_time;
          //printf(dataPtr->cycle_time[0];
          ending_row = row;

/* sim01 print statements ////////////////////////////////////////////////
          //dump
          printf("The data item component letter is: %s\n",
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


/*SIM02 START*/

      log_file = fopen(log_file_path,"w+");
      //get ZERO_TIMER
      startTime = accessTimer(0,timeArray); //start
      //if set to 'File'
      if(log_to[0] != 'F')
      {
        printf("Time:  %f, System Start\n", startTime);
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

      //FCFS-N
      for(row = 0; row<ending_row; row++)
      {
        //loop between 'A' start and 'A' end
        if(*meta_data_matrix[row][0] == 'A' && *meta_data_matrix[row][0] != 'M'
                          && *meta_data_matrix[row][1] == 's')
        {
          endTime = accessTimer(1,timeArray);
          if(log_to[0] != 'F')
          {
            printf("Time:  %f, OS: FCFS-N Strategy selects Process %d "\
                            "with time: %s mSec\n", endTime, procIteration,
                            processor_cycle_time);
          }
          else
          {
            //write to file
            fprintf(log_file, "Time:  %f, OS: FCFS-N Strategy selects "\
                            "Process %d with time: %s mSec\n", endTime,
                            procIteration, processor_cycle_time);
          }

          endTime = accessTimer(1,timeArray);
          if(log_to[0] != 'F')
          {
            printf("Time:  %f, OS: Process %d Set in Running State\n", endTime,
                            procIteration);
          }
          else
          {
            fprintf(log_file,"Time:  %f, OS: Process %d Set in "\
                            "Running State\n", endTime, procIteration);
          }
        }

        else if(*meta_data_matrix[row][0] != 'A' && row != 0)
        {
          //set time to required values
          total_time = stringToInt(processor_cycle_time)*(*meta_data_matrix[row][2]);
          total_io_time = stringToInt(io_cycle_time)*(*meta_data_matrix[row][2]);
          char location = *meta_data_matrix[row][1];
          char type = *meta_data_matrix[row][0];
          if (*meta_data_matrix[row][0] != 'I'
                            && *meta_data_matrix[row][0] != 'O')
          {
            if(*meta_data_matrix[row][0] == 'M' && row != 0) //memory
            {
              //blank for this project
              //if equal to 'Memory'
              if(*log_to == 'M' || *log_to == 'B')
              {
                if(log_to[0] != 'F')
                {
                  printf("Time:  %f, Process %d Memory management allocate action"\
                              " start\n", endTime, procIteration);
                  printf("Time:  %f, Process %d Memory management allocate action"\
                              " end\n", endTime, procIteration);
                }
                else
                {
                  fprintf(log_file, "Time:  %f, Process %d "\
                              "Memory management allocate action start\n",
                              endTime, procIteration);
                  fprintf(log_file, "Time:  %f, Process %d Memory "\
                              "management allocate action end\n",
                              endTime, procIteration);
                }
              }
            }
            else
            {
              runTimer(total_time);
              endTime = accessTimer(1,timeArray);
              if(log_to[0] != 'F')
              {
                printf("Time:  %f, Process %d run operation start\n", endTime,
                               procIteration);
                printf("Time:  %f, Process %d run operation end\n", endTime,
                               procIteration);
              }
              else
              {
                fprintf(log_file, "Time:  %f, Process %d run operation "\
                               "start\n", endTime, procIteration);
                fprintf(log_file, "Time:  %f, Process %d run operation "\
                               "end\n", endTime, procIteration);
              }
            }
          }
          else //io process
          {
            startIOProcess(io_cycle_time, log_to, location, type, total_io_time,
                              timeArray, endTime, procIteration, log_file);
            char start[20] = {'s','t','a','r','t','\0'};
            start[20] = start[20];
            if(log_to[0] != 'F')
            {
              printf("start\n");
            }
            else
            {
              fprintf(log_file,"start\n");
            }
            runTimer(total_io_time);
            createThread();
            startIOProcess(io_cycle_time, log_to, location, type, total_io_time,
                              timeArray, endTime, procIteration, log_file);
            if(log_to[0] != 'F')
            {
              printf("end\n");
            }
            else
            {
              fprintf(log_file,"end\n");
            }
          }
        }

        //exit
        else if(*meta_data_matrix[row][0] == 'A' &&
                          *meta_data_matrix[row][1] == 'e')
        {
          endTime = accessTimer(1, timeArray);
          if(log_to[0] != 'F')
          {
            printf("Time:  %f, OS: Process %d Set in Exit State\n", endTime,
                            procIteration);
          }
          else
          {
            fprintf(log_file, "Time:  %f, OS: Process %d Set in Exit "\
                            "State\n", endTime, procIteration);
          }
          procIteration++;
        }
      }
      endTime = accessTimer(1,timeArray);
      if(log_to[0] != 'F')
      {
        printf("Time:  %f, System Stop\n", endTime);
      }
      else
      {
        fprintf(log_file, "Time:  %f, System Stop\n", endTime);
      }
      procIteration = 0; //reset iterator
      printf("%s", file_out_array);

      fclose(meta_data_file);
      fclose(log_file);
    }
}



int getConfig(FILE *config_file, char config_buffer[], char version[],
                    char file_path[], char cpu_scheduling_code[],
                    char quantum_time[], char available_memory[],
                    char processor_cycle_time[], char io_cycle_time[],
                    char log_to[], char log_file_path[])
{
  int iterator = 0;
  int error_code = 0;
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
  //version number section
  //trim version number
  trim(version, 1, 20);

  //convert to int and check version number
  if (rangeCheck(stringToInt (version), 0, 10) != 1)
  {
    error_code = 1;
  }

  //quantum time check
  if (rangeCheck(stringToInt (quantum_time), 0, 100) != 1)
  {
    error_code = 2;
  }

  //memory check
  if (rangeCheck(stringToInt (available_memory), 0, 1048576) != 1)
  {
    error_code = 3;
  }

  if (rangeCheck(stringToInt (processor_cycle_time), 1, 1000) != 1)
  {
    error_code = 4;
  }

  if (rangeCheck(stringToInt (io_cycle_time), 1, 10000) != 1)
  {
    error_code = 5;
  }
  if(cpu_scheduling_code[0] == 'N' && cpu_scheduling_code[1] == 'O') //if NONE is encountered
  {
    //clear array
    for (iterator=0; iterator<10;iterator++)
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
  return error_code;
}

#endif // RUN_C
