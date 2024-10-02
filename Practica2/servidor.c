#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> 
#include <inttypes.h>

int socketServidor;
int socketConexion;
struct sockaddr_in direccionSocket;
socklen_t tamañoSocket;

uint16_t puerto;
uint16_t puertoared;

int aceptar;


char string[1000];


int main(){
    puerto=0x175C;//5980
    puertoared=htons(puerto);

    tamañoSocket=sizeof(direccionSocket);

    socketServidor=socket(AF_INET,SOCK_STREAM, 0);
    if (socketServidor < 0){
        perror("No se pudo crear el socket de Servidor");
        exit(EXIT_FAILURE);
    }

    direccionSocket.sin_family=AF_INET;
    direccionSocket.sin_addr.s_addr=htonl(INADDR_ANY);
    direccionSocket.sin_port=puertoared;

    if(bind(socketServidor, (struct sockaddr *) &direccionSocket, sizeof(struct sockaddr_in) ) <0){
        perror ("No se pudo asignar la dirección");
        exit (EXIT_FAILURE);
    }

    if(listen(socketServidor,20)<0){
        perror("Error al escuchar");
        exit(EXIT_FAILURE);
    }

    if(accept(socketServidor, (struct sockaddr *) &direccionSocket, tamañoSocket) <0){
        perror("Error al intentar aceptar");
        exit(EXIT_FAILURE);
    }

    
    




}

