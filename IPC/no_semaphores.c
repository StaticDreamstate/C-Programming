
/*
    * Este código apresenta um exemplo simples que acessa dados globais sem um 
    * semáforo usando vários threads e mostra como isso leva à inconsistência 
    * nos dados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Variáveis globais

int a = 5, b = 7;

// change_two(): acesso aos dados globais

void* change_two(void* arg) {
    
    a += 3;
    b -= 1;

    printf("O valor de a agor é %d, e o valor de b agora %d\n", a,b);
    
    sleep(1);
    exit(0);

}

int main(void) {

    // Instâncias de threads

    pthread_t t1,t2,t3;

    pthread_create(&t1, NULL, change_two, NULL);
    pthread_create(&t2, NULL, change_two, NULL);
    pthread_create(&t3, NULL, change_two, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_exit(&t1);
    pthread_exit(&t2);
    pthread_exit(&t3);

    return 0;

}

/* 
    * A função change_two() atua como uma seção crítica. Três threads estão tentando acessar os dados globais de a e b. 
    * Como não há mecanismo de bloqueio adequado para dados globais, isso leva a race conditions e resultados inconsistentes.
*/
