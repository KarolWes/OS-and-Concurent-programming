#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 512


pthread_cond_t c1; // pełny
pthread_cond_t c2; // pusty
pthread_cond_t c_main;

pthread_mutex_t m1;
pthread_mutex_t m_main;

int bufor = 0;
int bufor_size = 10;



void *Producent(){

    while(1){
        if(bufor < bufor_size){
            bufor ++;
            printf("Produce: %d\n", bufor);
            pthread_cond_signal(&c2);
        }
        else{
            pthread_cond_signal(&c2);
            pthread_mutex_trylock(&m1);
            pthread_cond_wait(&c1, &m1);
            pthread_mutex_unlock(&m1);
        }

    }
    return;
}
void *Konsument(int *n){
    pthread_cond_signal(&c1);
    while(1){
        if(bufor > 0){
            bufor --;
            printf("buy: %d\n", bufor);
            pthread_cond_signal(&c1);
        }
        else{
            pthread_cond_signal(&c1);
            pthread_mutex_trylock(&m1);
            pthread_cond_wait(&c2, &m1);
            pthread_mutex_unlock(&m1);
        }

    }
    return;
}


int main(int argc, char* argv[]){
        int err;


        pthread_cond_init(&c1, NULL);
        pthread_cond_init(&c2, NULL);
        pthread_cond_init(&c_main, NULL);

        pthread_t threadPing;
        pthread_t threadPong;

        err = pthread_create(&threadPing, NULL, Producent,NULL);
        err = pthread_create(&threadPong, NULL, Konsument,NULL);

        pthread_mutex_lock(&m_main);
        pthread_cond_wait(&c_main, &m_main);
        pthread_mutex_unlock(&m_main);

    exit(0);
}

