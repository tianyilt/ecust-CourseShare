# 数字信号处理 综合实践项目

- [数字信号处理 综合实践项目](#数字信号处理-综合实践项目)
  - [1. 项目简介](#1-项目简介)
  - [2. quick start](#2-quick-start)
  - [3. 文件介绍](#3-文件介绍)
    - [p1\_find\_peaks.m](#p1_find_peaksm)
    - [p2\_note\_pitch.m](#p2_note_pitchm)
    - [p3\_whole\_song.m 和 compare.m](#p3_whole_songm-和-comparem)
    - [p4\_application.m](#p4_applicationm)
    - [p4\_check\_chord.m](#p4_check_chordm)
    - [p5\_rhythm.m](#p5_rhythmm)
    - [p6\_overall.m](#p6_overallm)

## 1. 项目简介

"数字信号处理"课程综合实践项目, 实现对一段(纯钢琴弹奏的)音乐的频谱分析和旋律节奏提取

## 2. quick start

1. 在`param_setting.json`中设置参数
2. 运行`p6_overall.m`即可
3. 结果会保存到`output`文件夹中

输出格式:

```json
{
    "name": "star_69.wav",
    "tempo": 69,
    "key_list": [60],
    "dur_list": [1]
}
```

## 3. 文件介绍

### p1_find_peaks.m

实现了对音频信号的频谱分析, 通过滤波找到音频包络, 再通过寻找包络的极大值点来找到频谱的峰值点  
这些峰值点即代表了音符, 简单来说就是找到每个音符的起始位置  
区分出音符的准确性直接影响到后续的所有操作  

实现思路:

1. 对音频信号进行分帧(类似预分频)
2. 对每一帧进行滤波, 得到包络(用到了多点均值 和 平滑滤波`medfilt1`)
3. 对包络进行峰值检测, 得到峰值点

> 对于峰值检测, 采用了`widthreference`, `MinPeakHeight`, `MinPeakProminence`多个指标来筛选峰值点
> 通过多组对比实验, 最终确定了这些参数的值

将其封装成函数, 化为`get_peaks`函数  
函数签名: `function [envelope, peaks, start_index] = get_start_index(x,~,Frame_Num,threshold)`

- 输入参数:
  - `x`: 输入音频信号
  - `~`: 无用参数(Fs)
  - `Frame_Num`: 信号分帧数
  - `threshold`: 峰值点强度的阈值(一般别动)

### p2_note_pitch.m

在得到了音符的起始位置后, 还需要确定音符的**有效长度**  
针对定长和间隔时间的2/3长度做了对比, 最终确定了音符的有效长度为**音长的2/3长度**  
以及矩形窗和汉明窗的对比, 最终确定了**汉明窗**
得出幅频特性图, 再依据频率和钢琴键的对应关系, 得到每个琴键对应的能量强度  
最后通过瀑布流图直观展示  

将其封装成函数, 化为`get_Amp_MS`函数和`Amp_to_Key`函数  
函数签名: ```function Amp_MS = get_Amp_MS(audio, fs, Frame_Num, F0)
function KeyEnergy_Ms = Amp_to_Key(Amp_MS, F0)```

- 输入参数:
  - `audio`: 输入音频信号
  - `fs`: 采样频率
  - `Frame_Num`: 信号分帧数
  - `F0`: 观察的谱间隔
- 输出参数:
  - `Amp_MS`: 频谱幅度
  - `KeyEnergy_Ms`: 钢琴键能量

### p3_whole_song.m 和 compare.m

对于每个音符, 通过分析其琴键能量, 得到了音符的音高
一般来说, 通过观察中央音区的能量谱可发现如下规律:

- **最强**对应的琴键就是音符的本身的音高  
- **次强**对应的是琴键是音符的 **12半音泛音**
- **再次**对应的是琴键是音符的 **19半音泛音**
  
然而, 在低音区, 12半音泛音的能量会比音符本身的音高还要强, 因此需要特殊处理  
`p3_whole_song.m`是朴素取最大做法, `compare.m`是对比多个音阶方便调参数的  

我的实现思路是:

1. 先看最大值, 再取所有强度大于`sensitivity`的值(他们都可能是音符的音高, 在低音有些音是真的小, 因此为了保险我取了0.05)  
2. 如果可能的值里, 最低音也恰好是最大值, 那么就取最大值对应的琴键没错了  
3. 如果不是, 那么就对所有的候选做评估, 评估方法是:

   - 取出该候选的本音/12音/19音的能量
   - 加权求和(这个权重就纯经验了)  
   - 可能性最大的判定为音符的音高

将其封装成函数, 化为`get_note_key`函数  
函数签名: `function [Key_Rec, Key_code, Key_index, Key_count] = get_note_key(start_index, KeyEnergy_Ms, threshold)`  

- 输入参数:
  - `start_index`: 音符的起始位置
  - `KeyEnergy_Ms`: 钢琴键能量
  - `threshold`: 用于限制检测琴键值的范围, (a, b], 不包含左端点, 包含右端点
- 输出参数:
  - `Key_Rec`: 用于绘制瀑布图的矩阵
  - `Key_code`: 音符对应的键号数组, 下标在1-88之间
  - `Key_index`: 音符的起始位置, 与start_index相同
  - `Key_count`: 音符数量

### p4_application.m  

运用上述处理, 在整曲上进行了音符的提取和音高的识别  

### p4_check_chord.m

取出单个和弦(双音)分析其组成音, 可以明显通过12音和19音的能量分布来判断和弦的组成  
但是完全自动化的判断还是有一定难度, 因此实际提取用threshold限制了最低识别的音符范围, 不识别低音  

### p5_rhythm.m

通过音符的起始位置, 计算出音符的时长, 结合拍号, 得到了音符的时值  
再和已知的理想的音符时值进行对比, 从而对演奏者的节奏进行评估  

由于要提取乐谱, 因此会将演奏的实际时值按最好时值归一化处理, 表示为整数倍  
封装成函数`get_rhythm`  
函数签名: `function real_beat_t = get_rhythm(start_index, Frame_Num, Fs, tempo, min_div)`

- 输入参数:
  - `start_index`: 音符的起始位置
  - `Frame_Num`: 信号分帧数
  - `Fs`: 采样频率
  - `tempo`: 拍号
  - `min_div`: 最小音符时值, 如果不填则返回真实的浮点数
- 输出参数:
  - `real_beat_t`: 音符的时值

### p6_overall.m

加入了自动化处理, 从参数json文件中读取参数, 并将结果和图像保存到指定文件夹
