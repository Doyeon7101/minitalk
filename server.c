#include "minitalk.h"

void signal_handler(int signum, siginfo_t *info, void *(v))
{
    static char c;
    static int cnt;
    static int client_pid;

    if ((client_pid != info->si_pid && cnt !=0))
    {
        cnt = 0;
        c = 0;
    }
    if (signum == SIGUSR1 || signum == SIGUSR2)
    {
        c = c << 1;
        if (signum == SIGUSR1)
            c = c | 1;
        cnt++;
    }
    if (cnt == 8)
    {
        write(1, &c, 1);
        cnt = 0;
        c = 0;
    }
    client_pid = info -> si_pid;
}

int main(void)
{
    struct sigaction    signals;

    signals.sa_sigaction = &signal_handler;
    ft_printf("server pid is : %d\n", getpid());
    sigaction(SIGUSR1, &signals, NULL);
    sigaction(SIGUSR2, &signals, NULL);
    
    while (1)
        pause(); 
    return(1);
}