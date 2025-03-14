#ifndef		DEFINES_H_
#define		DEFINES_H_
#include <unistd.h>

#define MAX_SIZE 65536
#define DEFAULT_START_ADDRESS 0 
#define DEFAULT_STACK_ADDRESS (MAX_SIZE - 1)   
    
#ifdef DEBUG    
    #define VERBOSE
#endif
   
#endif
