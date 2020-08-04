package clabinfoe;
import java.io.*;
import java.util.Properties;
import java.net.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.mail.PasswordAuthentication;
public class SendEMailTo {
    public static int Main( String OwnerMail, 
                            String Password,
                            String RemoteEmail,
                            String Subject,
                            String Message2EMail,
                            Properties prop
                            ) throws UnknownHostException, IOException{
        final String AddressMail;
        final String MailPassword;
        AddressMail = OwnerMail.intern();
        MailPassword = Password.intern();
        Properties props = prop;
        props.put("mail.smtp.host", "smtp.gmail.com");
        props.put("mail.smtp.socketFactory.port", "465");
        props.put("mail.smtp.socketFactory.class", "javax.net.ssl.SSLSocketFactory");
        props.put("mail.smtp.auth", "true");
        props.put("mail.smtp.port", "465");
	Session session = Session.getDefaultInstance( props, new javax.mail.Authenticator() {
                            @Override
                            protected PasswordAuthentication getPasswordAuthentication() {
					return new PasswordAuthentication( AddressMail, MailPassword);}
			});
	try {
            Message message = new MimeMessage(session);
            message.setFrom(new InternetAddress("ns1.etb.net.co"));   ////
            message.setRecipients(Message.RecipientType.TO,
            InternetAddress.parse(RemoteEmail));
            message.setSubject(Subject);
            message.setText(Message2EMail);
            Transport.send(message);
	} catch (MessagingException ex) {
            System.out.println( ex.getMessage() );
            // Logger.getLogger(SendEMailTo.class.getName()).log(Level.SEVERE, null, ex);
            // UDPMNG.SendDatas( "Error: " + e.getMessage().substring( 0, 15), LocalPort, RemotePort );
            System.exit( -2 );
            return (-1);
	}
       return 0;
}
}