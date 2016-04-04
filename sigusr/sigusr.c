#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

char* sig_str = NULL;
pid_t sid_sender_id;

void sig_h(int sig, siginfo_t *siginfo, void *context) {
    sig_str = sig == SIGUSR1 ? "SIFUSR1" : "SIGUSR2";
    sid_sender_id = siginfo->si_pid;
}

int main(int argc, char** argv) {
    struct sigaction sa; 
    sa.sa_sigaction = &sig_h;
    sa.sa_flags = SA_SIGINFO;

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    sigaction(SIGUSR1, &sa, NULL); 
    sigaction(SIGUSR2, &sa, NULL);
    
    sleep(10);

    if (sig_str == NULL) printf("No signals were caught\n");
    else printf("%s from %d\n", sig_str, sid_sender_id);

	return 0;
}
