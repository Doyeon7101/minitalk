#include "minitalk.h"
void signal_handler(int signum, siginfo_t *info, void *(v))
{
    static char c;
    static int cnt;
    static int server_pid;
    
    (void)v;
    if ((server_pid!= info->si_pid && cnt !=0))
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
        if (c == 0)
        {
            ft_printf("MESSAGE SENT SUCCESSFULLY\n");
            exit(0);

        }
    }
    server_pid = info -> si_pid;
    
}
void send_signal(int pid, char c)
{
    int i; 

    i = 8;
    while (--i >= 0)
    {
        if (c && c >> i & 1)
        {
            if (kill(pid, SIGUSR1) == -1)
                exit(1);
        
        }
        else if (c)
        {
            if (kill(pid, SIGUSR2) == -1)
                exit(1);
        }
        usleep(500);
    }
}

void send_str(int pid, char *str)
{
    char c;
    int i;

    while (*str != '\0')
    {
        c = *str;
        send_signal(pid, c);
        str++;
    }
    if (*str == '\0')
    {
        i = 8;
        while (--i >= 0)
        {
            if (kill(pid, SIGUSR2) == -1)
                exit(1);
            usleep(500);
        }
    }
}

int main(int argc, char **argv)
{
    int server_pid;
    struct sigaction signals;

    server_pid = ft_atoi(argv[1]);
    signals.sa_sigaction = &signal_handler;
    signals.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2, &signals, NULL);
    if (argc != 3)
    {
        ft_printf("INVALID ARGUMENT!");
        return(0);
    }
    if (server_pid < 101 || server_pid > 99999)
    {
        ft_printf("INVALID PID!");
        return(0);
    }
    send_str(ft_atoi(argv[1]), argv[2]);
    while (1)
        pause();
    return(1);
}