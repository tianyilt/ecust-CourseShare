public class TestActionEvent extends JFrame implements ActionListener{
	JLabel jl=new JLabel();
	JButton jb=new JButton("ok");int i=0;
	TestActionEvent(){
		jb.addActionListener(this);
		getContentPane().add(jl,"North");
		getContentPane().add(jb,"Center");		
		setSize(200,300);
		setVisible(true);
	};  
    public void actionPerformed(ActionEvent e){	
	      if (i==0){
	         jl.setText("1");
	         i=1;
	       }else{
	         jl.setText("0");
	         i=0;
               }
        }
	public static void main(String[] args) 	{
		 new TestActionEvent();
	}
	
}
