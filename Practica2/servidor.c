#include <stdio.h>
#include <stdlib.h>
#include <string.h>        
#include <arpa/inet.h>     
#include <netinet/in.h>    
#include <unistd.h>        
#include <inttypes.h>      

int socketServidor;
int socketConexion;
struct sockaddr_in direccionSocket;
struct sockaddr_in direccionCliente;

socklen_t tamañoCliente;

uint16_t puerto;
uint16_t puertoared;

char string[1000];

int main() {
 
    puerto = 0x1389; 
    puertoared = htons(puerto); 


    socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServidor < 0) {
        perror("No se pudo crear el socket de Servidor");
        exit(EXIT_FAILURE);
    }


    direccionSocket.sin_family = AF_INET;
    direccionSocket.sin_addr.s_addr = htonl(INADDR_ANY); 
    direccionSocket.sin_port = puertoared; 

    if (bind(socketServidor, (struct sockaddr *) &direccionSocket, sizeof(struct sockaddr_in)) < 0) {
        perror("No se pudo asignar la dirección");
        exit(EXIT_FAILURE);
    }


    if (listen(socketServidor, 1) < 0) {
        perror("Error al escuchar");
        exit(EXIT_FAILURE);
    }
    printf("Servidor escuchando en el puerto %d...\n", ntohs(direccionSocket.sin_port));

    tamañoCliente = sizeof(direccionCliente);
    socketConexion = accept(socketServidor, (struct sockaddr *) &direccionCliente, &tamañoCliente);

    if (socketConexion < 0) {
        perror("Error al intentar aceptar");
        exit(EXIT_FAILURE);
    }

    printf("Conexión aceptada desde %s:%d\n", inet_ntoa(direccionCliente.sin_addr), ntohs(direccionCliente.sin_port));

    strcpy(string, "Hola cliente, conexión establecida.\n"); 
    ssize_t bytes_enviados = send(socketConexion, string, strlen(string), 0);

    if (bytes_enviados < 0) {
        perror("Error al enviar datos");
        exit(EXIT_FAILURE);
    }

    printf("Número de bytes enviados: %zd\n", bytes_enviados);

    close(socketConexion); 
    close(socketServidor);

    return 0;
}
