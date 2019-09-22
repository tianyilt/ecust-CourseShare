import javax.swing.*;
import java.awt.*;
public class TopLevelDemo2 {
   TopLevelDemo2(){
        JFrame frame = new JFrame("TopLevelDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create the menu bar.  Make it have a cyan background.
        JMenuBar cyanMenuBar = new JMenuBar();
        cyanMenuBar.setOpaque(true);
        cyanMenuBar.setBackground(Color.cyan);
        cyanMenuBar.setPreferredSize(new Dimension(200, 20));

        //Create a yellow label to put in the content pane.
        JLabel yellowLabel = new JLabel("center",JLabel.CENTER);
        yellowLabel.setOpaque(true);
        yellowLabel.setBackground(Color.yellow);
        yellowLabel.setPreferredSize(new Dimension(200, 180));
        //Set the menu bar and add the JButton to the content pane.
        frame.setJMenuBar(cyanMenuBar);
        frame.getContentPane().add(new JButton("north"),BorderLayout.NORTH);        
        frame.getContentPane().add(new JButton("south"),BorderLayout.SOUTH);
        frame.getContentPane().add(new JButton("west"),BorderLayout.WEST);
        frame.getContentPane().add(new JButton("east"),BorderLayout.EAST);
        frame.getContentPane().add(yellowLabel, BorderLayout.CENTER);
        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new TopLevelDemo2();
        
    }
}


         


