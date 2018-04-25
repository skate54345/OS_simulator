#ifndef SIM04_FUNCTIONS_H
#define SIM04_FUNCTIONS_H

#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linkedlist.h"
#include "simtimer.h"
#include "functions.h"
#include "sim02_functions.h"
#include "sim03_functions.h"


int checkFCFSN(char *cpu_scheduling_code);

int checkFCFSP(char *cpu_scheduling_code);


void FCFSN(FILE *log_file, int ending_row, char *timeArray, double startTime,
            double endTime, char *log_to, char *cpu_scheduling_code,
            char *processor_cycle_time, char *available_memory,
            char *io_cycle_time, char *quantum_time, char *log_file_path,
            char *meta_data_matrix[100][100][100]);



#endif   // SIM04_FUNCTIONS_H
