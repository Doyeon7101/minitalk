#include "minitalk.h"

void send_signal(int pid, char c, int flag)
{
    int i; 

    i = 7;
    if (flag == 0)
    {
        while (i >= 0)
        {
            if (c && c >> i & 1)
                kill(pid, SIGUSR1);
            else if (c)
                kill(pid, SIGUSR2);
            usleep(900);
            i--;
        }
    }
    if (flag == 1)
    {
        i = 7;
        while (i >= 0)
        {
            kill(pid, SIGUSR2);
            usleep(900);
            i--;
        }
    }
}

void send_str(int pid, char *str)
{
    char c;
    printf("pid : %d, str : %s", pid, str);

    while (*str != '\0')
    {
        c = *str;
        send_signal(pid, c, 0);
        str++;
    }
    if (*str == '\0')
    {
        send_signal(pid, c, 1);
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("argc error");
        return(0);
    }
    else
        send_str(atoi(argv[1]), argv[2]);
    return(1);

}