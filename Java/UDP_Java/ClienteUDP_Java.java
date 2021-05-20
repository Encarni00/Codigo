/*
 *  @(#)ClienteUDP_Java.java
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
 * Descripcion: Este codigo contiene la version simple de un cliente para UDP en Java.
 *
 * En linea de comandos se debe proporcionar el servidor y el numero de puerto.
 * version 1.0 Mayo 2021
 * Arquitectura de Redes
 */
public class ClienteUDP_Java {
    public static void main(String args[]) throws Exception{

		BufferedReader entradaDesdeUsuario = new BufferedReader ( new InputStreamReader (System.in));
		DatagramSocket socketCliente = new DatagramSocket ();		
		
		InetAddress direccionIP = InetAddress.getByName(args[0]);
		int puerto = Integer.parseInt( args[1] /*numero de puerto */);
		
		byte[] enviarDatos  = new byte[1024];
		byte[] recibirDatos = new byte[1024];
		
		String frase = entradaDesdeUsuario.readLine();
		enviarDatos = frase.getBytes();		
		DatagramPacket enviarPaquete = new DatagramPacket (enviarDatos, enviarDatos.length, direccionIP, puerto );
		socketCliente.send(enviarPaquete);
		DatagramPacket recibirPaquete = new DatagramPacket (recibirDatos, recibirDatos.length );
		socketCliente.receive(recibirPaquete);
		String fraseModificada = new String(recibirPaquete.getData());
		System.out.println("DEL SERVIDOR: " + fraseModificada);
		
		socketCliente.close();
	}
}


