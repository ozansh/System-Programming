#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef char *string;

int main(void){
    
    int fd ,sz;
    string c = (string) calloc(100, sizeof(char));
    fd = open("lorem.txt", O_RDONLY);

    if(fd < 0){return EXIT_FAILURE;}

    sz = read(fd, c, 20);

    if (sz < 0){return EXIT_FAILURE;}
    printf("called read(% d, c, 10). returned that"
        " %d bytes were read.\n", fd, sz); 
    
    // https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
}