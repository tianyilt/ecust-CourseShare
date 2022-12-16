import javax.swing.*;
public class TryBorderLayout extends JFrame {   	
	JButton  North, South, West, East, Center;     	
	TryBorderLayout() {
	    super("Borderlayout布局管理器应用举例"); 	
	    North = new JButton("North");             	
	    South = new JButton("South");
	    West = new JButton("West");
	    East = new JButton("East");
	    Center = new JButton("Center");
	    getContentPane().add(North,"North");         
	    getContentPane().add(South,"South");
	    getContentPane().add(West,"West");
	    getContentPane().add(East,"East");
	    getContentPane().add(Center,"Center");
	    setSize(300,200);           			
	    setVisible(true);
	}
	public static void main(String[] agrs)
	{
	   TryBorderLayout frame = new TryBorderLayout();   	
	   frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
