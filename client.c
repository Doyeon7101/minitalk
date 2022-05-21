#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("argc error");
        return(0);
    }
    else
    {
        int pid = atoi(argv[1]);
        int i = 7;
        char c = *argv[2];
        while (i >= 0)
        {
            if (c && c >> i & 1)
                kill(pid, SIGUSR1);
            else if (c)
                kill(pid, SIGUSR2);
            sleep(1);
            i--;
        }
    }
    return(1);

}