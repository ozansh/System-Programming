#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    char *programname = "ls";
    char *arg1 = "-lh";
    char *arg2 = "/mnt/c/Users/spaceSpaghetty/OneDrive/DriveHub/c_c++/unix_examples";
        
    execl(programname, arg1, arg2);
    printf("Hata Olustu\n");
      
    return 0;
}