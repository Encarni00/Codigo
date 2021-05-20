/*
 *  @(#)ServidorTCP_c.c
 *
 *  Arquitectura de Redes. GIERM.
 *  Departamento de Ingenieria Telematica
 *  Universidad de Sevilla
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

/* 
 * Descripcion: Este codigo contiene una version simple 
 * de un servidor TCP en el lenguaje C.
 * 
 * El numero de puerto se proporciona como argumento en linea de comandos.
 * Si no se proporciona el primer argumento en linea de comandos, el valor
 * por defecto es 51717.
 *
 * version 1.0 Mayo 2021
 * Arquitectura de Redes
 * 
 */
int main ( int argc, char **argv ) {
     int       numPuerto, 
               sockfd, 
               newsockfd;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, 
	                    cli_addr;
     int n;
     
     /* Asignacion del numero de puerto:
      * Si se proporciona como argumento en linea de comandos se toma el indicado.
      * Si no se asigna por defecto el 51717.
      */
     if (argc < 2) {
         numPuerto = 51717;
     } else {
         numPuerto = atoi(argv[1]);
     }
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if ( sockfd < 0 ) { 
        error("ERROR en la apertura del socket");
	 }	
     memset((void *) &serv_addr, 0, sizeof(serv_addr));	

     serv_addr.sin_family      = AF_INET;
     serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY;
     serv_addr.sin_port        = htons(numPuerto);
     if ( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ) 
              error("ERROR en binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,  (struct sockaddr *) &cli_addr,  &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
		  
     memset(buffer, 0, 256);		  
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR en la lectura del socket");
     printf("Mensaje recibido: %s\n",buffer);
     
     char *envio = "Mensaje recibido: ";
     n = write(newsockfd,envio,strlen (envio));
     n = write(newsockfd,buffer,strlen (buffer));
     
     if (n < 0)
  	     error("ERROR de escritura en el socket");
  	 printf("Cierre de los flujos.\n");    
     close(newsockfd);
     close(sockfd);
     return 0; 
}
