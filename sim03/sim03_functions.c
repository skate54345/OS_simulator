#ifndef SIM03_FUNCTIONS_C
#define SIM03_FUNCTIONS_C

#include <stdio.h>
#include "sim03_functions.h"

int startMemProcess(char *log_to, char *available_memory, char *timeArray,
            double endTime, int procIteration, int current_mem, FILE *log_file)
{
  int mem_seg;
  int mem_base;
  int mem_alloc;
  int mem_exit_code = 0;

//TODO put in struct if needed?

  //mem_seg = current_mem/1000000;
  mem_base = (current_mem)/1000; //removes last digits
  mem_base = mem_base%1000; //removes first digits
  mem_alloc = (current_mem)%1000;

  // printf("Time:  %f, Process %d MMU Allocation: %d/%d/%d\n", endTime,
        // procIteration, mem_seg, mem_base, mem_alloc);

  // printf("%d\n", mem_seg);
  // printf("%d\n", mem_base);
  // printf("%d\n", mem_alloc);
  // printf("\n%d\n", stringToInt(available_memory));

  if ((mem_exit_code == 0) && (mem_alloc>stringToInt(available_memory)))
  {
    printf("Time:  %f, Process %d MMU Allocation: Failed\n", endTime,
           procIteration);
    printf("ERROR: Segmentation fault. Not enough memory available\n");
    mem_exit_code = 1; //signal to stop proc early
  }
  else if ((mem_exit_code == 0) && (!mem_alloc || !current_mem))
  {
    printf("Time:  %f, Process %d MMU Access: Failed\n", endTime,
           procIteration);
    mem_exit_code = 1;
  }
  else
  {
    printf("Time:  %f, Process %d MMU Allocation: Success\n", endTime,
           procIteration);
  }
  return mem_exit_code;
}


#endif //SIM03_FUNCTIONS_C
