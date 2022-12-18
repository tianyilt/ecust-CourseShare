nameList = {'草肥熊': 65, '黄小丫': 52, '大黄鸭': 102, '胳膊粗': 89, '腿脚细': 90, '水蛇腰': 116, '水桶腰': 53}  # 网名和时间字典
noPass = {}  # 普通网虫字典初始化
Pass = {}  # 发烧级网虫字典初始化
for name, onlineTime in nameList.items():  # 遍历名单的键值对
    if onlineTime < 90:
        noPass[name] = onlineTime  # 添加普通网虫到普通字典
    else:
        Pass[name] = onlineTime  # 添加发烧级网虫到发烧字典
print('发烧级网虫:')
for name, onlineTime in Pass.items():  # 遍历发烧级网虫的键值对
    print(name, onlineTime)
print('\n普通网虫:')
for name in noPass.keys():  # 遍历普通网虫网名
    print(name, noPass[name])  # 通过网名输出网名和成绩
