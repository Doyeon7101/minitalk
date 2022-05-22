#include "minitalk.h"
char *str;
int cnt;

void signal_handler(int signum)
{
    char c;
    if (signum == SIGUSR1)
    {
        c = c << 1 | 1;
        cnt++;
    }
    if (signum == SIGUSR2)
    {
        c = c << 1;
        cnt++;
    }
    if (cnt == 8)
    {
        cnt = 0;
        write(1, &c, 1);
        if (c == '\0')
        {
            c ='\n';
            write(1, &c, 1);
            str = 0;
        }
        c = 0;
    }
}

int main()
{
    pid_t   pid;
    
    printf("server pid is : %d\n", getpid());
    signal(SIGUSR1, &signal_handler);
    signal(SIGUSR2, &signal_handler);
    while (1)
        pause(); 
}