#include <stdio.h>
#include <stdlib.h>
#include "sim02_functions.h"
#include "simtimer.h"
#include "simtimer.c"

//#include "simtimer.c"
#ifndef SIM02_FUNCTIONS_C
#define SIM02_FUNCTIONS_C

//get rid of this later, use h file
//double accessTimer( int controlCode, char *timeStr );
//double startProcess(char processor_cycle_time, char io_cycle_time);


// double startProcess(char processor_cycle_time, char io_cycle_time)
// {
//   char resultTime[20];
//   //0 for STOP_TIMER
//   //accessTimer(0, resultTime);
//   //printf("%s", accessTimer(STOP_TIMER));
//   //printf("%s", resultTime);
//   return accessTimer(2, resultTime);
// }


struct process createProcess(int processNum, struct process proc,
                             char *meta_data_matrix)
{
  // char processName [10];
  // processName[0] = 'P';
  // processName[1] = 'r';
  // processName[2] = 'o';
  // processName[3] = 'c';
  // processName[4] = 'e';
  // processName[5] = 's';
  // processName[6] = 's';
  // processName[7] = processNum;

  //proc.processName = processName;

  proc.processNumber = processNum;
  return proc;
}

void createPCB()
{
  //int iterator = 0;
  //for (iterator;iterator<)
}

int startIOProcess()
{
  //use this to confirm the process is finished before moving on
  return 1;
}



#endif // ifndef SIM02_FUNCTIONS_C
