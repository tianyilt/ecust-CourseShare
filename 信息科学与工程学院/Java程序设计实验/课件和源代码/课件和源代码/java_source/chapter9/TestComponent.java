import java.awt.*;
import javax.swing.*;
public class TestComponent extends Frame{    
    TestComponent(String title){
		super(title);
		JLabel prompt1=new JLabel("姓名");
		JLabel prompt2=new JLabel("性别");
		JLabel prompt3=new JLabel("个人爱好");
		JTextField name=new JTextField(10);
		 ButtonGroup group=new ButtonGroup();
		JCheckBox  check1=new JCheckBox("男" );
        JCheckBox  check2=new JCheckBox("女" );
		group.add(check1);
		group.add(check2);
        
		JCheckBox  check3=new JCheckBox("篮球");
        JCheckBox  check4=new JCheckBox("田径");
        JCheckBox  check5=new JCheckBox("游泳");

		setLayout(new FlowLayout());
        add(prompt1);add(name);
		add(prompt2);add(check1);add(check2);
		add(prompt3);add(check3);add(check4);add(check5);
		setBounds( 100, 100, 300, 300); 
		setVisible(true);
	}
	public static void main(String[] args){ 
     new TestComponent("Swing组件测试程序"); 
   } 
} 

