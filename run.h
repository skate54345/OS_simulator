#ifndef RUN_H
#define RUN_H

#include <stdio.h>
#include <stdlib.h>
#include "sim02_functions.h"

void run(int argc, char **argv);

int getConfig(FILE *config_file, char config_buffer[], char version[],
                    char file_path[], char cpu_scheduling_code[],
                    char quantum_time[], char available_memory[],
                    char processor_cycle_time[], char io_cycle_time[],
                    char log_to[], char log_file_path[]);

#endif // RUN_H
