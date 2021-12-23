/********************************************************
 * 
 *
 *  A simple function that periodically prints
 *              and sleeps 
 *     
 *
 ********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
 


void func1(void)
{
  int i;
  
  for (i = 1; i <10; ++i)   
    {
    printf("Function func1 prints and then sleeps 4 s: %d\n", i); 
    sleep(4);
    } 
  return;

}



