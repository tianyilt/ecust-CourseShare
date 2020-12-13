'''
32 位字节地址
直接映射
Cache大小 2^n 块，n 位用来tag
块大小 2^m 个字，2^(m+2) 个字节
------------------------
|标记  | n tag |  m  | 2  |
------------------------
'''


"""
字地址
----------------------------
 |  4   |
----------------------------

字节地址
----------------------------
 |  2   | 2|
----------------------------
用于字内寻址，如果块内有多个字，还要块内字寻址
"""
cache位数 = 8
访问地址 = [
    3, 100, 4, 2, 190, 102, 190, 14, 190, 4, 186, 3
]
tag = dict()
# tag : {  index 索引:tag 标记}
二进制总位数 = 8
tag位数 = 二进制总位数-4
块内数 = 0
j = 1
for i in 访问地址:
    print(j, end='')
    j += 1
    bini = bin(i)[2:].zfill(二进制总位数)
    # print(bini)
    标记 = bini[:tag位数]
    index = bini[tag位数:]
    if index in tag.keys() and (tag[index] == 标记):
        print(f'{str(i).center(7)}{bini.center(7)}{"命中".center(7)}')
    elif index in tag.keys() and tag[index] != 标记:
        print(f'{str(i).center(7)}{bini.center(7)}{"缺失替换".center(7)}')
        tag[index] = 标记
    else:
        tag[index] = 标记
        print(f'{str(i).center(7)}{bini.center(7)}{"缺失".center(7)}')

# [tag位数:] 冒号后面根据需要修改为 [tag位数:] [tag位数:-1] [tag位数:-2]
