#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void signal_handler(int signum, siginfo_t *info, void*(v))
{
    (void)info;
    (void)(v);
    if (signum == SIGUSR1);
    {
        printf("succes recieve\n");
        printf("this is server's si_pid : %d\n", info->si_pid);
    }
}
int main(int argc, char **argv)
{
    struct sigaction signals;

    signals.sa_sigaction = &signal_handler;
    sigaction(SIGUSR1, &signals, NULL);
    printf("client pid is : %d\n", getpid());
    if (argc != 3)
    {
        printf("invalid argument!");
        return(0);
    }
    else
        kill(1591, SIGUSR1);
    
    while (1)
        pause();
    return(1);

}