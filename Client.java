import java.io.*;
import java.net.*;

public class Client
{
	public static void main(String args[])
	{
		try{
		Socket s= new Socket("127.0.0.1",1234);
		DataInputStream din = new DataInputStream(s.getInputStream());
		DataOutputStream dout= new DataOutputStream(s.getOutputStream());
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		String str=" ",str2=" ";
		while(!str.equals("Bye"))
		{
			str=br.readLine();
			dout.writeUTF(str);
			str2=din.readUTF();
			System.out.println("Server Says: "+str2);
			
		}
		s.close();
		}
		catch(Exception e)
		{
			System.out.println("Error");
		}
	}
}
