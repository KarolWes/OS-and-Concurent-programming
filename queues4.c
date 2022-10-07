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
    int q = 40001;
    srand(time(NULL));
    if(argc < 2){
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }
    else{
        int msgid;
        struct buf_el el;
        msgid = msgget(q, IPC_CREAT|IPC_EXCL|0600);
        if(msgid == -1){
            msgid = msgget(q, IPC_CREAT|0600);
            if(msgid == -1){
                fprintf(stderr, "cannot assign a queue\n");
                exit(10);
            }
        }
        int n = atoi(argv[1]);
        for(int i = 0; i < n; i++){
            int pid = fork();
            if(pid == 0)
            {
                while(1){
                    if(msgrcv(msgid, &el, sizeof(el.val), 0, IPC_NOWAIT) == -1){
                        sleep(1);
                    }
                    else{
                        printf("%ld\t%d\tRCV\n", el.mtype, el.val);
                        el.mtype = getpid();
                        el.val = rand()%899+100;
                        msgsnd(msgid, &el, sizeof(el.val), 0);
                        printf("%ld,\t%d,\tNAD\n", el.mtype, el.val);
                        exit(0);
                    }

                }
            }
        }
        el.mtype = getpid();
        el.val = rand()%899+100;
        msgsnd(msgid, &el, sizeof(el.val), 0);
        printf("%ld,\t%d,\tNAD\n", el.mtype, el.val);
        wait(NULL);
        exit(0);
    }
}
