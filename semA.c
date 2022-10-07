#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/sem.h>
#define SIZE 128

struct buf_el{
    long mtype;
    int val;
};
static struct sembuf buf;

void reise(int semid, int semnum){
	buf.sem_num = semnum;
 	buf.sem_op = 1;
	buf.sem_flg = 0;
	if (semop(semid, &buf, 1) == -1){
 		perror("Podnoszenie semafora");
		exit(1);
	}
}

void lower(int semid, int semnum){
    buf.sem_num = semnum;
	buf.sem_op = -1;
	buf.sem_flg = 0;
 	if (semop(semid, &buf, 1) == -1){
		perror("Opuszczenie semafora");
		exit(1);
 	}
}

int main(int argc, char* argv[]){

    int n;
    int semid;
    semid = semget(11111, 1, IPC_CREAT|0600);
    if (semid == -1){
 		exit(2);
	}
	if (semctl(semid, 0, SETVAL, (int)1) == -1){
		exit(3);
	}
    if(argc < 2){
        exit(10);
    }
    n = atoi(argv[1]);
    if(fork() == 0){
        for(int i = 0; i < n; i++){
            lower(semid, 0);
            printf("Process 1 in critical section (%d)\n", i);
            reise(semid, 0);
            printf("Process 1 leaves critical section (%d)\n", i);
        }

    }
    else{
        for(int i = 0; i< n; i++){
            lower(semid, 0);
            printf("Process 2 in critical section (%d)\n", i);
            reise(semid, 0);
            printf("Process 2 leaves critical section (%d)\n", i);
        }
    }


    exit(0);
}
