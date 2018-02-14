#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


int main()
{
  //TODO rename program to driver?

    FILE *config_file;
    config_file = fopen("config1.cnf","r");

    char version[20];
    char file_path[100];
    char cpu_scheduling_code[10];
    char quantum_time[10];
    char available_memory[100];
    char processor_cycle_time[10];
    char io_cycle_time[10];
    char log_to[10];
    char log_file_path[100];

    //checks if file exists
    if (!config_file)
    {
      printf("No valid configuration file.\n");
      return 0;
    }

    //Open config_file file
    char next_string[500] = "";

    //Scan in first string for head node
    fscanf(config_file, "%s", next_string);

    //create head, fill it in with the first string, and create current

    //Scan in first string for head node
    fscanf(config_file, "%s", next_string);

    //create head, fill it in with the first string, and create current
    Node *head = malloc(sizeof(Node));
    head->next = malloc(sizeof(Node));
    head->string = next_string;

    printf("%s ", head->string);
    Node *current = head->next;

//Begin Iteration
    while(fscanf(config_file, "%s", next_string) != EOF)
    {
        current = (Node*)malloc(sizeof(Node));
        current->string = next_string;
        current->next = NULL;
        printf("%s ", current->string);
        current = current->next;
        if(compareStrings(head->string, "Version/Phase:")==0)
        {
          //printf("%s ", current->string);
        }

   }

    //printList(head);
 }

// int main(void)
// {
//
// //TODO rename program to driver?
//
//   char line_buffer[1000]; //where new config data is stored
//   FILE *config_file_pointer;
//   config_file_pointer = fopen("config1.cnf","r");
//   config_file_pointer = config_file_pointer;
//
//   char version[20];
//   char file_path[100];
//   char cpu_scheduling_code[10];
//   char quantum_time[10];
//   char available_memory[100];
//   char processor_cycle_time[10];
//   char io_cycle_time[10];
//   char log_to[10];
//   char log_file_path[100];
//
//   //checks if file exists
//   if (!config_file_pointer)
//   {
//      return 0;
//   }
//
//   //starts the config file scan
//   while (feof(config_file_pointer)==0) //until the end of file
//   {
//     fscanf(config_file_pointer, "%s", line_buffer); //stores text in line_buffer array
//
//     //version section
//     if (*line_buffer == 'V') //finds the first (and only) V to skip initial line
//     {
//       fscanf(config_file_pointer, "%s", version); //jump to string and store in version array
//
//       //file path section
//       //file path is listed next so cycle through the strings: 'testfile2.mdf', 'File', and 'Path:'
//       fscanf(config_file_pointer, "%s", file_path);
//       fscanf(config_file_pointer, "%s", file_path);
//       fscanf(config_file_pointer, "%s", file_path); //this stores the file path data in "file_path"
//
//       //CPU scheduling code section
//       fscanf(config_file_pointer, "%s", cpu_scheduling_code);
//       fscanf(config_file_pointer, "%s", cpu_scheduling_code);//skip 'CPU'
//       fscanf(config_file_pointer, "%s", cpu_scheduling_code);//skip 'Scheduling'
//       fscanf(config_file_pointer, "%s", cpu_scheduling_code);//skip 'Code:' and store result in array
//
//
//       //quantum time section
//       fscanf(config_file_pointer, "%s", quantum_time);
//       fscanf(config_file_pointer, "%s", quantum_time);
//       fscanf(config_file_pointer, "%s", quantum_time);
//       fscanf(config_file_pointer, "%s", quantum_time);//skip 'cycles' and store in variable
//     }
//
//     //logfile path section
//     else if (*line_buffer == 'L') //check all 'L strings' (Log)
//     {
//       fscanf(config_file_pointer, "%s", log_file_path); //jump to next string
//       if (*log_file_path == 'F') //checks if next string is 'File'
//       {
//         fscanf(config_file_pointer, "%s", log_file_path); //skip 'File'
//         fscanf(config_file_pointer, "%s", log_file_path); //skip 'Path:' and store next string
//         //printf("Log File Path: %s \n", log_file_path);
//       }
//     }
//
//     //available memory section
//     else if (*line_buffer == 'A')
//     {
//       //config_file_pointer = config_file_pointer;//reset backup array
//       fscanf(config_file_pointer, "%s", available_memory); //jump to next string
//       fscanf(config_file_pointer, "%s", available_memory); //skip '(KB):' and store memory in array
//       //printf("Memory Available: %s \n", available_memory);
//     }
//
//     //processor cycle time section
//     else if (*line_buffer == 'P') //check all 'P strings'
//     {
//       //config_file_pointer = config_file_pointer;//reset backup array
//       fscanf(config_file_pointer, "%s", processor_cycle_time); //jump to next string
//       fscanf(config_file_pointer, "%s", processor_cycle_time); //skip 'cycle'
//       fscanf(config_file_pointer, "%s", processor_cycle_time); //skip 'time'
//       fscanf(config_file_pointer, "%s", processor_cycle_time); //skip '(msec):'
//       if (*processor_cycle_time >= '0' && *processor_cycle_time <= '9') //if string (skipped from all P strings starts with number
//       {
//         //printf("Processor Cycle Time: %s \n", processor_cycle_time);
//       }
//       config_file_pointer = config_file_pointer;
//     }
//
//
//
//   }
//   //TODO NEED TO CONVERT DATA TYPES AND FAIL IF OTHER OPTIONS
//
//   if(*cpu_scheduling_code == 'N') //if NONE is encountered
//   {
//     //clear array
//     for (int i=0; i<sizeof(cpu_scheduling_code);i++)
//     {
//       cpu_scheduling_code[i] = '\0';
//     }
//     //write new code
//     cpu_scheduling_code[0] = 'F';
//     cpu_scheduling_code[1] = 'C';
//     cpu_scheduling_code[2] = 'N';
//     cpu_scheduling_code[3] = 'F';
//     cpu_scheduling_code[4] = '-';
//     cpu_scheduling_code[5] = 'N';
//     //"FCNF-N";
//   }
//   printf("Version: %s \n", version);
//   printf("File Path: %s \n", file_path);
//   printf("CPU Scheduling Code: %s \n", cpu_scheduling_code);
//   printf("Quantum Time (in cycles): %s \n", quantum_time);
//   printf("Memory Available (in KB): %s \n", available_memory);
//   printf("Processor Cycle Time: %s \n", processor_cycle_time);
//   printf("Log File Path: %s \n", log_file_path);
//
//   return 0;
// }
