
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 1024


// Variáveis Globais

int pipefds[2];
int status, pid;
char writemessage[BUFFER_SIZE];
char readmessage[BUFFER_SIZE];

// pipe_operation(): operações de leitura e escrita de dados.

void pipe_operation() {
    
    pid = fork();
    
    // Processo filho para ler os dados.
    
    if(pid == 0) {
        read(pipefds[0], readmessage, sizeof(writemessage));
        printf("Processo filho: Lendo do pipe - A mensagem é: %s", readmessage);
    }

    else { // Processo pai para escrever os dados.
        printf("Processo pai: Escrevendo no pipe - A mensagem é: %s", writemessage);
        write(pipefds[1], writemessage, sizeof(writemessage));
    }

}

int main(void) {
    
    status = pipe(pipefds);

    if(status == -1) {
        puts("Erro ao criar o pipe.");
        return 1;
    }

    printf("Entre com a mensagem a ser escrita no pipe (quit para sair): ");
    fgets(writemessage,BUFFER_SIZE, stdin);

    // Loop de entrada contínua de dados

    while (strcmp(writemessage, "quit\n") != 0) {
        pipe_operation();
        fgets(writemessage,BUFFER_SIZE, stdin);
        kill(pid, SIGKILL);
    }

    close(pipefds[0]);
    close(pipefds[1]);

    return 0;

}
