#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/shm.h>
#define SIZE 128

struct buf_el{
    long mtype;
    int val;
};

int smaller(int* a, int* b){
    if(*a < *b) return -1;
    else if (*a > *b) return 1;
    else return 0;

}
int greater(int* a, int* b){
    if(*a < *b) return 1;
    else if (*a > *b) return -1;
    else return 0;
}

int main(int argc, char*argv[])
{
    srand(time(NULL));
    int msgid;
    int shmid;
    int *buf;
    int q = 11112;
    int sh = 999998;
    struct buf_el el;
    msgctl(q, IPC_RMID, NULL);
    msgid = msgget(q, IPC_CREAT|IPC_EXCL|0600);
    if(msgid == -1){
        msgctl(q, IPC_RMID, NULL);
        msgid = msgget(q, IPC_CREAT|0600);
        if(msgid == -1){
            fprintf(stderr, "cannot assign a queue\n");
            exit(10);
        }
    }
    shmid = shmget(sh, SIZE*sizeof(int), IPC_CREAT|0600);
    if(shmid == -1){
        fprintf(stderr, "cannot assign shared memory\n");
        exit(11);
    }
    if(fork() == 0){
        buf = (int*)shmat(shmid, NULL, 0);
        if (buf == NULL){
            exit(12);
        }
        for(int i = 0; i < 128; i++){
            buf[i] = rand()%150;
        }
        el.mtype = rand()%3+1;
        el.val = 0;
        msgsnd(msgid, &el, sizeof(el.val), NULL);
    }
    else{
        msgrcv(msgid, &el, sizeof(el.val),0, NULL);
        buf = (int*)shmat(shmid, NULL, 0);
        if (buf == NULL){
            exit(12);
        }
        printf("type: %ld\n", el.mtype);
        switch(el.mtype){
            case 1:
                qsort(buf, SIZE, sizeof (*buf), smaller);
                break;
            case 2:
                qsort(buf, SIZE, sizeof (*buf), greater);
                break;
            default:
                break;
        }
        for(int i = 0; i < SIZE; i++)
        {
            printf("%d\t", buf[i]);
        }
        printf("\n");
        shmdt(buf);
        exit(0);


    }
    exit(0);
}
