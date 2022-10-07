#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	fprintf(stdout, "Proces\tSierota\n");
    fprintf(stdout, "______\t______\n");
    int pid = fork();
    if(pid == 0)
    {
        fprintf(stdout, "%d\t%d\n", getpid(), getppid());
        sleep(5);
        fprintf(stdout, "%d\t%d\n", getpid(), getppid());
    }

    sleep(3);
    exit(0);
}
