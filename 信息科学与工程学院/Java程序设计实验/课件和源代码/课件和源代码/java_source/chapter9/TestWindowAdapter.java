 import java.awt.*;
 import java.awt.event.*;
 import javax.swing.*;
 class windowAdapter extends WindowAdapter {   
  public void windowClosing(WindowEvent e){
	 System.out.println("window closed" );	  
	 System.exit(0);
  }   
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
 public class TestWindowAdapter  extends JFrame{     
	TestWindowAdapter(){		 
		this.addWindowListener(new windowAdapter());
		this.setSize(200,200);
		setVisible(true);		
	}
	public static  void main(String[]args){
		new TestWindowAdapter();
	}
 }