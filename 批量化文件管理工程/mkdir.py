import os
"""
用来给课程文件夹建立目录
"""
def AutoMkdir(path,name):
    dir_path=os.path.join(path,name)
    if not os.path.exists(dir_path):
        os.mkdir(dir_path)
    return dir_path

main_path = "../数学系/专业选修/"
class_list = sorted(os.listdir(main_path))
for class_name in class_list:
    class_path=os.path.join(main_path,class_name)
    AutoMkdir(class_path, '考试')
    AutoMkdir(class_path, '作业')
    sub_path=AutoMkdir(class_path, '课件与教材')
    AutoMkdir(sub_path, '课件')
    sub_path=AutoMkdir(class_path, '复习')
    AutoMkdir(sub_path, '思维导图')
    AutoMkdir(sub_path, '复习文档')