'''
jmp 跳转
'''

目标地址 = '000100001111110101001010'
# if '1' in 目标地址[:4]:
#     print('no')
# else:
#     print('y')
'''
bne
'''

offset_max = '0'+'1'*9
offset_neg_max = -2**15
PC = 0
print(offset_max)
offset4的二进制 = bin(int(offset_max, 2)*4)[2:].zfill(32)
正向最远 = int(offset_max, 2)*4+4+PC*4
负向最远 = offset_neg_max*4+PC+4
print(f'{hex(正向最远)}')
print(f'{hex(int("ffffffff", 16)+负向最远)}')
