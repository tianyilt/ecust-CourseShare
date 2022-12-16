 import java.awt.*;
 import java.awt.event.*;
 import javax.swing.*;
 class windowListener implements WindowListener {
  public void windowClosed(WindowEvent e){  }
  public void windowClosing(WindowEvent e){
	 System.out.println("window closed" );	  
	 System.exit(0);
  }
  public void windowIconified(WindowEvent e){  }
public void windowDeiconified(WindowEvent e){  }
public void windowOpened(WindowEvent e){
	   System.out.println("window opened" );	    
  }
public void windowActivated(WindowEvent e){
	    System.out.println("window Activated" );	    
  }
 public void windowDeactivated(WindowEvent e){
	   System.out.println("window Deactivated" );	    
  }
 
 }
 public class TestWindowEvent  extends JFrame{     
	TestWindowEvent(){		 
		this.addWindowListener(new windowListener());
		this.setSize(200,200);
		setVisible(true);		
	}
	public static  void main(String[]args){
		new TestWindowEvent();
	}
 }