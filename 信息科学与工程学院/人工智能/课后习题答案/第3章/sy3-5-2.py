chinese = [76, 63, 79, 82, 53, 78, 67]
math = [88, 56, 78, 92, 69, 75, 82]
total = []
for i in range(len(math)):
    total.append(math[i] + chinese[i])
print("每位组员总分：", total)
print("最高总分：{},小组平均分{:.2f}".format(max(total), max(total) / len(total)))
