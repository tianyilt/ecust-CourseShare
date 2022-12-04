import java.awt.*;
public class TestBorderLayout extends Frame{
  TestBorderLayout(String title){
     super(title);
     Button North=new Button("North");
     Button South=new Button("South");
     Button West=new Button("West");
     Button East=new Button("East");
     Button Center=new Button("Center");
     setLayout(new BorderLayout());
     add(North,"North"); add(South,"South");
     add(West,"West");   add(East,"East");
     add(Center,"Center");
     setBounds(100,100,250,250);
     setVisible(true);
     }
  public static void main(String[] args){
      String title=new String("FlowLayout ≤‚ ‘≥Ã–Ú");
      TestBorderLayout t1=new TestBorderLayout(title);
  }
}

     
     
    