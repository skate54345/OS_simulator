/*
string copy modified from site:
https://stackoverflow.com/questions/19641291/how-to-create-my-own-strcpy-function
*/

#include "simtimer.h"
#include <stdio.h>

#ifndef SIM02_FUNCTIONS_H
#define SIM02_FUNCTIONS_H

typedef struct process
{
  char processName;
  int processNumber;
  int subProcID;
  char processState;
} process;


void createThread();

void threadStart();

void stringCopy(char *source, char* destination);

void addSubProc(int processNum);

struct process createProcess(int processNum, struct process proc,
                             char *meta_data_matrix);

double startProcess(char processor_cycle_time, char io_cycle_time);

void startIOProcess(char *io_cycle_time, char *log_to, char location, char type,
                  int total_io_time,  char *timeArray, double endTime,
                  int procIteration, FILE *log_file);

int createSubProcID(int procIteration);

void returnTimer();


#endif // ifndef SIM02_FUNCTIONS_H
