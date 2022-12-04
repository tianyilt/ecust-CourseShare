//import java.awt.*;
import javax.swing.*;
public class TestFlowLayout extends JFrame{
  TestFlowLayout(String title){
     super(title);
     setLayout(new FlowLayout(FlowLayout.LEFT,10,10));
     for(int i=1;i<10;i++){
        add(new JButton("button"+i));
     }
     setBounds(100,100,250,250);
     setVisible(true);
     }
  public static void main(String[] args){
      TestFlowLayout t1=new TestFlowLayout("FlowLayout ²âÊÔ³ÌÐò");
  }
}

     
     
    