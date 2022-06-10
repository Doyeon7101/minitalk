#include "minitalk.h"

struct sigaction client_signals;

void hdr_last_signal(int signum, siginfo_t *info, void *(v))
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

void hdr_check_signal(int signum, siginfo_t *info, void *(v))
{
    (void)v;
    (void)info;
    if (signum == SIGUSR1)
    {
        client_signals.sa_sigaction = hdr_last_signal;
        sigaction(SIGUSR1, &client_signals, NULL);
        sigaction(SIGUSR2, &client_signals, NULL);
    }
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

void check_connection(int server_pid)
{
    if (kill(server_pid, SIGUSR1) == -1)
        exit(1);
    pause();
}

int main(int argc, char **argv)
{
    int server_pid;

    server_pid = ft_atoi(argv[1]);
    client_signals.sa_flags = SA_SIGINFO;
    client_signals.sa_sigaction = hdr_check_signal;
    sigemptyset(&client_signals.sa_mask); //sa_mask : 시그널을 처리할 동안 블록시킬 시그널을 모아놓은 변수. 
    sigaction(SIGUSR1, &client_signals, NULL);
    sigaction(SIGUSR2, &client_signals, NULL);
    if (argc != 3)
    {
        ft_printf("INVALID ARGUMENT!");
        return(0);
    }
    check_connection(server_pid);
    send_str(server_pid, argv[2]);
    return(1);
}