// Program Information ////////////////////////////////////////////////////////
/**
 * @file runsimulation.h
 *
 * @brief Header file for the sim02 started run simulation processes
 * 
 * @author Matthew Burns
 * 
 * @details Specifies all member methods of the SimpleTimer
 *
 * @version 1.00 (28 February 2018)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef RUNSIMULATION_H
#define RUNSIMULATION_H

// Header files ///////////////////////////////////////////////////////////////

#include <pthread.h>
#include "util_functions.h"

struct file_printStorage
{
    char toPrint[ 120 ];
    struct file_printStorage * next;
};

struct process_headers
{
//process id
    struct MetaDataNode * pointer;
    int counter;
    int size;
    //Bool processed;
    struct process_headers * next;
};

struct memory_manager
{
    int process;
    char segment[2];
    char base[2];
    char memory[2];
    struct memory_manager * next;
};

// Handling Struct
struct file_printStorage *addFPNode( struct file_printStorage *headNode, 
                                            struct file_printStorage *newNode );
struct file_printStorage *makeFPNode( char *toPrint );
struct process_headers *addPHNode( struct process_headers * headNode, 
                                    struct process_headers * newNode );
struct process_headers *makePHNode( struct MetaDataNode * pointer, 
                                    int counter, int size );
struct memory_manager *addMMNode( struct memory_manager *headNode, 
                                            struct memory_manager *newNode );
struct memory_manager *makeMMNode( int process, char *segment, char *base, char *memory );

// Function Prototype  /////////////////////////////////////////////////////////
void runSimulation( struct MetaNodeType * metaNode, 
         struct ConfigNodeType * configNode );
int incrementProcess( struct MetaNodeType *metaNode, 
                      struct ConfigNodeType *config, 
                      int counter, struct file_printStorage * output );
void incProcHelper( struct MetaNodeType *metaNode, 
                      struct ConfigNodeType *config, 
                      int counter, struct file_printStorage * output );
void runParse( struct MetaNodeType *metaNode, struct ConfigNodeType *configNode
               , struct memory_manager * memManager,
                  int counter , struct file_printStorage * output );
void fileOutput( struct file_printStorage * output, char * fileName );
void printOutput( struct file_printStorage * output );
struct memory_manager *findMMNodeBySeg( struct memory_manager *workingNode, 
                                    int seg );

// Runs for Sched Codes
void runFCFSN(  struct MetaNodeType *metaNode, struct ConfigNodeType *configNode,
                 struct file_printStorage * output );
void runSJF(   struct MetaNodeType *metaNode, struct ConfigNodeType *configNode,
              struct file_printStorage * output );


// Made for SJF
void createThread( struct MetaNodeType * metaNode, 
                   struct ConfigNodeType *configNode, 
                   struct process_headers * processThreadPtr );
int createThreadHelper( struct MetaNodeType * metaNode, 
                   struct ConfigNodeType *configNode );
void sortShortest( struct process_headers * processThreadPtr );
void switched( struct process_headers * a, struct process_headers * b );

// Memory
int handleMemory( struct MetaNodeType * metaNode, 
                  struct ConfigNodeType * configNode, char * memory,
                   struct memory_manager * memManager,int counter );


#endif 
