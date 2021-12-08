# FCNTL.H

## EN
**FNCTL.H** is used for system calls which can control input/output. This library includes these system calls:

- int create(char *filename, mode_t mode)
- int open (const char* Path, int flags [, int mode ])
- int close(int fd)
- size_t read (int fd, void* buf, size_t cnt)
- size_t write (int fd, void* buf, size_t cnt)

### OPEN()
open system call is used for opening files from certain Path. This call can be used instead of CREATE call with certain flags. It returns a file descriptor if call works without problem. If call fails, it returns -1

Some Useful Flags:
- O_WRONLY (opens file with read and write permissions)
- O_CREAT (creates a file if specified file doesnt exist)
- O_APPEND (I am not sure but I think with this flag, file descriptor starts at end of file instead of beggining of it)
