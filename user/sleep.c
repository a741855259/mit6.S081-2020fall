#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(2,"Usage: sleep [microseconds]\n");
        exit(0);
    } 
    int t = atoi(argv[1]);
    sleep(t);
    exit(0);    
}
