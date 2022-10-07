#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <stdlib.h>

struct buf_el{
    long mtype;
    int val;
};


int main(int argc, char* argv[])
{
    int q = 45283;
    printf("Hello\n");
    if(argc < 3){
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }
    else{
        int m = atoi(argv[1]);
        int n = atoi(argv[2]);
        printf("%d\n", m);
        int msgid;
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
        else{
            if(fork() == 0){
                srand(time(NULL));
                for(int i = 0; i < m; i++){
                    el.mtype = rand()%9+1;
                    el.val = rand()%899+100;
                    msgsnd(msgid, &el, sizeof(el.val), 0);
                    printf("%d\t%d\tSND\n", el.val, el.mtype);
                }
            }
            else{
                while(1){
                    if(msgrcv(msgid, &el, sizeof(el.val), n, IPC_NOWAIT) == -1){
                        exit(20);
                    }
                    printf("%d\t%d\tRCV\n", el.val, el.mtype);
                }
            }
        }
    }
    exit(0);
}
