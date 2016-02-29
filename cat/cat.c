#include <unistd.h>

#define BUFFER_SIZE 256
#define stdin 0
#define stdout 1

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE];
    int n;

    while ( (n = read(stdin, buffer, BUFFER_SIZE)) > 0) {    
        write(stdout, buffer, n);  
    }
 
    return 0;
}
