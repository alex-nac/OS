#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#define BUFFER_SIZE 256

int main(int argc, char** argv) {
    int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (fd == -1) return -1;

    char buffer[BUFFER_SIZE];
    ssize_t n; 

    while ( (n = read(STDIN_FILENO, buffer, BUFFER_SIZE)) != 0)  { 
        if (n == -1) {
            if (errno == EINTR) {
                printf("EINTR!!!\n");
                continue;
            }
            else return -1;    
        }

        int offset = 0;
        while (offset != n) {
            ssize_t m = write(fd, &buffer[offset], n - offset);
            if (m == -1) {
                if (errno == EINTR) continue;
                else return errno;
            }

            offset += m;
        }  
    } 

    close(fd);
    return 0;
}
