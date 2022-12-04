 import java.awt.*;
 public class TryFrame extends Frame{
      TryFrame(String str){
         super(str);
	Button ok=new Button("确定");
	Button cancel=new Button("取消");
	setLayout(new FlowLayout());
	add(ok);
	add(cancel);
        setBounds( 100, 100, 500, 500);  //setSize(200,100);	
        setVisible(true); 	//show();
	}
       public static void main(String[] args){
	  new TryFrame("Frame 测试程序");
	}
}
