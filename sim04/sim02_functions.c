#ifndef SIM02_FUNCTIONS_C
#define SIM02_FUNCTIONS_C

#include "sim02_functions.h"

//#include "simtimer.c"

int threadID = 0;

struct process addProc(int processNum)
{
  struct process proc;
  proc.processState = 'W'; //Waiting
  proc.processNumber = processNum;
  return proc;
}


void *threadEnd()
{
  return NULL;
}


void createThread()
{
  pthread_t threadID;
  pthread_create(&threadID, NULL, *threadEnd, NULL);
  pthread_join(threadID, NULL);
}


//TODO
void startIOProcess(char *io_cycle_time, char *log_to, char location, char type,
                  int total_io_time,  char *timeArray, double endTime,
                  int procIteration, FILE *log_file)
{
  char location_var[20];
  char type_var[10];
  if(location == 'h')
  {
    char location_var[20] = {'h','a','r','d',' ','d','r','i','v','e','\0'};
    //for some reason this is needed to suppress "unused" warning
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


  endTime = accessTimer(1,timeArray);
  if (log_to[0] != 'F')
  {
    printf("Time:  %f, Process %d %s %s ", endTime, procIteration,
                    location_var, type_var);
  }
  else
  {
    fprintf(log_file,"Time:  %f, Process %d %s %s ", endTime,
                    procIteration, location_var, type_var);
  }
  //addProc(procIteration);
}

#endif // ifndef SIM02_FUNCTIONS_C
