#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// We include <fcntl.h> to use file control system calls such as OPEN, CREATE

// <fcntl.h> kütüphanesini OPEN CREAT ve READ gibi dosya kontol sistem çağrıları için ekliyoruz

int main(void){
    
    // O_CREAT
    int fd = open("lorem.txt", O_RDONLY);// 0 on success
    // open(path,flags)
    printf("fd = %d\n", fd);

    if (fd == -1){
        printf("There is an error\n");
        return EXIT_FAILURE;
    }

    if( close(fd) < 0)// returns 0 if succesful
    {
        puts("I can't close the file");
    }

    return EXIT_SUCCESS;

}