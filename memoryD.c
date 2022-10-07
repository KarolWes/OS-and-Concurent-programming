#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/shm.h>
#define SIZE 10


int main(int argc, char*argv[])
{
    srand(time(NULL));
    int shmid;
    char *buf;
    if (argc < 2){
        fprintf(stderr, "to few arguments\n");
        exit(99);
    }
    shmid = shmget(IPC_PRIVATE, SIZE*sizeof(char), IPC_CREAT|0600);
    if(shmid == -1){
        fprintf(stderr, "cannot assign shared memory\n");
        exit(11);
    }
    buf = (char*)shmat(shmid, NULL, 0);
    if (buf == NULL){
        exit(12);
    }
    for(int i = 0; i < SIZE; i++)
    {
        //buf[i] = rand()%26+'a';
        buf[i] = argv[1][i];
    }
    printf("saved\n");
    if(fork()==0){
        buf = (char*)shmat(shmid, NULL, 0);
        if (buf == NULL){
            exit(12);
        }
        for(int i = 0; i < SIZE; i++){
            printf("%c", buf[i]);
        }
        printf("\n read \n");
        shmdt(buf);
    }

    exit(0);
}
