def isLeap(year):
    return year % 400 == 0 or year % 4 == 0 and year % 100 != 0


def prtLeap(startY, endY):
    c = 0
    for i in range(startY, endY + 1):
        if isLeap(i):
            c += 1
            if c % 10 == 0:
                print(i, end='\t\n')
            else:
                print(i, end='\t')


def main():
    prtLeap(1900, 2020)


main()
