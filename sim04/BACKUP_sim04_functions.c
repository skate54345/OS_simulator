#ifndef SIM04_FUNCTIONS_C
#define SIM04_FUNCTIONS_C


#include "sim04_functions.h"

//shortest job first non-preemptive
void SJFN(char *log_to, int PCBIteration, int row, int col,
            char *meta_data_matrix[100][100][100])
{
  //printf("\n\n%s\n\n", meta_data_matrix[0][1][0]);
}

void run(FILE *log_file, int ending_row, char *timeArray, double startTime,
            double endTime, char *log_to, char *cpu_scheduling_code,
            char *processor_cycle_time, char *available_memory,
            char *io_cycle_time, char *quantum_time,
            char *meta_data_matrix[100][100][100])
{
  char file_out_array[10000];
  char string_buffer[100];
  int current_mem;
  int procIteration = 0;
  int PCBIteration = 0;
  int total_time;
  int total_io_time;
  int row = 0;

  printf("Quantum time:   %s\n", quantum_time);


  startTime = accessTimer(0,timeArray);//+endTime; //start
  /* /FCFS-N*////////////////////////////////////////////////////////////////////

  //set time to required values
  total_time = stringToInt(processor_cycle_time)*(*meta_data_matrix[PCBIteration][row][2]);
  total_io_time = stringToInt(io_cycle_time)*(*meta_data_matrix[PCBIteration][row][2]);

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
                              "with time: %d mSec\n", endTime, cpu_scheduling_code,
                              procIteration, total_time);
            }
            else
            {
              //write to file
              fprintf(log_file, "Time:  %f, OS: %s Strategy selects "\
                              "Process %d with time: %d mSec\n", endTime,
                              cpu_scheduling_code, procIteration, total_time);
            }


            //set to running state

            meta_data_matrix[PCBIteration][row][3] = "R";

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
                endTime = accessTimer(1,timeArray);
            }
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
