# Chapter5
## 5.1
**函数依赖**： 关系模式中属性之间存在的一种约束关系。   

**平凡函数依赖与非平凡函数依赖**： 在关系模式中 $r(R)$ 中， $\alpha$ $\subseteq R ，\beta \subseteq R$。 若 $\alpha \rightarrow \beta$, 但 $\beta \not\subseteq \alpha$, 则称 $\alpha \rightarrow \beta$ 是非平凡函数依赖。反之，若  $\beta \subseteq \alpha$ ，则称 $\alpha \rightarrow \beta$ 是平凡函数依赖。  

**完全函数依赖与部分函数依赖**： 在关系模式 $r(R)$ 中，$\alpha \subseteq R ，\beta \subseteq R$，且 $\alpha \rightarrow \beta$ 是非平凡函数依赖。若对任意的 $\gamma \subset \alpha, \gamma \rightarrow \beta$ 都不成立，则称 $\alpha \rightarrow \beta$ 是完全函数依赖。否则，若存在非空的 $\gamma \subset \alpha$ 使 $\gamma \rightarrow \beta$ 成立，则称 $\alpha \rightarrow \beta$ 是部分函数依赖。   

**传递函数依赖**： 若 $\alpha \rightarrow \beta, \beta \rightarrow \gamma$，且 $\beta \not\subseteq \alpha, \gamma \not\subseteq \beta, \beta \not\rightarrow \alpha$，则必存在函数依赖 $\alpha \rightarrow \gamma$ ，并称 $\alpha \rightarrow \gamma$ 是传递函数依赖。  

**函数依赖集闭包**： 令F为一函数依赖集，F逻辑蕴涵的所有函数依赖组成的集合称为F的闭包，记为 $F^{+}$ 。  

**属性闭包**： 令 $r(R)$ 为关系模式，$F$ 为函数依赖集， $A \subseteq R$ 的属性集，则称在函数依赖集 $F$ 下由 $A$ 函数确定的所有属性的集合为 $F$ 下属性集 $A$ 的闭包，记为 $A^{+}$。  

**无损连接分解**： 能够根据分解后的关系通过连接运算还原原来的关系示例。  

**保持依赖分解**： 称具有函数依赖集 $F$ 的关系模式 $r(R)$ 的分解 $r_1(R_1), r_2(R_2), \cdots, r_n(R_n)$ 为保持依赖分解，当且仅当 $(F_1 \cup F_2 \cup \cdots \cup F_n)^+ = F^+$。  

**1NF**： 如果一个关系模式r(R)的每个属性对应的域值都是不可分的，则称r(R)属于第一范式。  

**2NF**： 如果一个关系模式r(R)属于第一范式，且所有非主属性都**完全函数**依赖于r(R)的候选码，则称r(R)属于第二范式。  

**3NF**： 如果一个关系模式r(R)属于第二范式，且所有非主属性都**直接函数**依赖于r(R)的候选码，则称r(R)属于第三范式。  

**BCNF**: 在关系模式r(R)中，如果每一个非平凡函数依赖 $\alpha \rightarrow \beta$ 的决定属性集 $\alpha$ 都包含候选码，则称r(R)属于BCNF方式。  

## 5.7
(1)  
$A^+ = \{ ABCDE \}$（第二次循环）；  
$B^+ = \{ BD \}$ （第二次循环）  
(2)  
由于所有函数依赖右方都没有出现的属性集X为空。
考虑每一条函数依赖，从左边属性较小的函数依赖开始：  
对于 $A \rightarrow BC$，$A^+ = \{ ABCDE \} = R$，所以A为候选码  
对于 $B \rightarrow D$，$B^+ = \{ BD \} \not= R$，所以B不是候选码  
对于 $E \rightarrow A$，$A^+ = \{ ABCDE \} = R$，所以E为候选码  
对于 $CD \rightarrow E$，$CD^+ = \{ ABCDE \} = R$，所以CD为候选码   
对于属性B，考虑增加属性A，由于A是候选码，所以AB不可能是候选码，排除。考虑增加属性C， $BC^+ = \{ ABCDE \} = R$，所以BC是候选码，考虑BD， $BD^+ = \{ BD \} \not= R$，所以BD也不是候选码。同样E是候选码，所以BE也不是候选码。  
综上 ，r(R)的候选码有A,E,CD,BC  

## 5.9
（1） $\{ AB, BC, ABDE, EG\}$  
$F_1 = \{ \}, F_2 = \{ \}, F_3 = \{AD \rightarrow E ,B \rightarrow D\}, F_4 = \{ E \rightarrow G \}.$   
原函数依赖集中的关于B，C属性的函数依赖全部丢失，故该分解没有保持依赖分解。  
对于分解 $r_1(R_1)=r_1(A,B)，r_2(R_2)=r_2(B,C)$，由于 $R_1 \cap R_2 = B$，且 $B \not \rightarrow r_1(R_1)，B \not \rightarrow r_2(R_2)$，故该分解不是无损连接分解。  
（2） $\{ ABC, ACDE, ADG \}$   
$F_1 = \{ AB \rightarrow C, AC \rightarrow B, BC \rightarrow A \}, F_2 = \{ AD \rightarrow E \}, F_3 = \{\}.$  
原函数集中 $B \rightarrow D, AC \rightarrow B, E \rightarrow G$ 均不能推导出来，故该分解没有保持依赖分解。  
对于分解 $r_2(R_2)=r_1(A,C,D,E)，r_3(R_3)=r_3(A,D,G)$，由于 $R_2 \cap R_3 = AD$，且 $AD \not \rightarrow r_2(R_2)，AD \not \rightarrow r_3(R_3)$，故该分解不是无损连接分解。   

## 5.10
### （1） $F_1 = \{C \rightarrow D, C \rightarrow A, B \rightarrow C\}$
#### 候选码：B
#### 范式：存在传递函数依赖，最高满足2NF
#### 分解：
$\qquad C \rightarrow D, C \rightarrow A$ 可合并为 $C \rightarrow AD$, 合并后的函数依赖的决定属性C不是超码，可分解为：  
$\qquad r_1(A,C,D),r_2(B,C)$    
$\qquad f_1=(C \rightarrow AD， 候选码为C)$  
$\qquad f_2=(B \rightarrow C， 候选码为B)$  
$\qquad $ 分解后满足BCNF范式
> $C \rightarrow AD$ 不满足，$\alpha = C, \beta = AD, R_1= \alpha \cup \beta = ACD, R_2 = R - (\beta - \alpha) = ABCD - (AD - C) = ABCD - AD = BC$  

### （2） $F_2 = \{ABC \rightarrow D, D \rightarrow A\}$
#### 候选码：ABC、BCD
#### 范式：$D \rightarrow A$  的决定属性D不是超码，最高满足3NF  
$\qquad$ （不存在非主属性对码的传递依赖，是3NF）
#### 分解：
$\qquad D \rightarrow A$  的决定属性D不是超码，可分解为：  
$\qquad r_1(A,D),r_2(B,C,D)$    
$\qquad $ 分解后满足BCNF范式（不保持依赖分解）  

### （3） $F_3 = \{A \rightarrow B, BC \rightarrow D\}$
#### 候选码：AC
#### 范式：存在部分函数依赖，最高满足1NF范式 $(AC \rightarrow B, A \rightarrow B)$ 
#### 分解：
$\qquad A \rightarrow B$ 的决定属性A不是超码，可分解为：  
$\qquad r_1(A,B),r_2(A,C,D)$  

