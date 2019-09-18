public class frame  extends JFrame{
  frame(){
     JButton jb1=new JButton("ok");
     JButton jb2=new JButton("cancel");
     JMenuBar jmb=new JMenuBar();
      jmb.setOpaque(true);
      jmb.setBackground(Color.cyan);
      jmb.setPreferredSize(new Dimension(200, 20));       
    JPanel contentPane = new JPanel(new FlowLayout());
    //Make it the content pane.
    contentPane.setOpaque(true);
    setContentPane(contentPane);    
    getContentPane().add(jb1);
    getContentPane().add(jb2);
    setJMenuBar(jmb);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setVisible(true);  
   }   
    public static void main(String[] args){   
		new frame();	   	 
   }
}
