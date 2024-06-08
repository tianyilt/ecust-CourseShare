# 使用随机数函数产生20个同学的成绩，存入文本文件ex4_scores.txt中
# 从文件中读入这些成绩，将其转换成等级，将成绩和等级存入文本文件ex4_degrees.txt中，并在屏幕上输出
# 90-100分为A；80-89为B；70-79为C；60-69为D；60以下为E
# 说明：数据存储方式有列表、元组、字典等，数据输入方式有直接赋值、键盘输入、文件读取、随机产生等，结果可以输出到屏幕，也可以输出到文件等。

import random
# ---创建&写入---
list_a = [random.randint(0, 100) for x in range(20)]
# print(list_a)
f_scores = open("ex4_scores.txt", 'w')
for num in list_a:
    f_scores.write(str(num)+"\n")
f_scores.close()

# ---读取分析---
f_scores = open("ex4_scores.txt", 'r')
scores_str_list = f_scores.readlines()
scores_int_list = list(map(int, scores_str_list))
grades_str_list = []
f_scores.close()

# ---写入grade---
f_grades = open("ex4_grades.txt", "w")
for i in range(20):
    if(scores_int_list[i] >= 90):
        f_grades.write("A\n")
    elif(90 > scores_int_list[i] >= 80):
        f_grades.write("B\n")
    elif(80 > scores_int_list[i] >= 70):
        f_grades.write("C\n")
    elif(70 > scores_int_list[i] >= 60):
        f_grades.write("D\n")
    elif(scores_int_list[i] < 60):
        f_grades.write("E\n")
f_grades.close()