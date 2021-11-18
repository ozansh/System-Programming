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
        printf("Child : pid1=%i\n",pid1);
        printf("Child : getpid=%i\n", getpid());
        printf("Child : getppid=%i\n", getppid());
        sleep(5);
        printf("Child after sleep: getpid=%i\n", getpid());
        printf("Child after sleep: getppid=%i\n", getppid());
        return EXIT_SUCCESS;
    }
    else
    {
        puts("I am Parent");
        printf("Parent : pid1=%i\n", pid1);
        printf("Parent : getpid=%i\n", getpid());
        printf("Parent : getppid=%i\n", getppid());
        puts("Parent is exiting...");
        exit(0);
    }
}