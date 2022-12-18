a = input('请输入字符串:')
li = []
for i in range(0, len(a)):
    # if (a[i] >= 'a' and a[i]<='z') or (a[i] >= 'A' and a[i]<='Z'):
    if a[i].isalpha():
        ch = a[i].lower()
        if ch not in li:
            li.append(ch)
print('找到的英文字母有: ')
for ch in li:
    print(ch, end="")
