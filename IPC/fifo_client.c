
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
int end_process;
int stringlen;
char message_buffer[MAX_BUFF];
char end_message_buffer[5];

// send_data(): operação de escrita de dados do cliente

void send_data() {

    while(1) {

        fgets(message_buffer, sizeof(message_buffer), stdin);
        stringlen = strlen(message_buffer);
        message_buffer[stringlen-1] = '\0';
        end_process = strcmp(message_buffer, end_message_buffer);

        // Condição de existência do cliente FIFO

        if(strcmp(message_buffer, "end") == 0) {
            puts("O pipe terminou de enviar dados.");
            close(file_descriptor);
            exit(1);
        }

        // Ecoando na saída padrão os dados enviados ao servidor

        if(end_process != 0) {
            write(file_descriptor, message_buffer, strlen(message_buffer));
            printf("Mensagem enviada: %s\n", message_buffer);
        } else {
            write(file_descriptor, message_buffer, strlen(message_buffer));
            printf("Mensagem enviada: %s\n", message_buffer);
            close(file_descriptor);
            break;
        }

   }

}

int main(void) {

    puts("Cliente FIFO está pronto para enviar mensagens ao servidor.");
    printf("Entre com a mensagem. Digite \'end\' para sair: ");

    file_descriptor = open(FIFO_FILE, O_CREAT|O_WRONLY);
    
    // Função de escrita de dados do pipe.
    send_data();

    return 0;

}
