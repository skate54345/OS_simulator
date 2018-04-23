/*
string copy modified from site:
https://stackoverflow.com/questions/19641291/how-to-create-my-own-strcpy-function
*/

#ifndef SIM02_FUNCTIONS_H
#define SIM02_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "simtimer.h"
#include "pthread.h"
#define word_size 50
#define GNU_SOURCE

typedef struct process
{
  int subProcID;
  char processState;
  int processNumber;
  int burstTime;
} process;

typedef struct subProc
{
  char component_letter;
  char operation_string;
  char cycle_time;
} subProc;


void createThread();

void threadStart();

void stringCopy(char *source, char* destination);


struct process createProcess(int processNum, struct process proc,
                             char *meta_data_matrix);

struct subProc createSubProc(int processNum, char letter, char string, char cycle_time);

double startProcess(char processor_cycle_time, char io_cycle_time);

void startIOProcess(char *io_cycle_time, char *log_to, char location, char type,
                  int total_io_time,  char *timeArray, double endTime,
                  int procIteration, FILE *log_file);

void returnTimer();


#endif // ifndef SIM02_FUNCTIONS_H
