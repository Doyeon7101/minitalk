#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
    char c = 0;
void signal_handler(int signum)
{
    int cnt ; 
    cnt = 0;
    if (signum == SIGUSR1)
    {
        c = c << 1 | 1;
        cnt ++;
    }
    if (signum == SIGUSR2)
    {
        c = c << 1;
        cnt ++;
    }
    printf("here = %c\n", c);
}
int main()
{
    printf("server pid : %d\n", getpid());
    signal(SIGUSR1, &signal_handler);
    signal(SIGUSR2, &signal_handler);
    while (1)
    {
        sleep(3);
    }
}