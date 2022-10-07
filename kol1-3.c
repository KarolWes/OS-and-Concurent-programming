#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid == 0){
        dup2(fd[1], 1);
        execlp("cat", "cat", "/etc/passwd", (char*)NULL);
        exit(0);
    }
    dup2(fd[0], 0);
    execlp("grep", "grep", "root", (char*)NULL);
    exit(0);
}





