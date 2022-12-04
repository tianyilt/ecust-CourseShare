import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
class TestActionEvent2  extends JFrame {
 Button b3=new Button("exit");
    public TestActionEvent2(){
		this.getContentPane().setLayout(new BorderLayout());
		Panel p=new Panel();
       
		b3.addActionListener(  new ActionListener(){
			                       public void actionPerformed(ActionEvent e){
									    Object obj = e.getSource();      
									   if(obj==b3)  System.exit(0);
								   }
		                       }  
	                        );
		p.add(new Button("ok"));
		p.add(new Button("cancel"));
		p.add(b3);

		this.getContentPane().add(p);
		show();
	}
		

	public static void main(String[] args) 
	{
		new Jframe();
	}
}
