#include "runsimulation.h"
#include <strings.h>

// These two functions add to our output
struct file_printStorage *addFPNode( struct file_printStorage *headNode,
                                            struct file_printStorage *newNode )
   {

    // check for viable node
    if( headNode != NULL )
    {
        headNode->next = addFPNode( headNode->next, newNode );

        return headNode;
    }
    else
    {
       // assume empty head node
       headNode = makeFPNode( newNode->toPrint );
       return headNode;
   }
}

struct file_printStorage *makeFPNode( char *print )
   {
    struct file_printStorage *newNode
                   = ( struct file_printStorage * ) malloc( sizeof( struct file_printStorage ) );

    strcpy( newNode->toPrint, print );
    newNode->next = NULL;

    return newNode;
   }

//For process headers
struct process_headers *addPHNode( struct process_headers *headNode,
                                            struct process_headers *newNode )
   {

    // check for viable node
    if( headNode != NULL )
    {
        headNode->next = addPHNode( headNode->next, newNode );

        return headNode;
    }
    else
    {
       // assume empty head node
       headNode = makePHNode( newNode->pointer, newNode->counter, newNode->size );
       return headNode;
   }
}

struct process_headers *makePHNode( struct MetaDataNode * pointer,
                                    int counter, int size )
   {
    struct process_headers *newNode
                   = ( struct process_headers * ) malloc( sizeof( struct process_headers ) );

    newNode->pointer = pointer;
    newNode->counter = counter;
    newNode->size = size;
    newNode->next = NULL;

    return newNode;
   }

struct memory_manager *addMMNode( struct memory_manager *headNode,
                                            struct memory_manager *newNode )
   {

    // check for viable node
    if( headNode != NULL )
    {
        headNode->next = addMMNode( headNode->next, newNode );

        return headNode;
    }
    else
    {
       // assume empty head node
       headNode = makeMMNode( newNode->process, newNode->segment,
                              newNode->base, newNode->memory );
       return headNode;
   }
}

struct memory_manager *makeMMNode( int process, char *segment, char *base, char *memory )
   {
    struct memory_manager *newNode
                   = ( struct memory_manager * ) malloc( sizeof( struct memory_manager ) );
    newNode->process = process;
    strcpy( newNode->segment, segment );
    strcpy( newNode->base, base );
    strcpy( newNode->memory, memory );
    newNode->next = NULL;

    return newNode;
   }
struct memory_manager *findMMNodeBySeg( struct memory_manager *workingNode, int seg )
   {
    if( workingNode != NULL )
       {
        if( stringToInt( workingNode->segment) == seg )
           {
            return makeMMNode( workingNode->process, workingNode->segment,
                               workingNode->base, workingNode->memory);
           }

        return findMMNodeBySeg( workingNode->next, seg );
       }

    return NULL;
   }

void runSimulation( struct MetaNodeType *metaPtr, struct ConfigNodeType *configPtr )
{

    struct ConfigNodeType *tempCNodePtr = ( struct ConfigNodeType * )malloc(
                                       sizeof( struct ConfigNodeType ) );
    struct file_printStorage * output= ( struct file_printStorage * )malloc(
                                       sizeof( struct file_printStorage ) );

    char *schedCode = ( char * )malloc( sizeof( char ) * MAX_STR_LEN );
    char *logPath = ( char * )malloc( sizeof( char ) * MAX_STR_LEN );
    char *logTo = ( char * )malloc( sizeof( char ) * MAX_STR_LEN );
    //int p_time, io_time = 0;

    tempCNodePtr = findConfigNodeByName( configPtr, "CPU Scheduling Code");
    strcpy( schedCode, tempCNodePtr->selectionName );
    tempCNodePtr = findConfigNodeByName( configPtr, "Log To");
    strcpy( logTo, tempCNodePtr->selectionName );
    tempCNodePtr = findConfigNodeByName( configPtr, "Log File Path");
    strcpy( logPath, tempCNodePtr->selectionName );

metaPtr = metaPtr->next;

    if( strcmp( schedCode, "FCFS-N" ) == 0 ||
        strcmp( schedCode, "NONE" ) == 0 )
    {

        runFCFSN( metaPtr, configPtr, output );
    }
    else if( strcmp( schedCode, "SJF-N" ) == 0 )
    {

        runSJF( metaPtr, configPtr, output );
    }


    if( strcmp( logTo, "File" ) == 0 )
    {
        fileOutput( output, logPath );
    }
    else if( strcmp( logTo, "Monitor" ) == 0 )
    {
        printOutput( output );
    }
    else
    {
        fileOutput( output, logPath );
        printOutput( output );
    }
}

void runFCFSN(  struct MetaNodeType *metaNode, struct ConfigNodeType *configNode
                , struct file_printStorage * output )
{
    struct memory_manager *memManager = ( struct memory_manager * )malloc(
                                       sizeof( struct memory_manager ) );
    int counter = -1;

    while( metaNode != NULL )
    {
        counter = incrementProcess( metaNode, configNode, counter, output );
        runParse( metaNode, configNode, memManager, counter, output );
        metaNode = metaNode->next;
    }
}

void runSJF(   struct MetaNodeType *metaNode, struct ConfigNodeType *configNode
                , struct file_printStorage * output )
{
    //store processes into a linked list: pointer address/process number/length/next
    struct process_headers * processThreadPtr = ( struct process_headers * )malloc(
                                       sizeof( struct process_headers ) );
    struct file_printStorage *tempOutput = ( struct file_printStorage * )malloc(
                                       sizeof( struct file_printStorage ) );
    struct memory_manager *memManager = ( struct memory_manager * )malloc(
                                       sizeof( struct memory_manager ) );

    char timeString[ MAX_STR_LEN ];
    char *timePtr = timeString;
    float time = 0;

    // Capture S
    runParse( metaNode, configNode, memManager, 0, output );

    //store processes into a linked list: pointer address/process number/length/next
    createThread( metaNode, configNode, processThreadPtr );
    processThreadPtr = processThreadPtr->next;

    time = accessTimer(LAP_TIMER, timePtr);
    sprintf( tempOutput->toPrint,
          "Time: %f, OS: All processes initialized in New state\n", time );
    output = addFPNode( output, tempOutput );

    sortShortest( processThreadPtr ); // THIS IS THE ERROR

    time = accessTimer(LAP_TIMER, timePtr);
    sprintf( tempOutput->toPrint, "Time: %f, OS: All processes initialized in Ready state\n", time );
    output = addFPNode( output, tempOutput );
    //while loop that runParse for each different process

    while( processThreadPtr != NULL )
    {
        metaNode = processThreadPtr->pointer;
        do
        {
            runParse( metaNode, configNode, memManager, processThreadPtr->counter, output );
            metaNode = metaNode->next;
        }while( metaNode->component != 'A' && strcmp( metaNode->operation, "end" ) != 0 );
        processThreadPtr = processThreadPtr->next;
    }
    // Capture S
    runParse( metaNode, configNode, memManager, 0, output );

}

//used for FCFSN

int incrementProcess( struct MetaNodeType *metaNode,
                      struct ConfigNodeType *configNode,
                      int counter, struct file_printStorage * output )
{
    if( metaNode->component == 'A' && strcmp( metaNode->operation, "start" ) == 0 )
    {
        incProcHelper( metaNode, configNode, counter, output );
        return counter + 1;
    }
    return counter;
}

// For SJF
void createThread( struct MetaNodeType * metaNode,
                   struct ConfigNodeType *configNode,
                   struct process_headers * processThreadPtr )
{
    struct process_headers * tempThread = ( struct process_headers * )malloc(
                                       sizeof( struct process_headers ) );
    int  counter = 0;
    while( metaNode != NULL )
    {
        if( metaNode->component == 'A' && strcmp( metaNode->operation, "start" ) == 0 )
        {
            tempThread->pointer = metaNode;
            tempThread->counter = counter;
            tempThread->size = createThreadHelper(metaNode, configNode );
            processThreadPtr = addPHNode( processThreadPtr, tempThread );
            counter += 1;
        }
        metaNode = metaNode->next;
    }
}

int createThreadHelper( struct MetaNodeType * metaNode,
                   struct ConfigNodeType *configNode )
{
    struct ConfigNodeType *tempCNodePtr = ( struct ConfigNodeType * )malloc(
                                       sizeof( struct ConfigNodeType ) );
    int p_time, io_time = 0;

    tempCNodePtr = findConfigNodeByName( configNode, "Processor Cycle Time (msec)");
    p_time = tempCNodePtr->selectionNum;
    tempCNodePtr = findConfigNodeByName( configNode, "I/O Cycle Time (msec)");
    io_time = tempCNodePtr->selectionNum;

    int runningCPUTime = 0;
    int runningIOTime = 0;
    int totalTime = 0;

    while( strcmp( metaNode->operation, "end") != 0 )
    {
        if( metaNode->component == 'O' || metaNode->component == 'I' )
        {
            runningIOTime += metaNode->cycleTime;
        }
        else
        {
            runningCPUTime += metaNode->cycleTime;
        }
        metaNode = metaNode->next;
    }
    totalTime = ( runningCPUTime * p_time ) + (runningIOTime * io_time );
    return totalTime;

}

void sortShortest( struct process_headers * processThreadPtr )
{
    int swapped;
    struct process_headers * ptl = ( struct process_headers * )malloc(
                                       sizeof( struct process_headers ) );
    struct process_headers * ptr = ( struct process_headers * )malloc(
                                       sizeof( struct process_headers ) );
    ptr = NULL;
    do
    {
        swapped = 0;
        ptl = processThreadPtr;

        while( ptl->next != ptr )
        {

            if( ptl->size > ptl->next->size )
            {
                switched( ptl, ptl->next );
                swapped = 1;
            }
            ptl = ptl->next;
        }
        ptr = ptl;
    }
    while( swapped );
}

void switched( struct process_headers * a, struct process_headers * b )
{
    struct MetaDataNode * tempPointer = a->pointer;
    int tempCounter = a->counter;
    int tempSize = a->size;
    a->pointer = b->pointer;
    a->counter = b->counter;
    a->size = b->size;
    b->pointer = tempPointer;
    b->counter = tempCounter;
    b->size = tempSize;
}

void incProcHelper( struct MetaNodeType *metaNode,
                      struct ConfigNodeType *configNode,
                      int counter, struct file_printStorage * output )
{
    struct ConfigNodeType *tempCNodePtr = ( struct ConfigNodeType * )malloc(
                                       sizeof( struct ConfigNodeType ) );
    struct file_printStorage *tempOutput = ( struct file_printStorage * )malloc(
                                       sizeof( struct file_printStorage ) );
    char timeString[ MAX_STR_LEN ];
    char *schedCode = ( char * )malloc( sizeof( char ) * MAX_STR_LEN );
    char *timePtr = timeString; //TODO: so we can pass it to our threaded function
    float time = 0;
    //char temp = '';
    int p_time, io_time = 0;

    tempCNodePtr = findConfigNodeByName( configNode, "Processor Cycle Time (msec)");
    p_time = tempCNodePtr->selectionNum;
    tempCNodePtr = findConfigNodeByName( configNode, "I/O Cycle Time (msec)");
    io_time = tempCNodePtr->selectionNum;
    tempCNodePtr = findConfigNodeByName( configNode, "CPU Scheduling Code");
    strcpy( schedCode, tempCNodePtr->selectionName );


    int runningCPUTime = 0;
    int runningIOTime = 0;
    int totalTime = 0;

    while( strcmp( metaNode->operation, "end") != 0 )
    {
        if( metaNode->component == 'O' || metaNode->component == 'I' )
        {
            runningIOTime += metaNode->cycleTime;
        }
        else
        {
            runningCPUTime += metaNode->cycleTime;
        }
        metaNode = metaNode->next;
    }
    //TODO: Thread this?
    time = accessTimer(LAP_TIMER, timePtr);
    totalTime = ( runningCPUTime * p_time ) + (runningIOTime * io_time );
    sprintf( tempOutput->toPrint,
           "Time: %f, OS: %s strategy chooses process %d with time: %d mSec\n",
            time, schedCode, counter + 1, totalTime);
    output = addFPNode( output, tempOutput );

}



void runParse( struct MetaNodeType *metaNode, struct ConfigNodeType *configNode,
               struct memory_manager * memManager, int counter,
               struct file_printStorage * output )
{
    struct ConfigNodeType *tempCNodePtr = ( struct ConfigNodeType * )malloc(
                                       sizeof( struct ConfigNodeType ) );
    struct file_printStorage *tempOutput = ( struct file_printStorage * )malloc(
                                       sizeof( struct file_printStorage ) );
    char *memReq = ( char * )malloc( sizeof( char ) * MAX_STR_LEN );
    char timeString[ MAX_STR_LEN ];
    char *timePtr = timeString;
    float time = 0;
    int p_time, io_time = 0;
    int runningTime = metaNode->cycleTime / 1000;
    int * time_ptr = &runningTime;

    tempCNodePtr = findConfigNodeByName( configNode, "Processor Cycle Time (msec)");
    p_time = tempCNodePtr->selectionNum;
    tempCNodePtr = findConfigNodeByName( configNode, "I/O Cycle Time (msec)");
    io_time = tempCNodePtr->selectionNum;
    tempCNodePtr = findConfigNodeByName( configNode, "Memory Available (KB)");
    strcpy( memReq, tempCNodePtr->selectionName );
    //Set up pthread
    pthread_t tid;

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    if( metaNode->component == '0' || metaNode->component == 'I' )
    {
        runningTime = runningTime + io_time; // or *?
    }
    else
    {
        runningTime = runningTime + p_time;
    }

    if( metaNode->component == 'S' )
    {
        if( strcmp( metaNode->operation, "start" ) == 0 )
        {
            time = accessTimer(ZERO_TIMER, timePtr );
            sprintf( tempOutput->toPrint,
                      "Time: %f, System start\n", time );
            output = addFPNode( output, tempOutput );
            time = accessTimer( LAP_TIMER, timePtr );
            sprintf( tempOutput->toPrint,
                      "Time: %f, Begin PCB creation\n", time );
            output = addFPNode( output, tempOutput );
        }
        else if( strcmp( metaNode->operation, "end" ) == 0 )
        {
            time = accessTimer( STOP_TIMER, timePtr );
            sprintf( tempOutput->toPrint, "Time: %f, System stop\n", time );
            output = addFPNode( output, tempOutput );
        }
    }
    else if( metaNode->component == 'A' )
    {
        if( strcmp( metaNode->operation, "start" ) == 0 )
        {

            time = accessTimer( LAP_TIMER, timePtr );
            sprintf(tempOutput->toPrint,
                   "Time: %f, OS: Process %d set in running state\n",
                    time, counter );
            output = addFPNode( output, tempOutput );
        }
        else if( strcmp( metaNode->operation, "end" ) == 0 )
        {
            time = accessTimer( LAP_TIMER, timePtr );
            sprintf( tempOutput->toPrint,
                  "Time: %f, OS: Process %d set in exit state\n",
                     time, counter );
            output = addFPNode( output, tempOutput );
        }
    }
    else if( metaNode->component == 'I' )
    {
        time = accessTimer( LAP_TIMER, timePtr );
        sprintf(tempOutput->toPrint, "Time: %f, Process %d, %s input start\n",
                  time, counter, metaNode->operation  );
        output = addFPNode( output, tempOutput );

        pthread_create( &tid, NULL, runTimer, (void *)time_ptr );
        pthread_join( tid, NULL );
        //runTimer( runningTime );;

        time = accessTimer( LAP_TIMER, timePtr );
        sprintf( tempOutput->toPrint, "Time: %f, Process %d, %s input end\n",
                  time, counter, metaNode->operation  );
        output = addFPNode( output, tempOutput );
    }
    else if( metaNode->component == 'O' )
    {
        time = accessTimer( LAP_TIMER, timePtr );
        sprintf( tempOutput->toPrint, "Time: %f, Process %d, %s output start\n",
                  time, counter, metaNode->operation  );
        output = addFPNode( output, tempOutput );

        pthread_create( &tid, NULL, runTimer, (void *)time_ptr );
        pthread_join( tid, NULL );
        //runTimer( runningTime );

        time = accessTimer( LAP_TIMER, timePtr );
        sprintf( tempOutput->toPrint, "Time: %f, Process %d, %s output end\n",
                  time, counter, metaNode->operation  );
        output = addFPNode( output, tempOutput );
    }
    else if( metaNode->component == 'M' )
    {
        time = accessTimer( LAP_TIMER, timePtr );
        sprintf( tempOutput->toPrint,
                 "Time: %f, Process %d, Memory management %s action start\n",
                  time, counter, metaNode->operation  );
        output = addFPNode( output, tempOutput );

        pthread_create( &tid, NULL, runTimer, &runningTime );
        handleMemory( metaNode, configNode, memReq, memManager, counter );
        //pthread_join( tid, NULL );

        time = accessTimer( LAP_TIMER, timePtr );
        sprintf( tempOutput->toPrint,
            "Time: %f, Process %d, Memory management %s action end\n",
                  time, counter, metaNode->operation  );
        output = addFPNode( output, tempOutput );
    }
    else if( metaNode->component == 'P' )
    {
        time = accessTimer( LAP_TIMER, timePtr );
        sprintf( tempOutput->toPrint,
            "Time: %f, Process %d, %s operation start\n",
                  time, counter, metaNode->operation  );
        output = addFPNode( output, tempOutput );

        //pthread_create( &tid, NULL, runTimer, &runningTime );
        //pthread_join( tid, NULL );

        time = accessTimer( LAP_TIMER, timePtr );
        sprintf( tempOutput->toPrint,
                  "Time: %f, Process %d, %s operation end\n",
                  time, counter, metaNode->operation  );
        output = addFPNode( output, tempOutput );
    }
    else
    {
        strcpy( tempOutput->toPrint, "Error\n");
        output = addFPNode( output, tempOutput );
    }



}

void fileOutput( struct file_printStorage * output, char * fileName )
{
    FILE *filePointer = NULL;
    filePointer = fopen( fileName, "w" );
    char temp[ MAX_STR_LEN ];

    while( output != NULL )
    {
        strcpy( temp, output->toPrint );
        fprintf( filePointer, "%s", temp );
        output = output->next;
    }

    fclose( filePointer );

}

void printOutput( struct file_printStorage * output )
{
    char temp[ MAX_STR_LEN ];

    while( output != NULL )
    {
        strcpy( temp, output->toPrint );
        printf( "%s", temp );
        output = output->next;
    }
}

int handleMemory( struct MetaNodeType * metaNode,
                  struct ConfigNodeType * configNode, char * memory,
                   struct memory_manager * memManager,int counter )
{
    struct memory_manager *tempMem = ( struct memory_manager * )malloc(
                                       sizeof( struct memory_manager ) );
    struct memory_manager *searchedMem = ( struct memory_manager * )malloc(
                                       sizeof( struct memory_manager ) );
    struct ConfigNodeType *tempConfig = ( struct ConfigNodeType * )malloc(
                                       sizeof( struct ConfigNodeType ) );
    char *mem = ( char * )malloc( sizeof( char ) * MAX_STR_LEN );
    char seg[3];
    char base[4];
    char memRequest[4];
    int i, segInt, intBase, intMemReq = 0;
   // Boolean allotted = True;
    mem = intToString( metaNode->cycleTime, mem, 10 );

    tempConfig = findConfigNodeByName( configNode, "Memory Available (KB)" );

    while(i < 7)
    {
        if(i < 2)
        {
            seg[i] = mem[i];
        }
        else if(i >= 2 && i < 5 )
        {
            base[i - 2] = mem[i];
        }
        else if( i >= 5 )
        {
            memRequest[i - 5] = mem[i];
        }
        i++;
    }
    seg[3] = '\0';
    base[4] = '\0';
    memRequest[4] = '\0';

    // Assign variables to temp list
    tempMem->process = counter;
    strcpy( tempMem->segment, seg );
    strcpy( tempMem->base, base );
    strcpy( tempMem->memory, memRequest );

    segInt = stringToInt( seg );
    intBase = stringToInt( base );
    intMemReq = stringToInt( memRequest );

    if( intMemReq - intBase > tempConfig->selectionNum )
    {
        return 1;
    }

    if( strcmp( metaNode->operation, "allocate" ) == 0 )
    {
        //check if mem is free
        searchedMem = findMMNodeBySeg( memManager, segInt );

        if( searchedMem == NULL )
        {
            memManager = addMMNode( memManager, tempMem );
            return 0;
        }
        else
        {
            return 1; // seg fault
        }

    }
    else if( strcmp( metaNode->operation, "access" ) == 0 )
    {
        // Search for segment.
        searchedMem = findMMNodeBySeg( memManager, segInt );
        if( searchedMem == NULL )
        {
            if( intBase > stringToInt( searchedMem->base )
                 && intMemReq < stringToInt( searchedMem->memory ) )
            {
                 return 0; //success
            }
            return 1;
        }
        else
        {
            return 1; // seg fault
        }
    }
    else
    {
        return 1; // seg fault
    }

    return 1;

}
