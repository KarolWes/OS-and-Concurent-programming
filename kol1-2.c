#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    printf("Proces\tRodzic\n");
    printf("------\t------\n");
    int pid = fork();
    if(pid == 0){
        int new_pid = fork();
        if(new_pid == 0){
            printf("%d\t%d\n", getpid(), getppid());
            sleep(2);
	    printf("__________________\n");
            printf("%d\t%d\n", getpid(), getppid());
            sleep(2);
	    printf("__________________\n");
            printf("%d\t%d\n", getpid(), getppid());
            exit(1);
        }
        printf("%d\t%d\n", getpid(), getppid());
        sleep(2);
        printf("%d\t%d\n", getpid(), getppid());
        exit(0);
    }
    sleep(1);
    exit(0);
}
