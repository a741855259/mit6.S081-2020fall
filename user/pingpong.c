#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pp[2];
    int cp[2];
    pipe(pp);
    pipe(cp);
    int pid = fork();
    if (pid == 0) //child
    {
        // child传pong
        // 关闭 child的输入、parent的输出
        close(cp[1]);
        close(pp[0]);
        char buf[4];
        // 从child输出
        read(cp[0], buf, 4);
        close(cp[0]);
        fprintf(1,"%d: received ping\n", getpid());
        // 往parent输入
        write(pp[1], "pong", 4);
        close(pp[1]);
        exit(0);
    }
    else if (pid > 0)
    {
        // parent传ping给child
        // 关闭 child的输出、parent的输入
        close(cp[0]);
        close(pp[1]);
        char buf[4];

        // 注意顺序！

        // 向cp[1] 输入（写）
        write(cp[1],"ping",4);
        close(cp[1]);

        // pp[0] 输出（读）
        read(pp[0],buf,4);
        close(pp[0]);
        fprintf(1,"%d: received pong\n",getpid());
        
        // exit(0);     错，要等子进程结束
        wait(&pid);
    }
    else
    {
        // fork error
        fprintf(2,"Fork Error!\n");
        exit(1);
    }
    exit(0);
}
