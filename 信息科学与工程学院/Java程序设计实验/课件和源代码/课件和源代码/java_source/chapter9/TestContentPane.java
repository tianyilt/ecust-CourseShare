import javax.swing.JFrame; 
import java.awt.Container; 
import javax.swing.JPanel; 
import javax.swing.JLabel; 
import javax.swing.JTextField;  

public class TestContentPane{
     JFrame jFrame=null; //顶层容器
	 Container contentPane=null;//顶层容器jFrame的内容器
	 JPanel jPanel = null;//通用容器
	 JLabel  nameLabel=null;  //组件
     JTextField name=null; //组件 
	 public TestContentPane(){
       jFrame=new JFrame("JPanel 测试程序 ");
	   jFrame.setBounds(100,100,300,300);
	   jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
	   //将窗口框架的左上角位置设置为坐标点100，100，宽为width,高为height大小
        
	   //contentPane=jFrame.getContentPane();

	   //显示窗口框架
	   jPanel = new JPanel();  
	   nameLabel = new JLabel("姓名"); 
       name= new JTextField(10); 
       jPanel= new JPanel();  
	   jPanel.add(nameLabel);        
       jPanel.add(name); 
       //contentPane.add(jPanel); 

       jFrame.setContentPane(jPanel);
	    
	   jFrame.setVisible(true);//一般要放置在最后

      } 
    public static void main(String[] args){ 
      TestContentPane tp = new TestContentPane( ); 
    } 
} 

