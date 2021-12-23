/********************************************************
 * 
 *
 * A  singlethreaded process (with only the main thread)
 *      
 *       Files: singlethread.c, func1.c, func2.c  
 *
 ********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
 
/* Function declarations */
 void func1(void);
 void func2(void); 

int r1 = 0, r2 = 0; /* Global variables, accessible to functions if necessary */

int 
main(void)
{
  pthread_t       td1, td2; /* Descriptors for two child threads, not used here */
  int p;  /* Not used here */
  int j;
  float delta;
  struct timeval time1, time2;


  printf("Singlethreaded process starts  here...\n");
   gettimeofday(&time1, 0); /* Starting time */

/* Creation of two child threads 
  p = pthread_create(&td1, 
		 NULL,		 
                 (void *)func1,
		 NULL); 

  if (p != 0) {perror("Thread 1 creation problem"); exit(1);}

  p = pthread_create(&td2,
                 NULL,                 
                 (void *)func2,
                 NULL);
  if (p != 0) {perror("Thread 2 creation problem"); exit(1);}
*/ 
          
/* Now the process does something by its main thread */ 
  for (j=1; j<=4; ++j)
    {
    printf("Main  function of the process works: %d\n", j);
    sleep(3); /* Sleep 3 seconds */
    }
   
/* Then the process calls sequentially two functions */
  func1();
  func2();  






/* Determining the total time of running the  process */
   gettimeofday (&time2, 0);
   delta = (float)((1000000*time2.tv_sec + time2.tv_usec) -
                   (1000000*time1.tv_sec + time1.tv_usec))/1000000;
   printf("Total elapsed time = %f seconds\n", delta);

   printf("Main thread terminated...\n");

   return 0; 
}



