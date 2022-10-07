#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 512

int main(int argc, char* argv[])
{


    int fd[4][2];
    pipe(fd[0]);
    int pid = fork();
    if(pid == 0)
    {
        pipe(fd[1]);
        pid = fork();
        if(pid == 0){
            pipe(fd[2]);
            pid = fork();
            if(pid == 0)
            {
                pipe(fd[3]);
                pid = fork();
                if(pid == 0){
                    dup2(fd[3][1], 1);
                    execlp("cat","cat", "//home/student/.bash_history", (char * ) NULL);
                    //execlp("bash","bash", "-c", "history", (char * ) NULL);
                    perror("history");
                    exit(1);
                }
                else{
                    close(fd[3][1]);
                    dup2(fd[2][1], 1);
                    dup2(fd[3][0], 0);
                    execlp("cut", "cut", "-c7-", (char *) NULL);
                    perror("cut");
                    exit(1);
                }
            }
            else{
                close(fd[2][1]);
                dup2(fd[1][1], 1);
                dup2(fd[2][0], 0);
                execlp("tail", "tail", "-30", (char *)NULL);
                perror("tail");
                exit(1);
            }

        }
        else{
            close(fd[1][1]);
            dup2(fd[0][1], 1);
            dup2(fd[1][0], 0);
            execlp("sort", "sort", (char *)NULL);
            perror("sort");
            exit(1);
        }

    }
    else{
        close(fd[0][1]);
        dup2(fd[0][0], 0);
        execlp("uniq", "uniq", (char *)NULL);
        perror("uniq");
        exit(1);
    }
    exit(0);
}

