#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    exec("echo",argv);
    printf("exec failed\n");
    exit(0);
}
