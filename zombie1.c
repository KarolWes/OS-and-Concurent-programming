#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    fprintf(stdout, "Proces\tZombie\n");
    fprintf(stdout, "______\t______\n");
    int pid = fork();
    if(pid == 0)
    {
        sleep(2);
        fprintf(stdout, "%d\t%d\n", getppid(), getpid());
        exit(0);
    }
    else{
        pid = fork();
        if(pid == 0)
        {
            sleep(3);
            fprintf(stdout, "%d\t%d\n", getppid(), getpid());
            exit(0);
        }
    }


    sleep(4);
    wait(NULL);




}
