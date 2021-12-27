#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    int n;
    int numArg;
    char *args[MAXARG];
    char buf[32];
    for (int i = 1; i < argc; i++)
    {
        args[i - 1] = argv[i];
        // printf("%s\n", args[i - 1]);
    }
    numArg = argc - 1;
    char *p = buf;
    while ((n = read(0, p, 1)) > 0)
    {
        if (*p == '\n')
        {
            // printf("%s--%d\n", p, n);
            *p = 0; // end
            if (fork() == 0)
            {
                args[numArg] = buf;
                for (int i = 0; i <= numArg; i++)
                // {
                //     printf("%s\n", args[i]);
                // }
                
                exec(args[0], args);
                exit(0);
            }
            else
            {
                wait(0);
            }
            p = buf; // new head
        }
        else
        {
            // printf("%s--%d\n", p, n);
            ++p;
        }
    }
    exit(0);
}

// echo "1\n2" | xargs -n 1 echo line