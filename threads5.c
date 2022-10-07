#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 512


pthread_cond_t c1;
pthread_cond_t c2;
pthread_cond_t c_main;

pthread_mutex_t m1;
pthread_mutex_t m2;
pthread_mutex_t m_main;



void *Ping(int *n){
    int i = 0;

    while(i < *n){
        pthread_mutex_trylock(&m1);
        pthread_cond_wait(&c1, &m1);
        printf("Ping\n");
        pthread_mutex_unlock(&m1);
        i++;
        pthread_cond_signal(&c1);
    }
    return;
}
void *Pong(int *n){
    int i = 0;
    pthread_cond_signal(&c1);
    while(i < *n){
        pthread_mutex_trylock(&m1);
        pthread_cond_wait(&c1, &m1);
        printf("Pong\n");
        pthread_mutex_unlock(&m1);
        i++;
        pthread_cond_signal(&c1);
    }
    pthread_cond_signal(&c_main);
    return;
}


int main(int argc, char* argv[]){
    if(argc < 2){
        printf("To few parameters\n");
        exit(2);
    }
    else{
        int n = atoi(argv[1]);
        int err;


        pthread_cond_init(&c1, NULL);
        pthread_cond_init(&c2, NULL);
        pthread_cond_init(&c_main, NULL);

        pthread_t threadPing;
        pthread_t threadPong;

        err = pthread_create(&threadPing, NULL, Ping,&n);
        err = pthread_create(&threadPong, NULL, Pong,&n);

        pthread_mutex_lock(&m_main);
        pthread_cond_wait(&c_main, &m_main);
        pthread_mutex_unlock(&m_main);
        printf("Tennis!\n");

    }

    exit(0);
}
