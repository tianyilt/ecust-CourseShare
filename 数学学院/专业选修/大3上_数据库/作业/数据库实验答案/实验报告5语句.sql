create database MT10172911
use MT10172911

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
('1','银河系'),
('2','天马系')

insert into class values
('001','机枪','1'),
('002','光剑','1'),
('003','托派','1'),
('004','术巨','2'),
('005','苦力','2'),
('006','西格','2')

insert into student values
('1001','鸡儿舒','男','1999-01-28',100,30,'002'),
('1002','真的舒','男','1999-02-28',80,30,'002'),
('1003','比较舒','男','1999-03-28',80,30,'002')

insert into course values
('101','犯憨分析'),
('102','孕愁学')

insert into teacher values
('3001','朱怡然','男','1997-01-01','教授')


insert into choice values
('1001','102',100),
('1002','102',100),
('1003','102',100)

insert into teaching values
('3001','102')

