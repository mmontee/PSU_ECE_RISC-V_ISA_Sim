#ifndef		DEFINES_H_
#define		DEFINES_H_
#include <unistd.h>

#define MAX_SIZE 65536
#define DEFAULT_START_ADDRESS 0 
#define DEFAULT_STACK_ADDRESS 65535   
    
#ifdef DEBUG_ON    
    #define DEBUG
    #define VERBOSE
#endif
   
#endif
