//function compareStrings() modified from strcpy source code
//stringToInt modified from class notes and link below
//https://www.geeksforgeeks.org/write-your-own-atoi/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>

#include"linkedlist.h"
#include"functions.h"

void skipString(FILE *file, char array[], int times)
{
  int iterator = 0;
  while(iterator<times)
  {
    fscanf(file, "%s", array);
    iterator++;
  }
}

int stringToInt(char *input_string)
{
  int iterator = 0;
  int return_int = 0;
  while(input_string[iterator] != '\0')
  {
    return_int = return_int*10 + input_string[iterator] - '0';
    iterator++;
  }
  return return_int;
}

void trim(char array[], int min, int max)
{
  int iterator = 0;
  for (iterator=min; iterator<max;iterator++)
  {
    array[iterator] = '\0';
  }
}

int compareStrings (const char *string1, const char *string2)
{
    const char *pointer1 = (const char *)string1;
    const char *pointer2 = (const char *)string2;

    while (*pointer1 != '\0')
    {
        if (*pointer2 == '\0')
        {
          return  1;
        }
        if (*pointer2 > *pointer1)
        {
          return -1;
        }
        if (*pointer1 > *pointer2)
        {
          return  1;
        }
        pointer1++;
        pointer2++;
    }

    if (*pointer2 != '\0')
    {
      return -1;
    }
    return 0;
}


int rangeCheck (int test_number, int integer1, int integer2)
{
  if (test_number <= integer1 || test_number >= integer2)
  {
    return 0; //false
  }
  else
  {
    return 1; //true
  }
}



int getConfig(FILE *config_file, char config_buffer[], char version[],
                    char file_path[], char cpu_scheduling_code[],
                    char quantum_time[], char available_memory[],
                    char processor_cycle_time[], char io_cycle_time[],
                    char log_to[], char log_file_path[])
{
  int iterator = 0;
  int error_code = 0;
  while (feof(config_file)==0) //until the end of file
  {
    fscanf(config_file, "%s", config_buffer); //stores text in config_buffer array

    //version section
    if (*config_buffer == 'V') //finds the first (and only) V to skip initial line
    {
      skipString(config_file,version,1);
      //file path section
      //file path is listed next so cycle through the strings: 'testfile2.mdf', 'File', and 'Path:'
      skipString(config_file,file_path,3);//this stores the file path data in "file_path"

      //CPU scheduling code section
      //skip 'Scheduling' 'Code: '
      skipString(config_file,cpu_scheduling_code,4);

      //quantum time section
      //skip 'cycles' and store in variable
      skipString(config_file,quantum_time,4);

      //memory section section
      skipString(config_file,available_memory,4);

      //cpu cycle time section
      skipString(config_file,processor_cycle_time,5);

      //IO cycle time section
      skipString(config_file,io_cycle_time,5);

      //log to section
      skipString(config_file,log_to,3);

      //log file path section
      skipString(config_file,log_file_path,4);
    }
  }
  //version number section
  //trim version number
  trim(version, 1, 20);

  //convert to int and check version number
  if (rangeCheck(stringToInt (version), 0, 10) != 1)
  {
    error_code = 1;
  }

  //quantum time check
  if (rangeCheck(stringToInt (quantum_time), 0, 100) != 1)
  {
    error_code = 2;
  }

  //memory check
  if (rangeCheck(stringToInt (available_memory), 0, 1048576) != 1)
  {
    error_code = 3;
  }

  if (rangeCheck(stringToInt (processor_cycle_time), 1, 1000) != 1)
  {
    error_code = 4;
  }

  if (rangeCheck(stringToInt (io_cycle_time), 1, 10000) != 1)
  {
    error_code = 5;
  }
  if(cpu_scheduling_code[0] == 'N' && cpu_scheduling_code[1] == 'O') //if NONE is encountered
  {
    //clear array
    for (iterator=0; iterator<10;iterator++)
    {
      cpu_scheduling_code[iterator] = '\0';
    }
    //write new code
    cpu_scheduling_code[0] = 'F';
    cpu_scheduling_code[1] = 'C';
    cpu_scheduling_code[2] = 'N';
    cpu_scheduling_code[3] = 'F';
    cpu_scheduling_code[4] = '-';
    cpu_scheduling_code[5] = 'N';
    //"FCNF-N";
  }
  //check for SJF-N
  else if(cpu_scheduling_code[0] == 'S' && cpu_scheduling_code[1] == 'J')
  {
    //clear array
    for (iterator=0; iterator<10;iterator++)
    {
      cpu_scheduling_code[iterator] = '\0';
    }
    cpu_scheduling_code[0] = 'S';
    cpu_scheduling_code[1] = 'J';
    cpu_scheduling_code[2] = 'F';
    cpu_scheduling_code[3] = '-';
    cpu_scheduling_code[4] = 'N';
  }
  return error_code;
}


void getMetaData(FILE *meta_data_file)
{
  char meta_data_buffer[ STD_STR_LEN ];
  //skip first line, store in buffer
  skipString(meta_data_file, meta_data_buffer, 4);
}



#endif   // FUNCTIONS_H
