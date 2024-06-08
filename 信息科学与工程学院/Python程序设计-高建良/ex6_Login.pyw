import tkinter
import tkinter.messagebox

# 创建应用程序窗口
root = tkinter.Tk()
root.title('登录')
# 与姓名关联的变量
varName = tkinter.StringVar()
varName.set('')
varPwd = tkinter.StringVar()
varPwd.set('')
#定义窗口大小
root['height'] = 100
root['width'] = 320
# 创建标签
labelName = tkinter.Label(root, text='姓名:', justify=tkinter.RIGHT, width=80)
# 将标签放到窗口上
labelName.place(x=10, y=5, width=80, height=20)
# 创建文本框，同时设置关联的变量
entryName = tkinter.Entry(root, width=80, textvariable=varName)
entryName.place(x=100, y=5, width=80, height=20)

labelPwd = tkinter.Label(root, text='密码:', justify=tkinter.RIGHT, width=80)
labelPwd.place(x=10, y=30, width=80, height=20)
# 创建密码文本框
entryPwd = tkinter.Entry(root, show='*', width=80, textvariable=varPwd)
entryPwd.place(x=100, y=30, width=80, height=20)
# 登录按钮事件处理函数
def login():
    # 获取用户名和密码
    name = entryName.get()
    pwd = entryPwd.get()
    if name == 'admin' and pwd == '123456':
        tkinter.messagebox.showinfo(title='Python tkinter', message='OK')
    else:
        tkinter.messagebox.showerror('Python tkinter', message='Error')


# 创建按钮组件，同时设置按钮事件处理函数
buttonOk = tkinter.Button(root, text='登录', command=login)
buttonOk.place(x=30, y=70, width=50, height=20)


# 取消按钮的事件处理函数
def cancel():
    # 清空用户输入的用户名和密码
    varName.set('')
    varPwd.set('')


buttonCancel = tkinter.Button(root, text='退出', command=cancel)
buttonCancel.place(x=90, y=70, width=50, height=20)
# 复选框
remePwd = tkinter.Checkbutton(root, text='记住密码', onvalue=1, offvalue=0)
remePwd.place(x=190, y=30, width=100, height=20)
# 启动消息循环
root.mainloop()
