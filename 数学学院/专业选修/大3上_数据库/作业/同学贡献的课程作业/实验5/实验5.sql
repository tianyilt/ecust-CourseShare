Create database MT10162551
use MT10162551
create table department(
dept_no char(2) primary key,
dept_name char(10)
)
create table class(
class_no char(5) primary key,
class_name char(10) not null,
dept_no char(2),
FOREIGN KEY (dept_no) REFERENCES department(dept_no)
)
create table student(
s_no char(6) primary key,
s_name char(10) not null,
s_sex char(2) check (s_sex='男' or s_sex='女'),
s_birthday date,
s_score numeric(5,1) CHECK (s_score>=0 and s_score<=100),
s_addf numeric(3,1) CHECK (s_addf>=0 and s_addf<=30),
class_no char(5),
FOREIGN KEY (class_no) REFERENCES class(class_no)
)
create table course(
course_no char(5) primary key,
course_name char(20) not null
)
create table teacher(
t_no char(6) primary key,
t_name char(8) not null,
t_sex char(2) check (t_sex='男' or t_sex='女'),
t_birthday date,
teach_title char(10) check (teach_title in ('助教','讲师','副教授','教授'))
)
create table choice(
s_no char(6) ,
course_no char(5),
score numeric(5,1) CHECK (score>=0 and score<=100),
FOREIGN KEY (course_no) REFERENCES course(course_no),
FOREIGN KEY (s_no) REFERENCES student(s_no) on delete cascade,
primary key(s_no,course_no)
)
create table teaching(
t_no char(6),
course_no char(5),
FOREIGN KEY (course_no) REFERENCES course(course_no),
FOREIGN KEY (t_no) REFERENCES teacher(t_no) on delete cascade,
primary key(t_no,course_no)
)
insert into department values
('1','数学系'),
('2','物理系')
insert into class values
('001','数161','1'),
('002','数162','1'),
('003','信计160','1'),
('004','光电161','2'),
('005','光电162','2'),
('006','应物160','2')
insert into student values
('2001','王一','男','1998-02-10',100,30,'001'),
('2002','赵二','女','1998-09-01',80,30,'001'),
('2003','张三','男','1997-05-04',90,30,'003'),
('2004','李四','女','1999-08-05',70,30,'004')
insert into course values
('101','数据库'),
('102','数据结构'),
('103','数学分析')
insert into teacher values
('3001','昭红庆','男','1975-01-01','讲师'),
('3002','金永飞','男','1976-02-02','讲师')
insert into choice values
('2001','101',100),
('2002','101',75),
('2003','102',86),
('2004','103',61)
insert into teaching values
('3001','101'),
('3001','102'),
('3002','103')