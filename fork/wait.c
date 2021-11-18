#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        return EXIT_FAILURE;
    }
    else if (pid1 == 0)
    {
        puts("I am the Child");
               sleep(20);
        return EXIT_SUCCESS;
    }
    else
    {
        puts("I am Parent");
        puts("Parent waiting for child");
        wait(pid1);
        puts("Parent is exiting...");
        return EXIT_SUCCESS;
    }
}