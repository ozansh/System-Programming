#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    // int execl(const char *path, const char *arg, ..., NULL);
    char *programname = "/bin/ls";
    char *arg1 = "-lh";
    char *arg2 = "/mnt/c/Users/spaceSpaghetty/OneDrive/DriveHub/c_c++/unix_examples";
        
    execl(programname, arg1, arg2);
    printf("Ending-----");
      
    return 0;
}