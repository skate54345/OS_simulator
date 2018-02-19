#include "simtimer.h"

#ifndef SIM02_FUNCTIONS_H
#define SIM02_FUNCTIONS_H

typedef struct process
{
  char processName;
  int processNumber;
} process;


struct process createProcess(int processNum, struct process proc,
                             char *meta_data_matrix);

double startProcess(char processor_cycle_time, char io_cycle_time);

int startIOProcess();

void returnTimer();


#endif // ifndef SIM02_FUNCTIONS_H
