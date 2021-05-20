/*
 *  @(#)ServidorTCP_Java.java
 *
 *  Arquitectura de Redes. GIERM.
 *  Departamento de Ingenieria Telematica
 *  Universidad de Sevilla
 *  
 */


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.DataOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Descripcion: Este codigo contiene la version simple de un servidor para TCP en Java.
 *
 * En linea de comandos se debe proporcionar el numero de puerto.
 * version 1.0 Mayo 2021
 * Arquitectura de Redes
 */
public class ServidorTCP_Java {
    public static void main(String args[]) throws Exception{
		
		String fraseCliente    = null;
		String fraseMayuscula  = null;

		ServerSocket socketAcogida = new ServerSocket(
		                                  Integer.parseInt( args[0] /*numero de puerto */)
										  );
		while ( true ){		
            Socket socketConexion = socketAcogida.accept();
            BufferedReader entradaDesdeCliente = new BufferedReader (new InputStreamReader(socketConexion.getInputStream()));		
		    DataOutputStream  salidaCliente = new DataOutputStream(socketConexion.getOutputStream());	
		    fraseCliente = entradaDesdeCliente.readLine();
		    fraseMayuscula = fraseCliente.toUpperCase() + '\n';
		    salidaCliente.writeBytes(fraseMayuscula);
		}
	}
}


