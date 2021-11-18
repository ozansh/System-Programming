#include <unistd.h>
 
int main(void) {
    // int execvp(const char *file, char *const argv[]);
    char *binaryPath = "/bin/ls";
    char *args[] = {binaryPath, "-lh", "/home", NULL};
    
    execv(binaryPath, args);
    
    return 0;
}