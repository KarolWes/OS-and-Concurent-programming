#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    fprintf(stdout, "Proces\tPotomek\n");
    fprintf(stdout, "______\t_______\n");
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
                sleep(5);

            }
            sleep(4);
        }
        sleep(3);
    }
    else{
        pid = fork();
        if(pid == 0)
        {
            pid = fork();
            sleep(6);
        }


    }
    pid = wait(NULL);
    int pid2 = getpid();
    fprintf(stdout, "%d\t", getppid());
    fprintf(stdout, "%d\n", getpid());
    pid = wait(NULL);

     exit(0);
}

