#include <unistd.h>
 
int main(void) {

    // int execle(const char *path, const char *arg, ..., NULL, char * const envp[] );

    char *binaryPath = "/bin/bash";
    char *arg1 = "-c";
    char *arg2 = "echo \"Visit $HOSTNAME:$PORT from your browser.\"";
    char *const env[] = {"HOSTNAME=www.linuxhint.com", "PORT=8080", NULL};
    
    execle(binaryPath, binaryPath,arg1, arg2, NULL, env);
    
    return 0;
}