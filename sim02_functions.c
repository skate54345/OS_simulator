#include <stdio.h>
#include <stdlib.h>
#include "sim02_functions.h"
#include "simtimer.h"
#define word_size 50
#include "pthread.h"

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


void addSubProc(int processNum)
{
  struct process proc;
  proc.processState = 'R'; //running
  proc.processNumber = processNum;
  proc.subProcID = createSubProcID(processNum);
  //int *subIterationPtr;
  //addToPCB(proc);
}

void addToPCB(struct process proc)
{
  // int *subIterationPtr,
  // struct process subProcArray[200];
  // //set pointer array index of pointer to proc
  // subProcArray[subIterationPtr] = proc;
  // subIterationPtr++;
  // printf("s\n", subProcArray[0].processState);
  //for (iterator;iterator<)
  //return procArray;
}


int changeThreadState(state, new_state)
{
  state = new_state;
  return state;
}


void *threadEnd()
{
  return NULL;
}

void threadStart()
{
  //printf("start\n");
}


void createThread()
{
  //TODO WAIT FOR DESIRED TIME
  pthread_t threadID;
  pthread_create(&threadID, NULL, *threadEnd, NULL);
  pthread_join(threadID, NULL);
}


int createSubProcID(int procIteration)
{
  int newID = procIteration + rand() %10000;
  return newID;
}


//TODO
void startIOProcess(char *io_cycle_time, char *log_to, char location, char type,
                  int total_io_time,  char *timeArray, double endTime,
                  int procIteration)
{
  char location_var[20];
  char type_var[10];
  if(location == 'h')
  {
    //stringCopy(hdd, location_var);
    char location_var[20] = {'h','a','r','d',' ','d','r','i','v','e','\0'};
    //for some reason needs this to suppress "unused" warning even though it is
    location_var[20] = location_var[20];
  }
  else if(location == 'p')
  {
    char location_var[20] = {'p','r','i','n','t','e','r','\0'};
    location_var[20] = location_var[20];
  }

  else if(location == 'k')
  {
    char location_var[20] = {'k','e','y','b','o','a','r','d','\0'};
    location_var[20] = location_var[20];
  }

  else if(location == 'm')
  {
    char location_var[20] = {'m','o','n','i','t','o','r','\0'};
    location_var[20] = location_var[20];
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


  endTime = accessTimer(1,timeArray);
  if (log_to[0] != 'F')
  {
    printf("Time:  %f, Process %d %s %s ", endTime, procIteration,
                    location_var, type_var);
  }

  addSubProc(procIteration);
  //createThread();
}



#endif // ifndef SIM02_FUNCTIONS_C
