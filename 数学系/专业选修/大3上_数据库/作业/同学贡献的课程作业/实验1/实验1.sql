create database MT10162551
create table class(
class_no char(5) primary key,
class_name char(10) not null,
dept_no char(2)
)
create table department(
dept_no char(2) primary key,
dept_name char(10) not null
)
create table course(
course_no char(5) primary key,
course_name char(20) not null
)
create table teacher(
t_no char(6) primary key,
t_name char(8) not null,
t_sex char(2) check(t_sex='ÄÐ' or t_sex='Å®'),
t_birthday date,
teach_title char(10)
)
create table choise(
s_no char(6),
course_no char(5),
scorse numeric(5,1),
primary key(s_no,course_no)
)
create table teaching(
t_no char(6),
course_no char(5),
primary key(t_no,course_no)
)
alter table teaching alter column t_no smallint;
alter table teaching drop constraint PK__teaching__3D88B418A0E9793B;
alter table teaching alter column t_no smallint not null;
alter table teaching add constraint pk_main primary key(t_no,course_no)
drop table teaching
