/*
string copy modified from site:
https://stackoverflow.com/questions/19641291/how-to-create-my-own-strcpy-function
*/

#include "simtimer.h"

#ifndef SIM02_FUNCTIONS_H
#define SIM02_FUNCTIONS_H

typedef struct process
{
  char processName;
  int processNumber;
  char processState;
} process;

void stringCopy(char *source, char* destination);

struct process createProcess(int processNum, struct process proc,
                             char *meta_data_matrix);

double startProcess(char processor_cycle_time, char io_cycle_time);

int startIOProcess(char *io_cycle_time, char location, char type,
                  int total_io_time,  char *timeArray, double endTime,
                  int procIteration);

void returnTimer();


#endif // ifndef SIM02_FUNCTIONS_H
