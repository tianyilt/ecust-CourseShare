using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace WindowsFormsApplication1
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_Load(object sender, EventArgs e)
        {
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;//重要:非UI线程可以访问UI控件，但有安全问题


        }


        public void fun()
        {

            int i = 0;
            while (true)
            {
                i++;
                this.label1.Text = ""+i;
               // Thread.Sleep(1000);


            }
        }


        private void button1_Click(object sender, EventArgs e)
        {
            Thread my = new Thread(fun);  // 线程
         //   my.IsBackground = true;
             
            my.Start();
            

            
        }
    }
}
