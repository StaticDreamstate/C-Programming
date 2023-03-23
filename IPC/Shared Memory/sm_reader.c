#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void) {

    // ftok(): geração de chave única para o segmento de memória

    key_t key = ftok("memory", 67);

    // shmget(): retorna um identificador em shmid

    int shmid = shmget(key, 1024, 0666|IPC_CREAT);

    if(shmid == -1) {
        
        puts("Não foi possível se conectar ao segmento de memória.");
        exit(1);

    }

    // shmat(): anexa o segmento de memória à região de memória do processo

    char *str = (char *) shmat(shmid,(void*) 0,0);
    printf("Dados lidos da memória: %s\n", str);

    // shmdt(): desanexa o segmento de memória da região de memória do processo

    shmdt(str);

    // shmctl(): destrói o segmento de memória

    shmctl(shmid,IPC_RMID,NULL);

    return 0;

}
