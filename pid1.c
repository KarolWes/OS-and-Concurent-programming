#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    fprintf(stdout, "Proces\tRodzic\n");
    fprintf(stdout, "______\t______\n");
    int pid = fork();
    if(pid == 0)
    {
        pid = fork();
        if(pid != 0)
        {
            pid = fork();
            if(pid != 0)
            {
                pid = fork();

            }
        }
    }
    else{
        pid = fork();
        if(pid == 0)
        {
            pid = fork();
        }
    }

    int pid2 = getpid();
    fprintf(stdout, "%d\t", pid2);
    if(pid2 != 0)
    {
        fprintf(stdout, "%d", getppid());
    }
    fprintf(stdout, "\n");
    wait(NULL);
     exit(0);
}
