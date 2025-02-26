#ifndef		DEFINES_H_
#define		DEFINES_H_
#include <unistd.h>

#define MAX_SIZE 64000

#define DEFAULT_START_ADDRESS 0
#define DEFAULT_HEAP_SIZE 256    
#define DEFAULT_STACK_SIZE 256   
    
#ifdef DEBUG_ON    
    #define DEBUG
#endif
   
#endif
