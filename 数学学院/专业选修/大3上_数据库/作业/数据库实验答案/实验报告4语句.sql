Create database xscj
use xscj
goCREATE TABLE xsqk(学号 CHAR(6) NOT NULL,姓名 CHAR(8) NOT NULL,性别 BIT NOT NULL DEFAULT 1,生日 SMALLDATETIME NOT NULL,专业 CHAR(10) NOT NULL,
所在系 CHAR(10) NOT NULL,
联系电话 CHAR(11),
总学分 TINYINT,
备注 TEXT,CONSTRAINT PK_XSQK_XH PRIMARY KEY(学号),CONSTRAINT UQ_XSQK_DH UNIQUE(姓名),CONSTRAINT CK_XSQK_XB CHECK(性别=1 or 性别=0),CONSTRAINT CK_XSQK_DH CHECK(联系电话 LIKE '[1-9][1-9][1-9][1-9][1-9][1-9]'),CONSTRAINT CK_XSQK_ZXF CHECK(总学分>=0 and 总学分<=200))goCREATE TABLE KC
(序号	INT IDENTITY,
课程号 CHAR(3) NOT NULL PRIMARY KEY(课程号),
课程名 CHAR(20) NOT NULL ,
授课教师 CHAR(8),
开课学期 TINYINT NOT NULL DEFAULT 1,
学时 TINYINT NOT NULL,
学分 TINYINT,
CONSTRAINT CK_KC_XQ CHECK(开课学期>=1 AND 开课学期<=6)
)
GO 

CREATE TABLE XS_KC
(学号 CHAR(6) NOT NULL REFERENCES XSQK(学号),
课程号 CHAR(3) NOT NULL,
成绩 TINYINT CHECK(成绩>=0 AND 成绩<=100),
学分 TINYINT,
PRIMARY KEY(学号,课程号),
FOREIGN KEY(课程号) REFERENCES KC(课程号)
)
GO

insert into xsqk values
('122315','渣渣辉',1,'1902-3-5','应用数学','数学系','626286',20,'天神'),
('154320','鸡儿舒',0,'1902-7-25','应用化学','化学系','218837',22,NULL),
('135825','鸡儿v舒',1,'1994-9-17','应用物理','物理系','243365',24,NULL),
('139093','dark舒',0,'1996-5-7','应用生物','生物系','987655',25,NULL),
('187146','fan舒',1,'1995-8-9','英语','英语系','154558',22,NULL)
go

insert into KC values
('001','哲学','鸡儿一舒',1,40,6),
('002','摔跤','鸡儿二舒',1,45,4),
('003','炉石传说','鸡儿三舒',3,36,5),
('004','XBOX','鸡儿四舒',4,41,5),
('101','0XFFFF','鸡儿五舒',5,40,5)
go

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
go

--汇总查询：
--a.在KC表中，统计每学期的总分数
select 开课学期,SUM(学分) as 总学分 
from KC
group by 开课学期
go
--b.在XS_KC表中统计每个学生的选修课程的门数select 学号,count(课程号) as 选修课程门数from XS_KCgroup by 学号go--c统计KC表中的总学分
select sum(学分) as 总学分
from KC


--d按开课学期统计KC表中各期的学分
select 开课学期,sum(学分) as 总学分
from KCgroup by 开课学期go--e.将XS_KC表中的数据记录按学号分类汇总，输出学号和平均分select 学号,AVG(成绩) as 平均分from XS_KCgroup by 学号go--d.查询平均分大于70且小于80的学生学号和平均分select 学号,avg(成绩) as 平均分from XS_KCgroup by 学号having AVG(成绩)>70 and AVG(成绩)<80go--e.查询XS_KC表，输出学号、课程号、成绩，并使查询结果首先按照课程号的升序排列，
-- 当课程号相同时再按照成绩降序排列，并将查询结果保存到新表TEMP_KC中
select 学号,课程号,成绩into TEMP_KCfrom XS_KCORDER BY 课程号 asc,成绩 descselect * from TEMP_KC--h.查询选修了“101”课程的学生的最高分和最低分select MAX(成绩) as 最高分,MIN(成绩) as 最低分from XS_KCgroup by 课程号having 课程号='101'--g.统计每个学期所开设的课程门数select 开课学期,count(课程号) as 课程门数from KCgroup by 开课学期go--h.查询各专业的学生人数select count(学号) as 学生人数,专业from xsqkgroup by 专业--------------------------连接查询和子查询


--a.查询不及格学生的学号、课程名、授课教师、开课学期的信息
select 学号,课程名,授课教师,开课学期
from KC,XS_KC
where 成绩<60 and KC.课程号=XS_KC.课程号

/*b.按学号分组汇总总分高于100的学生记录，并按总分的降序排列*/
SELECT   学号, SUM(成绩) AS 总分
FROM      XS_KC
GROUP BY 学号
HAVING   (SUM(成绩) > 100)
ORDER BY 总分 DESC



--c.使用子查询求恰好有两门课程不及格的学生信息
SELECT   学号, 姓名, 性别, 生日, 专业, 所在系, 联系电话, 总学分, 备注
FROM      xsqk
WHERE   (学号 IN
                    (SELECT   学号
                     FROM      XS_KC
                     GROUP BY 学号
                     HAVING   (COUNT(课程号) = 2)))

--d.使用子查询查询每门课程的最高分的学生记录
SELECT   a.学号, a.课程号, a.成绩, a.学分, xsqk.学号 AS Expr1, xsqk.姓名, xsqk.性别, xsqk.生日, xsqk.专业, xsqk.所在系, 
                xsqk.联系电话, xsqk.总学分, xsqk.备注
FROM      XS_KC AS a INNER JOIN
                xsqk ON a.学号 = xsqk.学号
WHERE   (a.成绩 =
                    (SELECT   MAX(成绩) AS Expr1
                     FROM      XS_KC AS b
                     WHERE   (a.学号 = 学号)))
ORDER BY a.课程号

--e.使用子查询查询每个学生的最低分的课

SELECT   学号, 课程号, 成绩, 学分
FROM      XS_KC AS a
WHERE   (成绩 =
                    (SELECT   MIN(成绩) AS Expr1
                     FROM      XS_KC AS b
                     WHERE   (a.学号 = 学号)))

