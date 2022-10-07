#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char* vowels = "AaEeIiOoUu";

struct buf_in{
    long mtype;
    char val[64];
};

struct buf_out{
    long mtype;
    int val;
};

int in(char l){
    for(int i = 0; i < 10; i+=1)
    {
        if(l == vowels[i]){
            return 1;
        }
    }
    return 0;
}

int counter(char word[])
{
    int len = strnlen(word, 100);
    printf("%d\n", len);
    int res = 0;
    for(int i = 0; i < len; i+=1){
        printf("%c\n", word[i]);
        if(in(word[i])){
            res+=1;
        }
    }
    printf("res %d\n", res);
    return res;
}

int main(int argc, char* argv[])
{
    int q = 11222;
    int msgid;
    struct buf_in el;
    struct buf_out el_out;
    msgid = msgget(q, IPC_CREAT|IPC_EXCL|0600);
    if(msgid == -1){
        msgid = msgget(q, IPC_CREAT|0600);
        if(msgid == -1){
            fprintf(stderr, "cannot assign a queue\n");
            exit(10);
        }
    }
    else{
        int i = 0;
        if(fork() == 0){
            while(1){
                int mpid = getpid();
                el.mtype = mpid-1;
                char word[] = "ABCDEFGAEBS0";
                strcpy(el.val, word);
                printf("size: %ld\n", sizeof(char)*strlen(word));
                msgsnd(msgid, &el, sizeof(char)*strlen(word), 0);
                printf("SND: %s\n", el.val);
                while(msgrcv(msgid, &el_out, sizeof(el_out.val), mpid, 0) == -1){
                    printf("hello %d\n", i);
                    sleep(1);
                }
                printf("RCV %d\n", el_out.val);
                i = 0;
                exit(1);


            }
        }
        else{
            while(1){
                if(msgrcv(msgid, &el, 64, 0,IPC_NOWAIT|MSG_NOERROR) == -1){
                    printf("sleep\n");
                    sleep(1);
                }
                else{
                    printf("%s\n", el.val);
                    printf("%ld\n", el.mtype);
                    el_out.mtype = el.mtype+1;
                    el_out.val = counter(el.val);
                    printf("%d\n", el_out.val );
                    msgsnd(msgid, &el_out, sizeof(el_out.val), 0);
                    printf("sent\n");
                    exit(7);
                }
            }
        }
    }
    exit(0);
}
