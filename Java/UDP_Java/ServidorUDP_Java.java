/*
 *  @(#)ServidorUDP_Java.java
 *
 *  Arquitectura de Redes. GIERM.
 *  Departamento de Ingenieria Telematica
 *  Universidad de Sevilla
 *  
 */


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.DataOutputStream;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;

/**
 * Descripcion: Este codigo contiene la version simple de un servidor para UDP en Java.
 *
 * En linea de comandos se debe proporcionar el numero de puerto
 * version 1.0 Mayo 2021
 * Arquitectura de Redes
 */
public class ServidorUDP_Java {
    public static void main(String args[]) throws Exception{
    
        int port = Integer.parseInt( args[0] /*numero de puerto */);
		DatagramSocket socketServidor = new DatagramSocket (port);
		byte[] recibirDatos = new byte[1024];		
		byte[] enviarDatos  = new byte[1024];

		while (true) {

   		    DatagramPacket recibirPaquete = new DatagramPacket (recibirDatos, recibirDatos.length);
            socketServidor.receive(recibirPaquete);
		    String frase = new String(recibirPaquete.getData());
		    InetAddress direccionIP = recibirPaquete.getAddress();
            int puerto = recibirPaquete.getPort();
			String fraseMayuscula = frase.toUpperCase();
			enviarDatos = fraseMayuscula.getBytes();
			DatagramPacket enviarPaquete = new DatagramPacket (enviarDatos, enviarDatos.length, direccionIP,puerto);
		    socketServidor.send(enviarPaquete);
		}
	}
}


