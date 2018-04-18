//function compareStrings() modified from strcpy source code
//stringToInt modified from class notes and link below
//https://www.geeksforgeeks.org/write-your-own-atoi/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>

void skipString(FILE *file, char array[], int times);

int stringToInt(char * input_string);

void trim(char array[], int min, int max);

int compareStrings (const char *string1, const char *string2);

int rangeCheck (int test_number, int integer1, int integer2);



int getConfig(FILE *config_file, char config_buffer[], char version[],
                    char file_path[], char cpu_scheduling_code[],
                    char quantum_time[], char available_memory[],
                    char processor_cycle_time[], char io_cycle_time[],
                    char log_to[], char log_file_path[]);

void getMetaData(FILE *meta_data_file);


#endif // FUNCTIONS_H
