import java.io.*;
import java.net.*;

public class Server
{
	public static void main(String args[])
	{
		try{
		ServerSocket ss= new ServerSocket(1234);
		Socket s= ss.accept();
		DataInputStream din = new DataInputStream(s.getInputStream());
		DataOutputStream dout= new DataOutputStream(s.getOutputStream());
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		String str=" ",str2=" ";
		while(!str.equals("Bye"))
		{
			str2=din.readUTF();
			System.out.println("Client Says: "+str2);
			str=br.readLine();
			dout.writeUTF(str);
			
		}
		s.close();
		}
		catch(Exception e)
		{
			System.out.println("Error");
		}
		
	}
}
