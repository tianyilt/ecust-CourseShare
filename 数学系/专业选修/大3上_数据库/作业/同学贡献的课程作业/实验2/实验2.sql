/*1、 创建数据库,要求：创建了一个Employee数据库*/
create database Employee
use Employee
/*2,3、 创建表，要求：使用SQl语句创建一个雇员信息表person,一个月薪表salary和一个部门表department。*/
CREATE TABLE department
(Deptno char(4) not null primary key,--部门代码，主键
Dname varchar(10) not null--部门名称
);
CREATE TABLE person
(Pno char(6) not null primary key,--工人编号，主键
Pname varchar(10) not null,--姓名
Sex char(2) not null check(sex='男'or sex='女'),--性别
Birthday datetime,--出生日期
Prof varchar(10),--职称
Deptno char(4) not null,--部门代码
FOREIGN KEY(Deptno) REFERENCES department(Deptno),
CONSTRAINT sex_rule CHECK(Sex='男' OR Sex='女')
);
CREATE TABLE salary
(Pno char(6) not null,--工人编号
base dec(5) check(base>=300),--基本工资（要求base>=300）
Bonus dec(5) check(bonus>=50),--奖金（要求bonus>=50）
Fact as base+Bonus,--实发工资=基本工资+奖金
Month int not null,--月份
primary key(Pno,Month),--将Pno和Month设为主键
FOREIGN KEY(Pno) REFERENCES person(Pno)
);
/*7、 利用sql语句创建视图要求：在雇员信息表person基础上创建员工视图personview,其中包括工人编号，姓名，职称，性别和部门代码字段。*/
CREATE VIEW personview
as
SELECT Pno,Pname,Prof,Sex,Deptno from person
/*8、 为表创建索引
要求：
（1) 在出生日期和姓名列创建组合索引birth_name
（2) 在姓名列上创建一个唯一索引name_unique
（3) 在月薪表salary的Fact列上创建聚簇索引fact_idx
（4) 删除索引fact_idx。*/
CREATE UNIQUE INDEX birth_name ON person(Birthday,Pname);
CREATE UNIQUE INDEX name_unique ON person(Pname);
CREATE CLUSTERED INDEX fact_idx ON salary(fact);
DROP INDEX fact_idx ON salary;
alter table salary drop constraint PK__salary__EAD90B71CEC4E6A1
/*执行完第三条后要执行下面的命令 恢复主键，否则主键没了*/
ALTER TABLE salary
ADD PRIMARY KEY(Pno,Month)
/*（二）（1）向表中插入数据要求：按下表所示，向表person, salary, department中插入数据*/
INSERT INTO department values
('001','营销部'), 
('002','财务部'), 
('003','认识部'), 
('004','采购部') 
INSERT INTO person values 
('000001','田林','男','1982-4-7','初级','001'), 
('000002','郭达','男','1953-2-14','高级','001'), 
('000003','王琳','女','1984-8-25','初级','002'), 
('000004','王辉','男','1984-5-11','初级','002'), 
('000005','罗大佑','男','1968-12-10','高级','002'), 
('000006','蔡琴','女','1978-4-20','中级','003'), 
('000007','李艳','女','1960-5-14','高级','001'), 
('000008','刘德华','男','1971-2-19','高级','003'), 
('000009','黎明','男','1973-10-9','中级','002') 
INSERT INTO salary(Pno,base,bonus,Month)values
('000001',2100,500,1) ,
('000002',3000,600,1) ,
('000003',2800,450,1) ,
('000004',2500,340,1) ,
('000005',3200,490,1) ,
('000006',2700,600,1) ,
('000007',4000,200,1) ,
('000008',2800,350,1) ,
('000009',2760,400,1) ,
('000001',2400,600,2) ,
('000002',2800,400,2) ,
('000003',2860,350,2) ,
('000004',2540,320,2) ,
('000005',3200,480,2) ,
('000006',2700,300,2) ,
('000007',4000,250,2) ,
('000008',2800,300,2) ,
('000009',2760,480,2) ,
('000001',2200,500,3) ,
('000002',3100,400,3) ,
('000003',2800,650,3) ,
('000004',2500,540,3) ,
('000005',3200,400,3) ,
('000006',2700,680,3) ,
('000007',4100,400,3) ,
('000008',2000,330,3) ,
('000009',2760,420,3)
/*
（2）将职工编号为000006的员工3月份基本工资增加为3000，奖金增加到800。
（3）员工000009已经离开公司，将该员工的数据删除
（4）向视图persinview中插入一条记录（‘000011’，‘范伟’，‘男’，‘高级’，‘004’）
（5）将视图personview删除
*/
select * from salary 
UPDATE salary 
SET base='3000' 
WHERE Pno='000006' and Month='3' 
UPDATE salary 
SET bonus='800' 
WHERE Pno='000006' and Month='3'
DELETE salary 
WHERE Pno='000009' 
DELETE person 
WHERE Pno='000009' 
INSERT INTO personview 
VALUES('000011','范伟','高级','男','004') 
DROP VIEW personview
/*（6）简单条件查询
a.查询person表中所有不重复的职称。
b.查询具有高级职称的女员工信息
c.查询职工姓名为黎明的员工数据
d.查询各部门的实发工资总数
*/
SELECT Prof 
FROM person 
GROUP BY Prof
SELECT * 
FROM person 
WHERE Prof='高级' and Sex='女'
SELECT * 
FROM person 
WHERE Pname='黎明' 
SELECT Deptno,SUM(Fact) 
FROM salary,person 
WHERE salary.Pno=person.Pno 
GROUP BY Deptno 
/*（7）复杂条件查询
a.查询平均工资高于3000的部门名和对应的平均工资。
b.查询1月份实发工资比平均实发工资高的员工姓名和实发工资额。
c.查询2月份实发工资比一月高的员工姓名。
d.利用sql语句将1，2，3月累积的员工的实发工资按降序排序
*/
SELECT Deptno,AVG(Fact) 
FROM salary,person 
WHERE salary.Pno=person.Pno 
GROUP BY Deptno 
HAVING AVG(Fact)>=3000 
SELECT Pname,Fact 
FROM salary,person 
WHERE salary.Pno=person.Pno and salary.Month='1' 
and salary.Fact>(SELECT AVG(Fact)FROM salary) 
SELECT Pname,Fact 
FROM salary,person 
WHERE salary.Pno=person.Pno 
and salary.Month='2' 
and salary.Fact>( 
SELECT Fact 
FROM salary 
WHERE salary.Pno=person.Pno 
and salary.Month='1' 
) 
SELECT Pname,SUM(Fact) 
FROM salary,person 
WHERE salary.Pno=person.Pno 
GROUP BY Pname 
ORDER BY SUM(Fact) DESC
