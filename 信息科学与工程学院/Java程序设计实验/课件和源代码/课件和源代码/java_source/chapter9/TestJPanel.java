public class TestJPanel{
     JFrame jFrame=null; //顶层容器
	 Container contentPane=null;//顶层容器jFrame的内容器
	 JPanel jPanel = null;//通用容器
	 JLabel  nameLabel=null;  //组件
     JTextField name=null; //组件 
	 public TestJPanel(){
       jFrame=new JFrame("JPanel 测试程序 ");
	   jFrame.setBounds(100,100,300,300);
	   //将窗口框架的左上角位置设置为坐标点100，100，宽为width,高为height大小
	   contentPane=jFrame.getContentPane();
	   //显示窗口框架
	   jPanel = new JPanel();  
	   nameLabel = new JLabel("姓名"); 
       name= new JTextField(10);          
	   jPanel.add(nameLabel);        
       jPanel.add(name); 
       contentPane.add(jPanel); 
       // this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
	   jFrame.setVisible(true);//一般要放置在最后
      } 
    public static void main(String[] args){ 
      TestJPanel tp = new TestJPanel( ); 
    } 
} 

