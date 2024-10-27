package org.example;

import javax.mail.*;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMultipart;
import java.io.File;
import java.io.IOException;
import java.util.Properties;

public class EnvioCorreos {

    private static String emailFrom = "parqueoscallejeros@gmail.com";
    private static String passwordFrom = "gpfvvxhpztdoldno";
    private String emailTo;
    private String subject;
    private String content;
    private String attachmentPath; // Ruta del archivo adjunto

    private Properties mProperties;
    private Session mSession;
    private MimeMessage mCorreo;

    public EnvioCorreos() {
        initComponents();
        mProperties = new Properties();
    }

    private void initComponents() {
        // Inicialización de propiedades, si es necesario
    }

    public void createEmail(String _emailTo, String _subject, String _content, String _attachmentPath) throws MessagingException, IOException {
        emailTo = _emailTo; // Tengo que poner la informacion, Paso como parametro?
        subject = _subject;
        content = _content;
        attachmentPath = _attachmentPath; // Asigna la ruta del archivo adjunto

        // Protocolo
        mProperties.put("mail.smtp.host", "smtp.gmail.com");
        mProperties.put("mail.smtp.ssl.trust", "smtp.gmail.com");
        mProperties.setProperty("mail.smtp.starttls.enable", "true");
        mProperties.setProperty("mail.smtp.port", "587");
        mProperties.setProperty("mail.smtp.user", emailFrom);
        mProperties.setProperty("mail.smtp.ssl.protocols", "TLSv1.2");
        mProperties.setProperty("mail.smtp.auth", "true");

        mSession = Session.getDefaultInstance(mProperties);
        mCorreo = new MimeMessage(mSession);

        mCorreo.setFrom(new InternetAddress(emailFrom));
        mCorreo.setRecipient(Message.RecipientType.TO, new InternetAddress(emailTo));
        mCorreo.setSubject(subject);

        // Crea el contenido del correo y añade el archivo adjunto
        MimeMultipart multipart = new MimeMultipart();

        // Parte del texto
        MimeBodyPart textPart = new MimeBodyPart();
        textPart.setText(content, "ISO-8859-1", "html");
        multipart.addBodyPart(textPart);

        // Parte del archivo adjunto
        if (attachmentPath != null && !attachmentPath.isEmpty()) {
            MimeBodyPart attachmentPart = new MimeBodyPart();
            File attachmentFile = new File(attachmentPath);
            attachmentPart.attachFile(attachmentFile);
            multipart.addBodyPart(attachmentPart);
        }

        mCorreo.setContent(multipart);
    }

    public void sendEmail() throws MessagingException {
        Transport mTransport = mSession.getTransport("smtp");
        mTransport.connect(emailFrom, passwordFrom);
        mTransport.sendMessage(mCorreo, mCorreo.getRecipients(Message.RecipientType.TO));
        mTransport.close();
    }
}
