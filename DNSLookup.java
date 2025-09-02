import java.net.InetAddress;
import java.net.UnknownHostException;

public class DNSLookup {
    public static void main(String args[]) {
        if (args.length != 1) {
            System.err.println("Enter a valid domain name or IP address.");
            System.exit(-1);
        }
        
        try {
            String input = args[0];
            System.out.println("Your Input: " + input);
            
            InetAddress inetAddress;
            if (Character.isDigit(input.charAt(0))) {
                byte[] b = new byte[4];
                String[] bytes = input.split("\\.");
                for (int i = 0; i < bytes.length; i++) {
                    b[i] = (byte) Integer.parseInt(bytes[i]);
                }
                inetAddress = InetAddress.getByAddress(b);
            } else {
                inetAddress = InetAddress.getByName(input);
            }
            
            // Output only once with both host and IP address
            System.out.println("Output: " + inetAddress.getHostName() + " ---OR--- " + inetAddress.getHostAddress());
        } catch (UnknownHostException exception) {
            System.err.println("Error: No Internet Address found");
        }
    }
}
