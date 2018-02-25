#include <stdio.h>
#include <stdlib.h>
#include "sim02_functions.h"
#include "simtimer.h"
#define word_size 50
#include "simtimer.c"

//#include "simtimer.c"
#ifndef SIM02_FUNCTIONS_C
#define SIM02_FUNCTIONS_C

//get rid of this later, use h file
//double accessTimer( int controlCode, char *timeStr );
//double startProcess(char processor_cycle_time, char io_cycle_time);

int threadID = 0;

void stringCopy(char* source, char *destination)
{

  char temp[word_size] = {'\0'};
  int index = 0;

  while (destination[index] != '\0')
  {
      source[index] = destination[index];
      index++;
  }
  //nullify rest of chars
  for (index = 0; index < word_size; index++)
  {
      source[index] = '\0';
  }
}

void addProcess(int processNum, char processState,
                             char *meta_data_matrix)
{
  //struct process proc;

  //proc.processState = "Running";
  //proc.processNumber = processNum;
  //addToPCB(proc);
}

void addToPCB(int processNum, char procArray, struct process proc)
{
  //char procArray [200];
  //int iterator = 0;
  //for (iterator;iterator<)
  //return procArray;
}


void createThread()
{
  //pthread_create(threadID ,NULL, *startIOProcess);
}


//TODO
int startIOProcess(char *io_cycle_time, char location, char type,
                  int total_io_time,  char *timeArray, double endTime,
                  int procIteration)
{
  char location_var[20];
  char type_var[10];
  char start_or_end[10] = {'s','t','a','r','t','\0'};
  //char hdd[100] = "hard drive";
  char return_string[100];
  if(location == 'h')
  {
    //stringCopy(hdd, location_var);
    char location_var[20] = {'h','a','r','d',' ','d','r','i','v','e','\0'};

  }
  else if(location == 'p')
  {
    char location_var[20] = {'p','r','i','n','t','e','r','\0'};
  }

  else if(location == 'k')
  {
    char location_var[20] = {'k','e','y','b','o','a','r','d','\0'};
  }


  if (type == 'I')
  {
    type_var[0] = 'i';
    type_var[1] = 'n';
    type_var[2] = 'p';
    type_var[3] = 'u';
    type_var[4] = 't';
    type_var[5] = '\0';
  }

  else if (type == 'O')
  {
    type_var[0] = 'o';
    type_var[1] = 'u';
    type_var[2] = 't';
    type_var[3] = 'p';
    type_var[4] = 'u';
    type_var[5] = 't';
    type_var[6] = '\0';
  }


//TODO run timer and start thread
  //printf("%d\n", (stringToInt(io_cycle_time))*(total_io_time));
  //runTimer((stringToInt(io_cycle_time))*(total_io_time));
  endTime = accessTimer(1,timeArray);
  printf("Time:  %f, Process %d %s %s %s\n", endTime, procIteration,
                  location_var, type_var, start_or_end);

  createThread();

  //use this to confirm the process is finished before moving on
  return 1;
}



#endif // ifndef SIM02_FUNCTIONS_C
