from sklearn.model_selection import train_test_split

s = "机器学习的研究涉及概率论统计学逼近论凸分析算法复杂度理论多门学科是人工智能的核心"
X, y = list(s), range(40)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=8)
print("测试集:", X_test)

