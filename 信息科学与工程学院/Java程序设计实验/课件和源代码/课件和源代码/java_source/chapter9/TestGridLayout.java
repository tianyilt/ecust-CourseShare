import java.awt.*;
public class TestGridLayout extends Frame{
  Button[] button;
  String[] str={"0","1","2","3","4","5","6","7","8","9","+","-","*","/","="};
  Panel panel1,panel2;
  TestGridLayout(String title){
    super(title);
    setBounds(100,100,250,250);
    button=new Button[15];
    setLayout(new BorderLayout());
    Panel panel1=new Panel();
    Panel panel2=new Panel();
    add(panel1,"North");
    add(panel2,"Center");
    
    TextField tf=new TextField(20);
    panel1.add(tf);
    panel2.setLayout(new GridLayout(5,3));
    for(int i=0;i<15;i++){
      button[i]=new Button(str[i]);
      panel2.add(button[i]);
      }
    setVisible(true);
   }
   public static void main(String[] args){
      String title=new String("GridLayout ²âÊÔ³ÌÐò");
      new TestGridLayout(title);
      }
 }
    
    