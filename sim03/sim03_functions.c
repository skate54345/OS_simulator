#ifndef SIM03_FUNCTIONS_C
#define SIM03_FUNCTIONS_C

#include <stdio.h>

void startMemProcess(char *log_to, char *available_memory, char *timeArray,
            double endTime, int procIteration, int current_mem, FILE *log_file)
{
  char mem_array[100];
  int mem_seg;
  int mem_base;
  int mem_alloc;

  mem_seg = stringToInt(current_mem)/1000000;
  mem_base = stringToInt(current_mem)/1000; //removes last digits
  mem_base = mem_base%1000; //removes first digits
  mem_alloc = stringToInt(current_mem)%1000;

  // printf("%d\n", mem_seg);
  // printf("%d\n", mem_base);
  // printf("%d\n", mem_alloc);
  // printf("\n%d\n", stringToInt(available_memory));

  if (mem_alloc>stringToInt(available_memory))
  {
    printf("ERROR: Segmentation fault. Not enough memory available to hold "\
            "memory in %d. \nContinuing operation.\n", procIteration);
  }
}


#endif //SIM03_FUNCTIONS_C
