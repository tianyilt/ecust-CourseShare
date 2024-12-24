# 通信电子线路（3 学分）

教师：凌小峰；从不点名，讲课比较抽象，建议全部翘掉。

信工大三上最抽象的一门课，没有之一。不过虽然抽象，考试还是相对简单的。

## 2023 考试

**没考**的内容：传输线阻抗，魔 T 网络，超外差收音机，鉴频器，角度调制的电路

- 简答 5 分 \* 6
  1. 地波相关
  2. 抽头阻抗变换如何影响电流源和极间电容
  3. 多级噪声系数。有点坑，第一级和第三级给了增益和噪声系数，第二级只给了一个衰减 8dB
  4. 高频功放调整什么参数能够从欠压到过压
  5. 忘了
  6. 忘了
- 计算题 10 分 \* 4
  1. 标准的高频小放，电路图与复习 ppt 上的完全一致，题目稍有不同。
     - 没考多级
  2. 功放，无图，给参数求参数。
  3. 唯一的一题角度调制，最简单的，类似复习 ppt 上第三题。
  4. 双二极管调幅电路的计算。
- 推导题 10 分：耦合回路，求证临界耦合系数 $k=1/Q$, Q 为初级回路与次级回路的品质因数比
- 设计题 10 分：有一个压感电容，（调幅，调相，调频选择其一）设计一个天线发送 - 接收系统传输压力值，使用最少的三极管。只要写过最后一次实验报告就没啥问题。
- 材料题 10 分：主要说火星探测器的通讯问题难点及改进，白送的 10 分

## 实验

- 示波器的管子有 1x 和 10x 之分，别搞错了。一般都用 1x。
- 第一节课先拍实验手册，报告很多能抄手册。

## [笔记](https://absx.pages.dev/farraginous/learning/CEC.html)

## 作业

[这里](https://github.com/lxl66566/my-college-files/tree/main/信息科学与工程学院/通信电子线路)能找到部分作业，可以直接打印上交。本人不对合法性与正确性作出任何保证。

## 理论课件

```
# 1-1 ~ 3-1
https://cs.e.ecust.edu.cn/download/f7447cf8b83937d09a451f421dff80e4
https://cs.e.ecust.edu.cn/download/da258e69fd526f12c98976d9122979f1
https://cs.e.ecust.edu.cn/download/69354de5a39f5b45962d408693cd82a7
https://cs.e.ecust.edu.cn/download/65f51d1a3fa07fd5f069dc5b383c0fbb
https://cs.e.ecust.edu.cn/download/3df16ed7f62f0f297e4e55cb2651f85b
https://cs.e.ecust.edu.cn/download/b0df24b97f89828aa9a6e38a2b16fe37
https://cs.e.ecust.edu.cn/download/638cffe5dd0e3de3872962c5bf08d5ef
https://cs.e.ecust.edu.cn/download/e1072566034923ea32e57e77a04d97c9
https://cs.e.ecust.edu.cn/download/57e712998bc9155e0cadde5b327e81e9
https://cs.e.ecust.edu.cn/download/4590bc0aa9b1f62caca635f40de15658
# 3-2 ~ 4-7
https://cs.e.ecust.edu.cn/download/0d9e4a30a65149bd8c6ba73b66ae0e90
https://cs.e.ecust.edu.cn/download/b3c7a265c16f453f95fae3ca3e4e7547
https://cs.e.ecust.edu.cn/download/f4ea347a9ac6b50575618ede395d3b50
https://cs.e.ecust.edu.cn/download/30313b6271119a8d589889937fe45a2e
https://cs.e.ecust.edu.cn/download/9c3bac4596c357aab532cb45320cfe19
https://cs.e.ecust.edu.cn/download/036970b741c64ffa7c4fc1a03226a838
https://cs.e.ecust.edu.cn/download/0ecaa0ca3863ce66464dc68ed32977fc
https://cs.e.ecust.edu.cn/download/77b2a50a82b9fe6cd8ac0b77e78fc54b
https://cs.e.ecust.edu.cn/download/90a4a2fa5cbb1dc564b37272f809ed9f
https://cs.e.ecust.edu.cn/download/e6a7cca9f18dc36e823b091af4610c94
# 5-1 ~ 6-4
https://cs.e.ecust.edu.cn/download/1939208dc549d6b23285439f4cb2ac7b
https://cs.e.ecust.edu.cn/download/1e1a77bb71c7af3a68387c2e812ee4da
https://cs.e.ecust.edu.cn/download/eb5c0f002ed38d91ae2e8e79cdb47945
https://cs.e.ecust.edu.cn/download/546bb53a1e083f3caa665d236483323f
https://cs.e.ecust.edu.cn/download/7148ddbf920661174d34284ee6f631f9
https://cs.e.ecust.edu.cn/download/0c75d24ed81affb47c5dad35dc0af4f5
https://cs.e.ecust.edu.cn/download/dd610304ae002a7fbb40b39bd88c95f9
https://cs.e.ecust.edu.cn/download/f8314773e3e0b5db1fc041d8a793257d
https://cs.e.ecust.edu.cn/download/bdb1c5064da91a5a460f0b8508555abb
https://cs.e.ecust.edu.cn/download/0ea3544d8ccd4bba11fb6da3df4b9ad6
# 6-5 ~ 7-7
https://cs.e.ecust.edu.cn/download/25ed78d03c9789b2037861379d46c7b4
https://cs.e.ecust.edu.cn/download/17c5c53781038f54557f9b180ccc7b73
https://cs.e.ecust.edu.cn/download/eb62a1ba1c3ca8b44693188e07ab15a3
https://cs.e.ecust.edu.cn/download/977bd4e1b6ba45c0c297951cc949ca31
https://cs.e.ecust.edu.cn/download/23f037153bb17e192ce9ee2f942d8d70
https://cs.e.ecust.edu.cn/download/9ad4dec0d552c42d5cdf862e703cb612
https://cs.e.ecust.edu.cn/download/fcf9c86e997b91758705b5ee48ce34d8
https://cs.e.ecust.edu.cn/download/3d07c9e677199fc3f4ca2f0804ed09da
```
