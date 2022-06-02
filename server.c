#include "minitalk.h"
int end_of_char(int s_pid, char c)
{
    int i;
    
    i = 8;
    write(1, &c, 1);
    if (c == 0) 
    {
        while (i-- >= 0)
        {
            kill(s_pid, SIGUSR2);
            usleep(500);
        }
    }
    return(0);
}

void signal_handler(int signum, siginfo_t *info, void *(v))
{
    static char c;
    static int cnt;
    static int client_pid;

    (void)v;
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
        cnt = end_of_char(client_pid, c);
        c = 0;
    }
    client_pid = info -> si_pid;
}

int main(void)
{
    struct sigaction    signals;

    signals.sa_sigaction = &signal_handler;
    signals.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &signals, NULL);
    sigaction(SIGUSR2, &signals, NULL);
    ft_printf("server pid is : %d\n", getpid());
    while (1)
        pause(); 
    return(1);
}