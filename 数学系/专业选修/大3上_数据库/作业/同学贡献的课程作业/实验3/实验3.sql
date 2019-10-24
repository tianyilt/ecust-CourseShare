create database test
use test
/*1.用Create Table建表Exam*/
create table Exam
(
Id varchar(17),
Name varchar(10),
Sex varchar(2),
Age integer,
score numeric(6,2),
address varchar(50),
Memo varchar(100),
)
/*2.用Insert Into语句向Exam表中添加6条记录*/
insert into Exam values
('A0001','赵一','男',20,580.00,'宿舍-3-5','学习委员'),
('A0002','钱二','女',19,540.00,'南福苑-2-9','班长'),
('A0003','孙三','男',21,555.50,'学生新区-5-15','优秀共青团员'),
('A0004','李四','男',22,480.00,'宿舍-2-22','暂无相关信息'),
('A0005','周五','女',20,495.50,'学生新区-4-8','暂无相关信息'),
('A0006','吴六','男',19,435.00,'南福苑-5-12','暂无相关信息')
/*3.对表Exam的Score字段建立一个名为IndexScore的升序索引。*/
create index IndexScore on Exam(Score asc)
/*4.建立视图ViewExam，字段ViewExam1和ViewExam2分别对应表Exam的Name和Address字段。*/
create view ViewExam(ViewExam1,ViewExam2)
as
select Name,address
from Exam
/*5.某电信局计费部门*/
create table Jm(
Jmbm varchar(20) primary key,
Jmhz varchar(50),
Jmbz image,
)
create table Zjm(
Zjmbm varchar(20) primary key,
Zjmhz varchar(50),
Jmbm varchar(20),
Zjmbz image,
constraint c1 foreign key (Jmbm) references Jm(Jmbm)
)
create table Dhshow(
Dhh varchar(20),
Sl1 numeric(6,2),
Sl3 numeric(6,2),
Sl39 varchar(20),
Sl40 varchar(20),
constraint c2 foreign key (Sl40) references Zjm(Zjmbm)
)
insert into Jm values
('01','电信局1',null),
('02','电信局2',null),
('03','电信局3',null)
insert into Zjm values
('0001','电信局1子局1','01',null),
('0002','电信局1子局2','01',null),
('0003','电信局2子局1','02',null)
insert into Dhshow values
('123456789',2.03,1.24,'001','0001'),
('234567891',1.57,0.65,'001','0002'),
('345678912',1.78,0.99,'002','0001'),
('456789123',2.90,0.64,'002','0003'),
('567891234',2.90,10.94,'002','0001'),
('678912345',0,10.64,'003','0001'),
('789123456',5.23,10.64,'003','0002')
/*6．用SELECT语句，求某一地区长话消费平均是多少分人民币。*/
select Sl39 地区,AVG(Sl1) 长话费用
from Dhshow
group by Sl39 having Sl39='001'
/*7．用SELECT语句，求某一地区市话消费总额大于10分人民币并且长话消费不为零的电话号码。*/
select Sl39 地区,Dhh 电话号码
from Dhshow
where Sl3>10 and Sl1 !=0 and Sl39='003'
/*8．用SELECT语句，查询每一电话局各包含哪些子局？*/
select Jmbm, Zjmbm
from Zjm
/*9．用SELECT语句，查询每一子局的长话费总额？*/
select Sl40,sum(Sl1) sum
from Dhshow
group by Sl40
/*10．用SELECT语句，查询每一电话局的长话费总额？*/
create view D(sd,sum1)
as
select Sl40,sum(Sl1)
from Dhshow
group by Sl40

select Zjm.Jmbm '电信局编码',SUM(D.sum1) '电话局的长话费总额'
from D,Zjm
where D.sd=Zjm.Zjmbm
group by Zjm.Jmbm
