#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 512

int main(int argc, char* argv[])
{

    int fd[2][2];

    pipe(fd[0]);

    if(fork() == 0)
    {
        pipe(fd[1]);
        if(fork() == 0)
        {
            dup2(fd[1][1],1);
            execlp("ls", "ls", "-l", (char * ) NULL);
            perror("ls");
            exit(1);
        }
        else{
            close(fd[1][1]);
            dup2(fd[1][0], 0);
            dup2(fd[0][1], 1);
            execlp("grep", "grep", "^d", (char * ) NULL);
            perror("grep");
            exit(1);
        }
    }
    else{
        close(fd[0][1]);
        dup2(fd[0][0], 0);
        execlp("more", "more", (char * ) NULL);
        perror("more");
        exit(1);
    }
    exit(0);
}
