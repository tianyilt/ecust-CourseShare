import struct


def float_to_bin(num):
    bits, = struct.unpack('!I', struct.pack('!f', num))
    return "{:032b}".format(bits)


print(float_to_bin(
    -0.875))
print(hex(int(float_to_bin(63.25), 2)))
# http://www.styb.cn/cms/ieee_754.php
# https://blog.csdn.net/u012063703/article/details/42609833
print(bin(~-20+1 & 0xFF))
