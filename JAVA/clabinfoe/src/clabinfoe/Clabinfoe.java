package clabinfoe;

import java.io.IOException;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.mail.Session;

public class Clabinfoe {
    public static void main(String[] args) {
        try {// clab123456789
            final Properties prop = new Properties();
            // TODO code application logic here
            SendEMailTo.Main( "clabinfoe@gmail.com",
                                    "clab123456789", 
                                        "clabinfoe@gmail.com", 
                                            "CLABINFO", 
                                                "Hi owner", 
                                                prop );
        } catch (IOException ex) {
            // Logger.getLogger(Clabinfoe.class.getName()).log(Level.SEVERE, null, ex);
            System.exit( -1 );
        }
        System.out.println( "Ok." );
    }
    
}
