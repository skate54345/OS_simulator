#ifndef SIM04_FUNCTIONS_C
#define SIM04_FUNCTIONS_C


#include "sim04_functions.h"


//shortest job first non-preemptive
void SJFN(char *log_to, int PCBIteration, int row, int col,
            char *meta_data_matrix[100][100][100])
{
  //printf("\n\n%s\n\n", meta_data_matrix[0][1][0]);
}


void run(FILE *log_file, int ending_row, char *timeArray, char *meta_data_matrix[100][100][100])
{
  char config_buffer[10000]; //where new config data is stored
  char file_out_array[10000];
  FILE *config_file;
  FILE *meta_data_file;
  //FILE *log_file;
//  char *meta_data_matrix[10][100][100]; //main matrix for meta data
  char version[20];
  char file_path[100];
  char cpu_scheduling_code[10];
  char quantum_time[10];
  char available_memory[100];
  char processor_cycle_time[10];
  char io_cycle_time[10];
  char log_to[10];
  char log_file_path[100];
  int current_mem;
  int error_code = 0;
  //int ending_row;

  struct subProc sub_proc_array[100];
//  char timeArray[20];
  double startTime;
  double endTime;
  int procIteration = 0;
  int PCBIteration = 0;
  int total_time;
  int total_io_time;
//  struct proc process_array[100];//array of proc (from A to A)

  struct NodeType *headPtr = NULL;
  // data node created, must be released
  struct NodeType *dataPtr
                  = ( struct NodeType * )malloc( sizeof( struct NodeType ) );
  char meta_data_buffer[ STD_STR_LEN ];

  int row = 0;
  int col = 0;
  /* /FCFS-N*////////////////////////////////////////////////////////////////////
        for(row = 0; row<ending_row; row++)
        {
          //loop between 'A' start and 'A' end (1 process)
          if(*meta_data_matrix[PCBIteration][row][0] == 'A' && *meta_data_matrix[PCBIteration][row][0] != 'M'
                            && *meta_data_matrix[PCBIteration][row][1] == 's')
          {
            endTime = accessTimer(1,timeArray);
            if(log_to[0] != 'F') //if logs to monitor or both
            {
              printf("Time:  %f, OS: %s Strategy selects Process %d "\
                              "with time: %s mSec\n", endTime, cpu_scheduling_code,
                              procIteration, processor_cycle_time);
            }
            else
            {
              //write to file
              fprintf(log_file, "Time:  %f, OS: %s Strategy selects "\
                              "Process %d with time: %s mSec\n", endTime,
                              cpu_scheduling_code, procIteration, processor_cycle_time);
            }


            endTime = accessTimer(1,timeArray);
            if(log_to[0] != 'F')
            {
              printf("Time:  %f, OS: Process %d Set in Running State\n", endTime,
                              procIteration);
            }
            else
            {
              fprintf(log_file,"Time:  %f, OS: Process %d Set in "\
                              "Running State\n", endTime, procIteration);
            }
          }

          else if(*meta_data_matrix[PCBIteration][row][0] != 'A' && row != 0)
          {
            //set time to required values
            total_time = stringToInt(processor_cycle_time)*(*meta_data_matrix[PCBIteration][row][2]);
            total_io_time = stringToInt(io_cycle_time)*(*meta_data_matrix[PCBIteration][row][2]);
            char location = *meta_data_matrix[PCBIteration][row][1];
            char type = *meta_data_matrix[PCBIteration][row][0];
            if (*meta_data_matrix[PCBIteration][row][0] != 'I'
                              && *meta_data_matrix[PCBIteration][row][0] != 'O')
            {
  //////////////MMU section//////////////////////////////////////////////////////
              //if equal to 'Memory'
              //proc matrix column goes in order: M,
              if(*meta_data_matrix[PCBIteration][row][0] == 'M' && row != 0) //memory
              {
                current_mem = *meta_data_matrix[PCBIteration][row][2];

                if(*log_to == 'M' || *log_to == 'B')
                {
                  if(log_to[0] != 'F')
                  {
                    printf("Time:  %f, Process %d memory management action"\
                                " start\n", endTime, procIteration);

                    endTime = accessTimer(1,timeArray);
                    //starts the memory section
                    startMemProcess(log_to, available_memory, timeArray, endTime,
                                    procIteration, current_mem, log_file);
                    endTime = accessTimer(1,timeArray); //stop timer
                    printf("Time:  %f, Process %d memory management action"\
                                " end\n", endTime, procIteration);

                  }
                  else
                  {
                    fprintf(log_file, "Time:  %f, Process %d "\
                                "memory management action start\n",
                                endTime, procIteration);
                    fprintf(log_file, "Time:  %f, Process %d memory "\
                                "management action end\n",
                                endTime, procIteration);
                  }
                }
              }
              else
              {
                runTimer(total_time);
                endTime = accessTimer(1,timeArray);
                if(log_to[0] != 'F')
                {
                  printf("Time:  %f, Process %d run operation start\n", endTime,
                                 procIteration);
                  printf("Time:  %f, Process %d run operation end\n", endTime,
                                 procIteration);
                }
                else
                {
                  fprintf(log_file, "Time:  %f, Process %d run operation "\
                                 "start\n", endTime, procIteration);
                  fprintf(log_file, "Time:  %f, Process %d run operation "\
                                 "end\n", endTime, procIteration);
                }
              }
            }
            else //io process
            {
              startIOProcess(io_cycle_time, log_to, location, type, total_io_time,
                                timeArray, endTime, procIteration, log_file);
              char start[20] = {'s','t','a','r','t','\0'};
              start[20] = start[20];
              if(log_to[0] != 'F')
              {
                printf("start\n");
              }
              else
              {
                fprintf(log_file,"start\n");
              }
              runTimer(total_io_time);
              createThread();
              startIOProcess(io_cycle_time, log_to, location, type, total_io_time,
                                timeArray, endTime, procIteration, log_file);
              if(log_to[0] != 'F')
              {
                printf("end\n");
              }
              else
              {
                fprintf(log_file,"end\n");
              }
            }

            // //assign proc number to matrix
            // meta_data_matrix[row][col+3] = procIteration;
            // //assign process number
            // meta_data_matrix[row][3] = procIteration;

          }

          //exit
          else if(*meta_data_matrix[PCBIteration][row][0] == 'A' &&
                            *meta_data_matrix[PCBIteration][row][1] == 'e')
          {
            // printf("%s\n", meta_data_matrix[PCBIteration][0][0]);
            // printf("%s\n", meta_data_matrix[PCBIteration][0][1]);
            // printf("%s\n\n", meta_data_matrix[PCBIteration][0][2]);

            printf("Process %d start time: %f\n", procIteration, startTime);
            printf("Process %d end time: %f\n", procIteration, endTime);

            endTime = accessTimer(1, timeArray);
            if(log_to[0] != 'F')
            {
              printf("Time:  %f, OS: Process %d Set in Exit State\n", endTime,
                              procIteration);
            }
            else
            {
              fprintf(log_file, "Time:  %f, OS: Process %d Set in Exit "\
                              "State\n", endTime, procIteration);
            }

            startTime = endTime;
            procIteration++;
          }
        }

        //HOW TO PASS TO FUNTION
        //SJFN(log_to, PCBIteration, row, col, meta_data_matrix);

        procIteration = 0; //reset iterator
        printf("%s\n", file_out_array);
        //fclose(meta_data_file);
        //fclose(log_file);


        endTime = accessTimer(1,timeArray);
        if(log_to[0] != 'F')
        {
          printf("Time:  %f, System Stop\n", endTime);
        }
        else
        {
          fprintf(log_file, "Time:  %f, System Stop\n", endTime);
        }
        PCBIteration++;
        procIteration = 0; //reset iterator
}



#endif //SIM04_FUNCTIONS_C
