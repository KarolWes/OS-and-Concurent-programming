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
#define SIZE 512

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

    int shmid;
    int sh = 999998;
    int *buf;
    shmid = shmget(sh, SIZE*sizeof(int), IPC_CREAT|0600);
    if(shmid == -1){
        fprintf(stderr, "cannot assign shared memory\n");
        exit(11);
    }
    int semid;
    semid = semget(11112, 2, IPC_CREAT|0600);
    if (semid == -1){
 		exit(2);
	}
	if (semctl(semid, 0, SETVAL, (int)1) == -1){
		exit(3);
	}
	if (semctl(semid, 1, SETVAL, (int)0) == -1){
		exit(4);
	}
    if(fork() == 0){//prod
        int i = 1;
        buf = (int*)shmat(shmid, NULL, 0);
        if (buf == NULL){
            exit(12);
        }
        while(1){
            sleep(3);
            if(semctl(semid, 1, GETVAL) < 100){
                lower(semid, 0);
                printf("Production\n");
                buf[semctl(semid, 1, GETVAL)] = i;
                i+=1;
                reise(semid, 1);
                reise(semid, 0);
            }
        }


    }
    else{//kons
        buf = (int*)shmat(shmid, NULL, 0);
        int id;
        if (buf == NULL){
            exit(12);
        }
        while(1){
            if(semctl(semid, 1, GETVAL) > 0){
                lower(semid, 0);
                id = semctl(semid, 1, GETVAL)-1;
                printf("consume %d\n", buf[id]);
                buf[id] = 0;
                lower(semid, 1);
                reise(semid, 0);
                sleep(2);
            }
        }

    }

    exit(0);
}

