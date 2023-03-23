// Esse código implementa um semáforo e um mutex 
// para obter a sincronização de processos e encadeamentos.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Variáveis globais

sem_t mutex;
int a = 5, b = 7;

// change_two(): acesso aos dados globais

void* change_two(void* arg) {
    
    sem_wait(&mutex);

    a += 3;
    b -= 1;

    printf("O valor de a agor é %d, e o valor de b agora %d\n", a,b);
    
    sleep(1);
    sem_post(&mutex);

}

int main(void) {

    sem_init(&mutex, 0, 1);
    
    // Instâncias de threads
    pthread_t t1,t2,t3;

    pthread_create(&t1, NULL, change_two, NULL);
    sleep(1);
    pthread_create(&t2, NULL, change_two, NULL);
    sleep(1);
    pthread_create(&t3, NULL, change_two, NULL);
    sleep(1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&mutex);

    return 0;

}

