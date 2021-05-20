/*
 *  @(#)ClienteUDP_c.c
 *
 *  Arquitectura de Redes. GIERM.
 *  Departamento de Ingenieria Telematica
 *  Universidad de Sevilla
 *  
 */


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
/**
 * Descripcion: Este codigo contiene la version simple de un cliente para TCP.
 *
 * En linea de comandos se debe proporcionar el servidor y el numero de puerto
 * version 1.0 Mayo 2021
 * Arquitectura de Redes
 */
int main(int argc, char *argv[])
{
   int                sock, n;
   unsigned int       length;
   struct sockaddr_in server, from;
   struct hostent   * hp;
   char   buffer[256];
   
   if (argc != 3) {  
       printf("Para invocarlo: servido puerto.\n");
       return (1);
   }
   sock = socket(AF_INET, SOCK_DGRAM, 0);
   if ( sock < 0 ) 
       error("socket");

   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   if ( hp == 0 )  
       error("Host desconocido.");

   bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
   
   server.sin_port = htons(atoi(argv[2]));
   length = sizeof(struct sockaddr_in);
   printf("Por favor introduzca el mensaje: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   n = sendto(sock,buffer, strlen(buffer),0,(const struct sockaddr *)&server,length);
   if (n < 0) error("Enviando a ...");
   n = recvfrom( sock, buffer, 256, 0, (struct sockaddr *)&from, &length);
   if (n < 0) 
       error("Recibiendo de ...");
   write(1,"Devuelve un ack: ",17);
   write(1,buffer,n);
   close(sock);
   return 0;
}


