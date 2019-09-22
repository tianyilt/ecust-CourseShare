package 实验一;

import java.awt.Graphics;
import java.applet.Applet;

public class HelloWorldApplet extends Applet {
	public void paint(Graphics g){
		g.drawString("Hello World!", 50, 50);
    }
}
