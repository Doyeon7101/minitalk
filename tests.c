#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void signal_handler(int signum, siginfo_t *info, void *(v))
{
    (void)info;
    (void)(v);
    if (signum == SIGUSR1);
    {
        printf("succes recieve\n");
        printf("this is client's si_pid : %d\n", info->si_pid);
        kill(info ->si_pid, SIGUSR1);
    }
}
int main(void)
{
    struct sigaction    signals;

    signals.sa_sigaction = &signal_handler;
    signals.sa_flags = SA_SIGINFO;
    printf("server pid is : %d\n", getpid());
    sigaction(SIGUSR1, &signals, NULL);
    sigaction(SIGUSR2, &signals, NULL); 
    
    while (1)
        pause(); 
    return(1);
}
