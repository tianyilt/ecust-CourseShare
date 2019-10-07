create database lab3;

/*建立数据库*/
create table Exam
(
 Id Varchar(17) not null primary key, --学生编号
 Name Varchar(10) not null, --姓名
 Sex Char(2) Not null check(sex='男' or sex='女'), --性别
 Age Datetime null, --年龄
 Prof Varchar(10) null, --职称
 Deptno Char(4) not null,
 foreign key(Deptno) references department(Deptno),
);
