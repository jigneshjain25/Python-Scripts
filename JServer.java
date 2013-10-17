import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
public class JServer {
	static int counter=1;
	public static void main(String[] args) {
		
		try {
			ServerSocket serverSock = new ServerSocket(6900);
			Socket client = serverSock.accept();
			System.out.println("Client Accepted JJ");
			DataInputStream dis = new DataInputStream(new BufferedInputStream(client.getInputStream()));
			
			while(true){
				
				File outputfile = new File("/home/jignesh/mnt/"+Integer.toString(counter)+".jpg");
				DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputfile));
				copy(dis,dos);
				dos.close();
				
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}
	static void copy(DataInputStream dis, DataOutputStream dos){
		
	   try{
		  long fileSize = dis.readLong();
		 // System.out.println(fileSize);
		  byte[] buf = new byte[8192];
		  int n = 0;
		  while( fileSize > 0 && (n = dis.read(buf, 0, (int)Math.min(buf.length, fileSize))) != -1){
			  dos.write(buf,0,n);
			  dos.flush();
			  fileSize -= n;
			}
            
        }catch(Exception e){
        	System.out.println(e);
        }
	   System.out.println("Wrote "+Integer.toString(counter));
	   counter++;
    }
}
