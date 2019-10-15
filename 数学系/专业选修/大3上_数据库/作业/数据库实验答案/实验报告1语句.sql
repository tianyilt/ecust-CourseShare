Create database MT10172912;
Use MT10172912;

Create table  class
(
	class_no char(5) primary key,
	class_name char(10) not null,
	dept_no char(2)
)

Create table department
(
	dept_no char(2) primary key,
	dept_name char(10) not null
)

Create table course
(
	course_no char(5) primary key,
	course_name char(20) not null
)

Create table teacher
(
	t_no char(6) primary key,
	t_name char(8) not null,
	t_sex char(2) check(t_sex='男' or t_sex='女'),
	t_birthday date,
	tech_title char(10)
)

Create table choice
(
	s_no char(6),
	course_no char(5),
	scorse numeric(5,1),
	primary key(s_no,course_no)
)

Create table teaching
(
	t_no char(6),
	course_no char(5),
	primary key(t_no,course_no)
)

Alter table teaching drop constraint PK__teaching__3D88B418B97608AC; --PK__teaching__3D88B418B97608AC每个机器不同，可以通过直接运行Alter table teaching alter column t_no smallint;来查看返回错误信息来确定
Alter table teaching alter column t_no smallint;
Alter table teaching add constraint t_no primary key(t_no,course_no);

Drop table teaching;