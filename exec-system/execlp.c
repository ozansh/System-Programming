#include <stdio.h>
#include <unistd.h>
 
int main(void) {
    // int execlp(const char *file, const char *arg, …, NULL );
    char *programName = "ls";
    char *arg1 = "-lh";
    char *arg2 = "/home";
    
    execlp(programName, programName, arg1, arg2, NULL);
    puts("Hatali");
    return 0;
}