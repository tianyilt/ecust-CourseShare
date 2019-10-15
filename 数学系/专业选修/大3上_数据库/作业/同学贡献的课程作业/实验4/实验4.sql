Create database xscj
use xscj
/*1） 在 xscj 数据库中分别创建学生情况表 xsqk， 课程表 kc， 学生与课程表 xs_kc*/
CREATE TABLE xsqk
(学号 CHAR(6) NOT NULL,
姓名 CHAR(8) NOT NULL,
性别 BIT NOT NULL DEFAULT 1,
生日 SMALLDATETIME NOT NULL,
专业 CHAR(10) NOT NULL,
所在系 CHAR(10) NOT NULL,
联系电话 CHAR(11),
总学分 TINYINT,
备注 TEXT,
CONSTRAINT PK_XSQK_XH PRIMARY KEY(学号),
CONSTRAINT UQ_XSQK_DH UNIQUE(姓名),
CONSTRAINT CK_XSQK_XB CHECK(性别=1 OR 性别=0),
CONSTRAINT CK_XSQK_DH CHECK (联系电话 LIKE '[1-9][1-9][1-9][1-9][1-9][1-9]'),
CONSTRAINT CK_XSQK_ZXF CHECK(总学分>=0 AND 总学分<=200)
)
CREATE TABLE KC
(序号 INT IDENTITY,
课程号 CHAR(3) NOT NULL PRIMARY KEY(课程号),
课程名 CHAR(20) NOT NULL ,
授课教师 CHAR(8),
开课学期 TINYINT NOT NULL DEFAULT 1,
学时 TINYINT NOT NULL,
学分 TINYINT,
CONSTRAINT CK_KC_XQ CHECK(开课学期>=1 AND 开课学期<=6)
)
CREATE TABLE XS_KC
(学号 CHAR(6) NOT NULL REFERENCES XSQK(学号),
课程号 CHAR(3) NOT NULL,
成绩 TINYINT CHECK(成绩>=0 AND 成绩<=100),
学分 TINYINT,
PRIMARY KEY(学号,课程号),
FOREIGN KEY(课程号) REFERENCES KC(课程号)
)
/*2）分别向xsqk,kc,xs_kc表中输入数据，其内容由用户自定义*/
insert into xsqk values
('122315','张一',1,'1997-3-5','应用数学','数学系','626286',20,'班长'),
('154320','李二',0,'1998-7-25','应用数学','数学系','218837',22,NULL),
('135825','王三',1,'1997-9-17','信息计算','数学系','243365',24,NULL),
('139093','孙四',0,'1998-5-7','应用物理','物理系','987655',25,NULL),
('187146','周五',1,'1999-8-9','光电材料','物理系','154558',22,'班长')
insert into KC values
('001','数学分析','金永飞',1,40,6),
('002','高等代数','章心发',1,45,4),
('003','大学英语','小天',3,36,5),
('004','数据结构','昭红庆',4,41,5),
('101','数据库','昭红庆',5,40,5)
insert into XS_KC values
('187146','002',40,5),
('122315','001',85,6),
('122315','002',90,4),
('154320','001',80,6),
('135825','003',86,5),
('139093','004',98,5),
('187146','003',78,5),
('187146','004',75,5),
('154320','101',90,5),
('135825','101',75,5),
('122315','101',80,5),
('122315','003',58,5),
('122315','004',56,5)
/*汇总查询：*/
/*a.在KC表中，统计每学期的总分数*/
select 开课学期,SUM(学分)as 总学分
from KC
group by 开课学期
/*b.在XS_KC表中统计每个学生的选修课程的门数*/
select 学号,count(课程号)as 选修的课程门数
from xs_kc
group by 学号
/*c.统计KC表中的总学分*/
select SUM(学分)
from KC
/*e.将XS_KC表中的数据记录按学号分类汇总，输出学号和平均分*/
select 学号,AVG(成绩)as 平均分
from XS_KC
group by 学号
/*f.查询平均分大于70且小于80的学生学号和平均分*/
select 学号,AVG(成绩)as 平均分
from XS_KC
group by 学号
having AVG(成绩)>70 and AVG(成绩)<80
/*g.查询XS_KC表，输出学号、课程号、成绩，并使查询结果首先按照课程号的升序排列，当课程号相同时再按照成绩降序排列，并将查询结果保存到新表TEMP_KC中*/
select 学号,课程号,成绩
into TEMP_KC
from xs_kc
order by 课程号 asc,成绩 desc
select * from TEMP_KC
/*h.查询选修了“101”课程的学生的最高分和最低分*/
select 课程号, MAX(成绩) 最高分, MIN(成绩) 最低分
from xs_kc
group by 课程号 having 课程号='101'
/*i.统计每个学期所开设的课程门数*/
select 开课学期,COUNT(课程号) 课程门数
from KC
group by 开课学期
/*j.查询各专业的学生人数*/
select 专业,COUNT(姓名) 学生数
from xsqk
group by 专业
/*连接查询和子查询*/
/*a.查询不及格学生的学号、课程名、授课教师、开课学期的信息*/
select 学号,课程名,授课教师,开课学期
from XS_KC,KC
where XS_KC.课程号=KC.课程号 and 成绩<60
/*b.按学号分组汇总总分高于100的学生记录，并按总分的降序排列*/
select 学号,SUM(成绩) 总成绩
from XS_KC
group by 学号
having SUM(成绩)>100
order by SUM(成绩)desc
/*c.使用子查询求恰好有两门课程不及格的学生信息*/
select *
from xsqk
where 学号 in (select 学号 from XS_KC where 成绩<60 group by 学号 having COUNT(课程号)=2 )
/*d.使用子查询查询每门课程的最高分的学生记录*/
select *
from xs_kc a,xsqk
where 成绩=(select max(成绩) from xs_kc b where a.学号=b.学号) and (a.学号=xsqk.学号)
/*e.使用子查询查询每个学生的最低分的课程记录*/
select * from xs_kc a
where 成绩=(select min(成绩) from xs_kc b where a.学号=b.学号)