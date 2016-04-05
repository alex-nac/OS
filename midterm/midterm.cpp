#include <unistd.h>
#include <sstream>
#include <fcntl.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

std::string process_input() {
    char buffer[BUFFER_SIZE];
    ssize_t n; 
    std::string command;

    while ( (n = read(STDIN_FILENO, buffer, BUFFER_SIZE)) != 0)  { 
        if (n == -1) {
            if (errno == EINTR) continue;
            else exit(-1);    
        }

        command.append(buffer, buffer[n - 1] == '\n' ? n - 1 : n);
        if (buffer[n - 1] == '\n') break; // read until '\n'
    }

    return command;
}

// run one program (e.g. cat)
pid_t run_program(std::vector<std::string> const& program, int r_fd, int w_fd) {

    if (pid_t child_pid = fork()) { // parent
       return child_pid;
    }
    else { // child
        dup2(r_fd, STDIN_FILENO);      
        dup2(w_fd, STDOUT_FILENO);

        execvp(program[0].c_str(), (char* const*)program.data());
    }
}

// run command (e.g. cat a.tmp | grep abc). Here we create our pipes
void run_cmd(std::vector<std::vector<std::string>> programs) {
    // keep our returned pid here
    std::vector<int> pids(programs.size());

    int p[2]; 
    
    for (size_t i = 0; i != programs.size(); ++i) {
        int new_p[2];
        if (i != programs.size() - 1) pipe2(new_p, O_CLOEXEC);

        pids[i] = run_program(programs[i], 
                    i == 0 ? STDIN_FILENO : p[0],                           // read fd
                    i == programs.size() - 1 ? STDOUT_FILENO : new_p[1]);   // write fs

        // close old pipe
        if (i != 0) {
            close(p[0]);
            close(p[1]);
        }
        
        // copy new pipe
        p[0] = new_p[0];
        p[1] = new_p[1];
    }


    // wait all process to end
    for (size_t i = 0; i != pids.size(); ++i) {
        //puts("Now im waiting");
        waitpid(pids[i], NULL, 0);   
        //puts("Waiting done");
    }
} 

// pair<program, program_args>
std::vector<std::vector<std::string>> split_into_commands(std::string const& cmd) {
    std::vector<std::vector<std::string>> program_vec;

    std::stringstream cmd_stream(cmd);
    std::string program, arg;

    while (std::getline(cmd_stream, program, '|')) {
        // create empty vec
        program_vec.emplace_back();
        
        // first arg is program itselt
        std::stringstream arg_stream(program);
        while(std::getline(arg_stream, arg, ' ')) {
            if (arg.length() != 0) program_vec.back().push_back(arg);
        }
    }

    return program_vec;
}

int main(int argc, char** argv) {
    //puts("hello im first");
    while (true) {
        write("$");
        itd::string cmd = process_input();
        std::vector<std::vector<std::string>> commands =  split_into_commands(cmd);
   
        run_cmd(commands);
    }

    return 0;
}
