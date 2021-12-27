#include "kernel/types.h"
#include "user/user.h"

void primes(int ppReadInterface)
{
    int prime;
    int otherNum;
    int p[2];
    pipe(p); //Create right neighbour
    if (read(ppReadInterface, &prime, sizeof(int)) != 0)
    {
        fprintf(1, "prime %d\n", prime);
    }
    else
    {
        close(p[0]);
        close(p[1]);
        close(ppReadInterface);
        exit(0);
    }
    int pid = fork();
    if (pid==0)
    {
        /* child process */
        close(ppReadInterface);
        close(p[1]);
        primes(p[0]);
    }
    else if (pid > 0)
    {
        // parent process
        close(p[0]);
        while(read(ppReadInterface,&otherNum,sizeof(int))!=0){
            if (otherNum%prime!=0)
            {
                write(p[1],&otherNum,sizeof(int));
            }
        }
        close(ppReadInterface);
        close(p[1]);
        wait(&pid);
        exit(0);
    }
    else
    {
        fprintf(2,"fork error!\n");
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    int pp[2];
    pipe(pp);
    for (int i = 2; i <= 35; i++)
    {
        write(pp[1], &i, sizeof(int));
    }
    close(pp[1]);

    primes(pp[0]);

    exit(0);
}