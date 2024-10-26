package org.example;

import javax.mail.MessagingException;
import java.io.*;
import java.net.*;

public class JavaServer {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(12345); // Puerto donde el servidor escucha
            System.out.println("Servidor escuchando en el puerto 12345");

            // Bucle infinito para mantener el servidor escuchando
            while (true) {
                try {
                    Socket clientSocket = serverSocket.accept(); // Aceptar la conexión del cliente
                    System.out.println("Cliente conectado: " + clientSocket.getInetAddress());

                    // Crear un nuevo hilo para manejar la conexión del cliente
                    new Thread(() -> handleClient(clientSocket)).start();
                } catch (IOException e) {
                    System.out.println("Error al aceptar la conexión del cliente: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try {
            // Flujos de entrada y salida
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println("Recibido del cliente: " + inputLine);
                String message = "<html>"
                        + "<head>"
                        + "<style>"
                        + "body { font-family: Arial, sans-serif; background-color: #f4f4f4; padding: 20px; }"
                        + "h1 { color: #333; }"
                        + "p { font-size: 16px; line-height: 1.5; }"
                        + "a { color: #007bff; text-decoration: none; }"
                        + "</style>"
                        + "</head>"
                        + "<body>"
                        + "<h1>Bitácora de Muerte</h1>"
                        + "<p>Estimado usuario,</p>"
                        + "<p>Adjunto a este correo encontrará la <strong>bitácora de muerte</strong> que solicitó.</p>"
                        + "<p>Saludos cordiales,<br>Su equipo de soporte</p>"
                        + "</body>"
                        + "</html>";


                EnvioCorreos envioCorreos = new EnvioCorreos();
                envioCorreos.createEmail(inputLine, "Bitacora de Muerte", message, "C:/Users/artur/Desktop/ITCR/ED/Proyectos/IC2001-BienVsMal/BienVsMal/build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/Archivostxt/bitacoraMuerte.txt");
                envioCorreos.sendEmail();
                out.println("Eco: " + inputLine); // Enviar respuesta al cliente
            }
        } catch (IOException e) {
            System.out.println("Error en la conexión con el cliente: " + e.getMessage());
        } catch (MessagingException e) {
            throw new RuntimeException(e);
        } finally {
            try {
                // Cerrar la conexión del cliente
                clientSocket.close();
            } catch (IOException e) {
                System.out.println("Error al cerrar la conexión del cliente: " + e.getMessage());
            }
        }
    }
}
