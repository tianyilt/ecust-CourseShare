package com.lib.login; 
import javax.swing.*;
import java.awt.BorderLayout; 
import com.lib.system.MainFrame;
//以下程序仅仅是一个图形用户界面，无事件处理
public class  Login{
	JFrame LoginFrame;//顶层容器
	JPanel  LoginPanel;//JPanel放置在顶层容器LoginFrame中
	JButton ok=null;  //"登录"按钮
	JButton cancel=null;  //"退出"按钮
	JLabel NoLabel=null;  // "用户名"标签
	JLabel PasswordLabel=null; // "密码"标签
	JTextField No=null;    // "用户名"编辑框
	JTextField Password=null; //"密码"编辑框 
	public Login(){		super();	}

	public Login(String title){
		LoginFrame=new JFrame();
		LoginPanel=new JPanel();
		NoLabel=new JLabel("用户名");
		PasswordLabel=new JLabel("    密码");
	    
        No= new JTextField(10); 
        Password = new JTextField(10);  
		ok=new JButton("登录");
        cancel=new JButton("退出");      

		LoginPanel.add(NoLabel  ); 
		LoginPanel.add(No  ); 
		LoginPanel.add(PasswordLabel  ); 
		LoginPanel.add(Password  ); 
		LoginPanel.add(ok  ); 
		LoginPanel.add(cancel  ); 

		BorderLayout LoginFrameLayout=new BorderLayout(); 
		LoginFrame.setLayout(LoginFrameLayout);
		LoginFrame.setTitle(title);
		LoginFrame.add("Center", LoginPanel ); 
		LoginFrame.setBounds(600,300,200,200); 
        LoginFrame.setVisible(true); 
	} 
   
	public static void main(String[] args) { 
		Login login=new Login("登录界面");		 
	}
}

 