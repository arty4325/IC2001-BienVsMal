package org.example;

import javax.mail.MessagingException;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws MessagingException, IOException {
        String message =
                "TEST";

        EnvioCorreos envioCorreos = new EnvioCorreos();
        envioCorreos.createEmail("arturo.acuna.duran@gmail.com", "TEST", message, "C:/Users/artur/Desktop/ITCR/ED/Proyectos/IC2001-BienVsMal/BienVsMal/build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/Archivostxt/bitacoraMuerte.txt");
        envioCorreos.sendEmail();
    }
}