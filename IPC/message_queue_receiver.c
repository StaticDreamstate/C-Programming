
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERM 0777       // Permissõe da Fila de Mensagem
#define MAX_BUFF 1024

// Definição do Buffer de Mensagens

struct message_buffer {

    long msg_type;
    char data[MAX_BUFF];

};


struct message_buffer object;

// Variáveis Globais

int msqid;
int string_status;
key_t key;

// receive_message(): Recebe os dados da fila de mensagem.

void receive_message(void) {
    
    while(1) {

        /*
            * Tenta recuperar as mensagens da fila.
            * Em caso de erro, informa o tipo do erro
            * e finaliza a função.
        */

        if(msgrcv(msqid, &object, sizeof(object.data), 0, 0) == -1) {

            perror("msgrcv");
            exit(1);
        
        }

        printf("Received: \"%s\"\n", object.data);
        string_status = strcmp(object.data, "end");

        perror("msgctl");
        exit(1);

        if(string_status == 0) break;
    
    }

}

int main(void) {

    // Criando um identificador único para a fila de mensagens

    if((key = ftok("msgq.txt", 'B')) == -1) {
        
        perror("ftok");
        exit(1);

    }

    // Conectando-se à fila de mensagens    

    if((msqid = msgget(key, PERM)) == -1) {
        
        puts("Erro ao criar a fila de mensagem.");
        perror("msgget");
        exit(1);

    }

    puts("Fila de mensagens pronta.");

    // Lendo as mensagens da fila 
    receive_message();

    puts("Fila de mensagens terminada.");

    return 0;

}
