# 这里给出一些 C 语言课程编译器的推荐（Windows系统）

鉴于学校在很长的一段时间里还可能会用 《谭 C》 这本坑人的书。而且配套的 VC6.0 也非常老了，只支持 C89 标准。

所以下面给一些推荐

## 懒人式

1. Dev-C++

目前停止更新，内置编译器为 TDM-GCC 4.9.2

2. Code::Blocks

> 什么叫懒人式呢？

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
return 0;
}
```

如果编译以上代码不出错，就是懒人式。即无脑安装。

## 轻量型

1. tcc

非常小的 C 编译器。

> 具体使用方法为，设定环境变量后在 cmd 里 `tcc -run file.c` ，直接运行，不会生成 exe

2. tio.run

可在线运行各种语言

## 装 13 型

1. MinGW + VS code

请到网上自行搜索配置教程。VS code 的编辑体验相当好。

## 重量型

1. VS studio
