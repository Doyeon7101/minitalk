#include "minitalk.h"



int send_signal(int pid, char c)
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

    if (argc != 3)
    {
        ft_printf("invalid argument!");
        return(0);
    }
    else
        send_str(atoi(argv[1]), argv[2]);
    return(1);

}