
/*创建数据库*/
 create database Lab3
 use Lab3
/*建表Exam*/

 CREATE TABLE Exam 
 (Id varchar(17) not null primary key,--学生编号
 Name varchar(10) not null,--姓名
 Sex varchar(2),--性别
 Age integer,--年龄 
 score numeric(6,2),--总成绩
 address varchar(50),--地址
 Memo varchar(100),--备注
 );

/*用Insert Into语句向Exam表中添加6条记录*/

Insert into Exam values
('A0001','赵一','男',20,580.00,'宿舍-3-5','学习委员'),
('A0002','钱二','女',19,540.00,'南福苑-2-9','班长'),
('A0003','孙三','男',21,555.50,'学生新区-5-15','优秀共青团员'),
('A0004','李四','男',22,480.00,'宿舍-2-22','暂无相关信息'),
('A0005','周五','女',20,495.50,'学生新区-4-8','暂无相关信息'),
('A0006','吴六','男',19,435.00,'南福苑-5-12','暂无相关信息')

/*对表Exam的Score字段建立一个名为IndexScore的升序索引*/
create index IndexScore on Exam(Score asc)

/*建立视图ViewExam，字段ViewExam1和ViewExam2分别对应表Exam的Name和Address字段。*/

create view ViewExam(ViewExam1,ViewExam2)
as
select Name,address
from Exam


/*建立jm表*/

create table Jm(
Jmbm varchar(20) primary key,
Jmhz varchar(50),
Jmbz image,
);



/*建立Zjm表*/

create table Zjm(
Zjmbm varchar(20) primary key,
Zjmhz varchar(50),
Jmbm varchar(20),
Zjmbz image,
constraint c1 foreign key (Jmbm) references Jm(Jmbm)/*表间关联：Jm表中的jmbm和zjm表中的jmbm是相等的；*/
)


/*建立Dhshow表*/

create table Dhshow(
Dhh varchar(20),
Sl1 numeric(6,2),
Sl3 numeric(6,2),
Sl39 varchar(20),
Sl40 varchar(20),
constraint c2 foreign key (Sl40) references Zjm(Zjmbm)/*Zjm表中的zjmbm和dhshow表中的sl40是相等的。*/
)






/*表说明：dhshow表中的sl1和sl3字段的计费单位是币人民分。*/

/*填入数据*/

insert into Jm values
('01','电信局1','搞事情'),
('02','电信局2','事情搞'),
('03','电信局3','事搞情')
insert into Zjm values
('0001','电信局1子局1','01','手榴弹'),
('0002','电信局1子局2','01','榴弹手'),
('0003','电信局2子局1','02','弹榴手')
insert into Dhshow values
('123456789',2.03,1.24,'001','0001'),
('234567891',1.57,0.65,'001','0002'),
('345678912',1.78,0.99,'002','0001'),
('456789123',2.90,0.64,'002','0003'),
('567891234',2.90,10.94,'002','0001'),
('678912345',0,10.64,'003','0001'),
('789123456',5.23,10.64,'003','0002')


/*用SELECT语句，求某一地区长话消费平均是多少分人民币。*/

SELECT   Sl39 AS 地区, AVG(Sl1) AS 长话费用
FROM      Dhshow
GROUP BY Sl39
HAVING   (Sl39 = '001')


/*用SELECT语句，求某一地区市话消费总额大于10元人民币并且长话消费不为零的电话号码。*/
SELECT   Sl39 AS 地区, Dhh AS 电话号码
FROM      Dhshow
WHERE   (Sl3 > 1000) AND (Sl1 <> 0) AND (Sl39 = '003')




/*用SELECT语句，查询每一电话局各包含哪些子局？*/

select Jmbm, Zjmbm
from Zjm



/*用SELECT语句，查询每一子局的长话费总额？*/
SELECT   Sl40, SUM(Sl1) AS sum
FROM      Dhshow
GROUP BY Sl40



/*用SELECT语句，查询每一电话局的长话费总额？*/


create view D(sd,sum1)
as
select Sl40,sum(Sl1)	
from Dhshow
group by Sl40


SELECT   Zjm.Jmbm AS '电信局编码', SUM(D.sum1) AS '电话局的长话费总额'
FROM      D CROSS JOIN
                Zjm
WHERE   (D.sd = Zjm.Zjmbm)
GROUP BY Zjm.Jmbm
