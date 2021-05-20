/*
 *  @(#)ServidorUDP_c.c
 *
 *  Arquitectura de Redes. GIERM.
 *  Departamento de Ingenieria Telematica
 *  Universidad de Sevilla
 *  
 */


#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
/* 
 * Es un servidor simple usando UDP.
 * 
 * El numero de puerto se proporciona como argumento en linea de comandos.
 * El servidor se ejecuta en bucle infinito.  
 *
 * version 1.0 Mayo 2021
 * Arquitectura de Redes
 * 
 */
int main ( int argc, char *argv[] )
{
   int sock, length, n;
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[1024];

   if (argc < 2) {
      fprintf(stderr, "ERROR, no se proporcona puerto\n");
      exit(0);
   }
   
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("Abriendo socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(atoi(argv[1]));
   if (bind(sock,(struct sockaddr *)&server,length)<0) 
       error("binding");
   fromlen = sizeof(struct sockaddr_in);
   while (1) {
       n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
       if (n < 0) error("recvfrom");
       write(1,"Recibido un datagrama: ",23);
       write(1,buf,n);
       n = sendto(sock,"Por el mensaje\n",17, 0,(struct sockaddr *)&from,fromlen);
       if (n  < 0) 
	      error("sendto");
   }
   return 0;
 }

