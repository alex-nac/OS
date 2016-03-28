#include <unistd.h>

int main (int argc, char** argv) {
    int p[2];
    pipe(p);
    
    if (!fork()) {
        if (fork()) { // child
            dup2(p[1], STDOUT_FILENO);           // copy write pipe to stdout
            close(p[0]);                         // close read pipe
            close(p[1]);
            execlp("cat", "cat", argv[1], NULL); // run cat
        }
        else { // parent
            dup2(p[0], STDIN_FILENO);             
            close(p[0]);
            close(p[1]);
            execlp("grep", "grep", "int", NULL);
        }
    }

    return 0;
}
