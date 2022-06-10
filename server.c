#include "minitalk.h"

struct sigaction server_signals;

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

void hdr_print_signal(int signum, siginfo_t *info, void *(v))
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

void hdr_check_connection(int signum, siginfo_t *info, void *(v))
{
    (void)v;
    if (signum == SIGUSR1)
    {
        printf("init\n");
        server_signals.sa_sigaction = hdr_print_signal;
        sigaction(SIGUSR1, &server_signals, NULL);
        sigaction(SIGUSR2, &server_signals, NULL);
        kill(info->si_pid, SIGUSR1);
    }
}

int main(void)
{
    ft_printf("server pid is : %d\n", getpid());
    server_signals.sa_sigaction = hdr_check_connection;
    server_signals.sa_flags = SA_SIGINFO;
    sigemptyset(&server_signals.sa_mask);
    sigaction(SIGUSR1, &server_signals, NULL);
    sigaction(SIGUSR2, &server_signals, NULL);
    while (1)
        pause(); 
    return(1);
}
