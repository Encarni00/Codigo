/*
 *  @(#)ClienteTCP_c.c
 *
 *  Arquitectura de Redes. GIERM.
 *  Departamento de Ingenieria Telematica
 *  Universidad de Sevilla
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#define TAM 256

void error(const char *msg){
    perror(msg);
    exit(1);
}

/**
 * Descripcion: Este codigo contiene la version simple de un cliente para TCP en el lenguaje C.
 *
 * En linea de comandos se debe proporcionar el servidor y el numero de puerto
 * version 1.0 Mayo 2021
 * Arquitectura de Redes
 */
int main ( int argc, char **argv ) {
    char   buffer [ TAM ];
    int                sockfd,         /* Representa el descriptor del socket */
                       numPuerto,      /* Representa el numero de puerto      */
                       n;
    char * servidor = NULL;            /* Servidor al que conectarse          */
    struct sockaddr_in   serv_addr;
    struct hostent     * server;

    if ( argc < 3 ) {
	   numPuerto = 51717;
	   servidor = "localhost";
    } else {
	    servidor =  argv[1];
        numPuerto = atoi(argv[2]);
	}

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( sockfd < 0 ) 
        error("ERROR en la apertura del socket");
        
    server = gethostbyname(servidor);
    if ( server == NULL ) {
        fprintf(stderr,"ERROR en la conexión del host\n");
        return 1;
    }
	
    /*Se pone a 0 la zona de memoria */
    memset ( &serv_addr, 0, sizeof(serv_addr)); 
	
    serv_addr.sin_family = AF_INET;

    strncpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length );

    /*El numero de puerto se pasa de int a 16 bits*/
    serv_addr.sin_port = htons(numPuerto);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("Ejecute el servidor antes que el cliente ...");
    printf("Introduzca el mensaje a enviar: ");

    memset(buffer, 0, 256);
    fgets(buffer,255,stdin);
	
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR en la escritura en el socket");

    memset(buffer, 0, 256);		 
    n = read(sockfd,buffer,255);
    if ( n < 0 ) 
         error("ERROR en lectura del socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
