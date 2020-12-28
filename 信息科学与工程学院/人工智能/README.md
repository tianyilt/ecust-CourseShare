#

PPT

http://cs.e.ecust.edu.cn/download/1bb4978df63b52be1e8b774bac119bdd
http://cs.e.ecust.edu.cn/download/c582954777d8cf35edede15d63ac5fa1
http://cs.e.ecust.edu.cn/download/c6c2d42fbb81b7bcd8d32e6591af062d
http://cs.e.ecust.edu.cn/download/67292185629d75d936e6aa3f35f52988
http://cs.e.ecust.edu.cn/download/ac41bf4c6a227757fe2a823f2006c540
http://cs.e.ecust.edu.cn/download/d06be3daa8c9774736b93cd60e2b16e5
http://cs.e.ecust.edu.cn/download/c56d597f925c045f2471c0ed8122b1b1
http://cs.e.ecust.edu.cn/download/a5469d68aedf04588f9495d4a4d533a4

---

## 下面是简单总结的笔记，raw 模式下复制到支持公式的 markdown 解析器里就能看了.

---

### 命题公式

记得按从低到高排序

矛盾式，可满足式，重言式

### 不确定性推理

- MB(h,e) 在证据 e 下对 h 的信任增加度
- MD(h,e) 在证据 e 下对 h 的不信任增加度
- CF(h,e) = MB(h,e)-MD(h,e) 可信度

$$
CF(h,e) =\begin{cases}
1&P(h) = 1 \\
MB(h,e)&P(h|e) > P(h)  \\
0&P(h|e) = P(h)  \\
-MD(h,e)&P(h|e) < P(h)  \\
-1&P(h) = 0  \end{cases}
$$

CF(h,e) 的说明

1. 大于 0 时，证据 e 的出现增加了结论 h 为真的概率；
2. 等于 1 时，证据 e 使得 h 为真
3. 小于 0 时，证据 e 的出现减少了结论 h 为真的概率；
4. 等于 -1 时，证据 e 使得 h 为假
5. 等于 0 时，证据 e 和结论 h 不相关

IF E THEN H (CF(H,E))

- CF(E): 证据本身的可能性
- CF(H,E) E = True，H 的可能性
- E=and(Ei) => CF(E)=min(CF(Ei))
- E=or(Ei) => CF(E)=max(CF(Ei))
- $CF(H) = CF(H,E) × \max \{ 0,CF(E)\}$

---

### 不精确推理模型

例题
设有下述一组知识：

- r1: IF E1 THEN H (0.8)
- r2: IF E2 THEN H (0.6)
- r3: IF E3 THEN H (-0.5)
- r4: IF E4 AND(E5 OR E6) THEN E1(0.7)
- r5: IF E7 AND E8 THEN E3(0.9)
- 已知 CF(E2)=0.8, CF(E4)=0.5, CF(E5)=0.6
  CF(E6)=0.7, CF(E7)=0.6, CF(E8)=0.9
- 求：CF(H) （运算过程保留小数点后 2 位)

### 产生式系统

推理树

先建树，计算出 CF(E1),CF(E2),CF(E3)

然后计算 $CF_1(H)=0.8*0.35=0.28$

接下来合成 3 个 CFi(H)

$$
CF_{1,2}(H)=\begin{cases}
    CF_1(H) +CF_2(H)- 乘起来 & ⩾ 0\\
    CF_1(H) +CF_2(H)+ 乘起来 & <0\\
  \dfrac{CF_1(H)+CF_2(H)}{1-\min(|CF_1(H)|,|CF_2(H)|)} & 异号
\end{cases}
$$

---

### 带加权因子的推理

$$
CF(E)=∑_{i=1}^{n}{\omega_i}* CF(E_i)
$$

$$
CF(H)=CF(H,E)*CF(E)
$$

---

### Zadeh 表示法

隶属函数 A(x)

$$
A=∑ \frac{A(xi)}{xi}
$$

- 包含：分子 >
- 相等：分子 =
- 并集：取最大
- 交集：取最小
- 补集：1- 每项
- 乘积：分母是元组，分子取 min

---

### 模糊关系矩阵的乘法

正常乘法，\* 重载为 min，+ 重载为 max

---

### 贴近度

$(A,B) = \frac{1}{2}[A \bullet B - A * B+1]$

$$
A \bullet B = \mathop  \vee \limits_U (\mu A(u_i) \wedge \mu B(u_i)),A * B = \mathop  \wedge \limits_U (\mu A(u_i) \vee \mu B(u_i))
$$

```py
def ∙(A,B):
    return max(map(min,zip(A,B)))
def *(A,B):
    return min(map(max,zip(A,B)))
```

---

$$
U = V = \left\{ {1,2,3,4,{\text{5}}} \right\}  \\
A = 1/1 + 0.5/2  \\
B = 0.4/3 + 0.6/4 + 1/5  \\
$$

模糊规则

$$
IF\ x\  is\  A\  THEN\  y\  is\  B(\lambda )
$$

证据

$$
x\  is\  A'  \\
A' = 1/1 + 0.4/2 + 0.2/3\\
(A,A') > \lambda
$$

求

$$
Bm'
$$

$$
B'm = A' ∘ Rm = A' ∘ [(A × B) ∪ (¬ A × V)]
$$

---

### 非单调推理

除了企鹅以外，大多数的鸟都会飞；

除了鹦鹉以外，一般动物都不会讲话

$$
\frac{BIRD(x):M(CAN - FLY(x) \wedge ¬ Penguin(x))}{CAN - FLY(x)}\\
\frac{ANIMAL(x):M(¬ SPEAK(x) \wedge ¬ PARROT(x))}{¬ SPEAK(x)}
$$

---

### TMS 正确性维持系统

P360

每得到一个命题，就按照

序号。谓词（对象) SL(IN_List)(OUT_List) IN/OUT

来写

如果出现逻辑问题，就把冲突的节点放到新节点的 IN_List 里，然后依次取 OUT，看是否解决冲突

---

### 主观 Bayes 算法

#### 确定性

题目会给 IF E THEN (LS,LN) R(P(R)) 格式的内容

$$
\tag{2} P(x)=\frac{O(x)}{1+O(x)}
$$

$$
\tag{5}P(R|E)=\frac{LS *P(R)}{(LS-1)*P(R)+1}
$$

$$
\tag{6}P(R|¬ E)=\frac{LN *P(R)}{(LN-1)*P(R)+1}
$$

代入公式算

---

### 决策树

A=B and C=D, A 是根节点，B 是分支名，and 表示连接

---

### 熵

题目会给 S 的属性 A，A 有两个值 B，C

B，C 有各自正反例占比

$$
熵=∑_{V∈\{B,C\}} \frac{B}{A}E(B)+\frac{C}{A}E(C)
$$

然后 E(A)

$$
-\frac{True}{all}*\log_2\left(\frac{True}{all}\right)-\frac{False}{all}*\log_2\left(\frac{False}{all}\right)
$$

增益

$$
Gain(S,A)=E(S)-熵
$$

画决策树:

计算按不同分类的 Gain，大的作为根节点

---

实例空间

$$\prod_{i = 1}^n {m_i}$$

搜索空间

$$1+\prod_{j = 1}^n {(m_j + 1)}$$

---

### FindS 算法

先初始化为 $<\Phi,\Phi,\Phi,\Phi>$

遇到一个新的，就批量替换，总是最特殊那个

假如只有 2 个，改为 ?

有 >2 个，改为 or

---

### 找平面分割

$\omega_1 x1 + \omega_2 x2 + b = 0$

构成 x1-x2 平面的一根直线

\> 0 True ⩽ 0 False

1. 画出布尔函数的真值表；
2. 画出 x1--x2 坐标系的输入点；
3. 画出对输入点正确分类的直线，标出正方向；
4. 写出直线方程；
5. 得到感知器的参数

---

- 填空 20
- 选择 16
- 计算 40
- 综合 24

---

模糊推理

RN 不用记

不确定推理不用

---

命题公式掌握

---

计算题：

- 命题公式\*5；
- Rm
- 贝叶斯

大题：

- 推理树
- 决策树
- 感知器
