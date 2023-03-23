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
int len;
int string_status;
key_t key;

// send_message(): Envia os dados para a fila de mensagem.

void send_message(void) {
    
    while(fgets(object.data, sizeof object.data, stdin) != NULL) {

        // Calcula o tamanho do objeto de dados

        len = strlen(object.data);

        if(object.data[len-1] == '\n')
            object.data[len-1] = '\0';

        // Se a mensagem não puder ser enviada:

        if(msgsnd(msqid, &object, len+1, 0) == -1) {

            perror("msgend");
            exit(1);
        
        }

        // Verificação do status de saída do sender

        string_status = strcmp(object.data, "end");

        if(string_status == 0) break;

    }

    if(msgctl(msqid, IPC_RMID, NULL) == -1) {

        perror("msgctl");
        exit(1);
    
    }

    puts("Fila de mensagem encerrada.");

}

int main(void) {

    system("touch msgq.txt");

    if((key = ftok("msgq.txt", 'B')) == -1) {
        
        perror("ftok");
        exit(1);

    }

    if((msqid = msgget(key, PERM | IPC_CREAT)) == -1) {

        perror("msgget");
        exit(1);

    }

    puts("Fila de mensagens pronta.");
    printf("Envie o seu texto. Digite 'end' para sair: ");
    object.msg_type = 1;

    // Enviando a mensagem para a fila
    send_message();

    system("rm msgq.txt");

    return 0;

}
