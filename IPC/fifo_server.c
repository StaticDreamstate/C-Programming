#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_FILE "/tmp/n4me3dP1p3"
#define MAX_BUFF 1024

// Variáveis globais

int file_descriptor;
char message_buffer[MAX_BUFF];
int read_buffer;

// receive_data(): operação de leitura de dados do cliente

void receive_data(void) {

    file_descriptor = open(FIFO_FILE, O_RDONLY);
    
    if (file_descriptor = -1) { 
        puts("Falha ao abrir o pipe para leitura.");
        exit(1);
    }

    while(1) {
        read_buffer = read(file_descriptor, message_buffer, sizeof(message_buffer));
        message_buffer[read_buffer] = '\0';

        if((int)strlen(message_buffer) == 0) {
            close(file_descriptor);
            break;
        }

        printf("Mensagem recebida: %s\n", message_buffer);
    }

}

int main(void) {

    // Cria o pipe nomeado, se ele não existir.
    mknod(FIFO_FILE, S_IFIFO|0640, 0);
    
    // Função de leitura de dados do pipe.
    receive_data();

    return 0;

}
