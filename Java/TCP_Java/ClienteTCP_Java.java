/*
 *  @(#)ClienteTCP_Java.java
 *
 *  Arquitectura de Redes. GIERM.
 *  Departamento de Ingenieria Telematica
 *  Universidad de Sevilla
 *  
 */


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.DataOutputStream;
import java.net.Socket;


/**
 * Descripcion: Este codigo contiene la version simple de un cliente para TCP en Java.
 *
 * En linea de comandos se debe proporcionar el servidor y el numero de puerto
 * version 1.0 Mayo 2021
 * Arquitectura de Redes
 */
public class ClienteTCP_Java {
    public static void main(String args[]) throws Exception{
		String frase           = null;
		String fraseModificada = null;

		BufferedReader entradaDesdeUsuario = new BufferedReader ( new InputStreamReader (System.in));
		Socket socketCliente = new Socket(args[0] /*nombre del host */,
		                                  Integer.parseInt( args[1] /*numero de puerto */)
										  );
		DataOutputStream  salidaAServidor = new DataOutputStream(socketCliente.getOutputStream());	
        BufferedReader entradaDesdeServidor = new BufferedReader (new InputStreamReader(socketCliente.getInputStream()));		
		frase = entradaDesdeUsuario.readLine();
		salidaAServidor.writeBytes(frase + "\n");
		fraseModificada = entradaDesdeServidor.readLine();
		System.out.println("DEL SERVIDOR: " + fraseModificada);		
		socketCliente.close();
	}
}


