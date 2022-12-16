import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.swing.*;
import javax.swing.border.EmptyBorder;

public class Calculator extends JFrame implements ActionListener {
    private ScriptEngine jse = new ScriptEngineManager().getEngineByName("JavaScript");

    private JPanel northPanel = new JPanel();
    private JTextField showText = new JTextField();
    private JButton acButton = new JButton("AC");

    private JPanel btnPanel = new JPanel(new GridLayout(4, 4, 4, 4));
    private JButton[] buttons = new JButton[16];
    private String btnStr = "789/456*123-0.=+";

    private void initUI() {
        this.setSize(300, 300);
        northPanel.setBorder(new EmptyBorder(6, 6, 6, 6));
        northPanel.setLayout(new BorderLayout());
        northPanel.add(showText, BorderLayout.CENTER);
        acButton.setFont(new Font("微软雅黑", Font.BOLD, 15));
        acButton.addActionListener(this);
        northPanel.add(acButton, BorderLayout.EAST);
        this.add(northPanel, BorderLayout.NORTH);

        btnPanel.setBorder(new EmptyBorder(6, 6, 6, 6));
        for (int i=0; i < btnStr.length(); i++) {
            buttons[i] = new JButton(String.valueOf(btnStr.charAt(i)));
            buttons[i].setFont(new Font("微软雅黑", Font.BOLD, 15));
            buttons[i].addActionListener(this);
            btnPanel.add(buttons[i]);
        }
        this.add(btnPanel, BorderLayout.CENTER);
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        JButton button = (JButton) e.getSource();
        if (button.getLabel().equals("AC")) {
            showText.setText("");
        }else if (button.getLabel().equals("=")) {
            try {
                showText.setText(jse.eval(showText.getText()).toString());
            } catch (ScriptException e1) {
                e1.printStackTrace();
            }
        }else {
            showText.setText(showText.getText() + button.getLabel());
        }
    }

    private Calculator (String title) throws HeadlessException {
        super(title);
    }

    public static void main(String[] args) {
        new Calculator("Calculator").initUI();
    }
}
