#ifndef SIM03_FUNCTIONS_H
#define SIM03_FUNCTIONS_H

#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "functions.h"


int startMemProcess(char *log_to, char *available_memory, char *timeArray,
            double endTime, int procIteration, int current_mem, FILE *log_file);

//int stringToInt(char * input_string);

#endif   // SIM03_FUNCTIONS_H
