指令 = 'addi rd rs -20'
_list = 指令.split(' ')
cmd = _list[0]
if cmd == 'add':
    print('0'*6, 'rs', 'rt', 'rd', '0'*5, bin(int('20', 16))[2:].zfill(6))
elif cmd == 'addu':
    print('0'*6, 'rs', 'rt', 'rd', '0'*5, bin(int('21', 16))[2:].zfill(6))
elif cmd == 'beq':
    print(bin(int('4', 16))[2:].zfill(6), 'rs', 'rt',
          'offset')  # 424
