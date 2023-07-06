# Chapter2
## 2.1
### 2.1.2
**超码**：对于关系r的一个或多个属性的集合A，如果属性集A可以唯一地标识关系中的一个元组，则称属性集A为关系r的一个超码。  

**候选码**：如果属性集A是关系r的超码，且属性集A的任意真子集都不能成为关系r的超码，则称属性集A为候选码。   

**主码**：若一个关系r有一个或多个候选码，则选定其中一个作为该关系的主码。  

**外码**：设F是关系r的一个属性(或属性集)，$K_s$ 是关系s的主码。如果F与$K_s$ 相对应，则称F是关系r参照关系s的外码，简称F是关系r的外码。

### 2.1.3
**关系**：关系模型的数据结构(二维表)  
**关系模式**：对于关系的描述，形式化地表示为$$r(U,D,DOM,F)$$
**关系数据库**：在一个给定地应用领域中，所有实体以及实体之间地联系所对应的关系的集合就构成了一个关系数据库。

## 2.3
完整性规则：实体完整性，参照完整性，用户自定义完整性

## 2.6
自然连接是一种特殊的等值连接，要求两个参与连接的关系具有公共的属性集，即R $\cap$ S $\neq$ $\varnothing$，并在这个公共属性集上进行等值连接；同时，要求公共属性集中的列只保留一次。

## 2.8
（2）查找2000年元旦以后出生的全体男同学。  
$$\sigma_{year(birthday)>=2000 \wedge sex='男'}(Student)$$  
（4）查找16172学期开出课程的编号、名称和学分。
$$\Pi_{courseNo,courseName,creditHour}(\sigma_{term='16172'}(Score \Join Course))$$
（6）查找班级名为"会计学15(3)"的学生在15161学期的选课情况，显示学生姓名、课程号、课程名称和成绩。
$$\Pi_{studentName,courseNo,courseName,score}(\sigma_{className='会计学15(3)'}(Class \Join Student \Join \sigma_{term='15161'}Score \Join Course))$$

## 2.9
（1）查找2016级蒙古族学生信息，包括学号、姓名、性别和所属班级。
$$\Pi_{studentNo,studentName,sex,classNo}(\sigma_{grade='2016 \wedge nation='蒙古族'}(Class \Join Student))$$

（3）查找选修了以“计算机概论”为其直接先修课的课程的学生学号、课程号和成绩。
$$\Pi_{studentNo, courseNo, score}(\sigma_{priorCourse='计算机概论'}(Student \Join SC \Join Course))$$

（5） 查找信息学校学生选课情况，要求显示学生姓名、课程号、课程名、开课班号、成绩和任课老师。
$$\Pi_{studentName, courseNo, courseName, cClassNo, score, teacherName}(\sigma_{instituteName='信息学院'}(Institute \Join Class \Join Student \Join SC \Join Course \Join CourseClass \Join Teacher))$$