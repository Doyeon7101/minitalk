#include "minitalk.h"
void check_success(char c)
{
    if (c == 0)
        ft_printf("SUCCESS!");
    else
    {
        ft_printf("FAIL!");
    }
    exit(1);

}
void signal_handler(int signum)
{
    static char c;
    static int cnt;
    
    cnt = 0;
    if (signum == SIGUSR1 || signum == SIGUSR2)
    {
        c = c << 1;
        if (signum == SIGUSR1)
            c = c | 1;
        cnt++;
    }
    if (cnt == 8)
        check_success(c);
    
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
    struct sigaction signals;

    printf("client pid is : %d\n", getpid());

    signals.sa_sigaction = &signal_handler;
    signal(SIGUSR2, &signals);
    signal(SIGUSR1, &signals);
    if (argc != 3)
    {
        ft_printf("invalid argument!");
        return(0);
    }
    else
        send_str(ft_atoi(argv[1]), argv[2]);
    
    while (1)
        pause();
    return(1);

}