while True:
    s = input()
    if len(s) < 8:
        print('密码长度要不小于8个字符，请重新输入')
    elif s.isdigit():
        print('密码要包含字母，请重新输入')
    elif s.isalpha():
        print('密码要包含数字，请重新输入')
    else:
        print('你的密码合格了')
        break
