create database work
use work
/*创建以下两个关系模式，并分别插入相应的数据。*/
create table Worker(
职工号 varchar(10),
姓名 char(10),
年龄 int,
职务 char(15),
工资 int,
部门号 char(50)
)
create table Section (
部门号 char(10),
名称 char(10),
经理名 char(10),
地址 char(50),
电话 char(15)
)
--插入部门信息
insert into Section values('a001','市场部门','李永','白理工','13750000000');
insert into Section values('a002','营销部门','李刚','白理工','13750000000');
--插入职工信息
insert into Worker values('a001001','王明',20,'市场营销员',2000,'a001');
insert into Worker values('a001002','李村',29,'市场营销员',2000,'a001');
insert into Worker values('a001003','李永',20,'经理',5000,'a001');
insert into Worker values('a002001','罗杰',18,'销售员',2000,'a002');
insert into Worker values('a002002','李红',24,'销售员',2000,'a002');
insert into Worker values('a002003','李刚',32,'经理',5000,'a002');
--查询部门表和职工表的数据
select *from Worker;
select *from Section
--sp_adduser：可以理解为增加User，并给出密码
--和sp_grantdbaccess：理解为授予连接权限。
EXEC sp_addlogin '王明','123'
EXEC sp_grantdbaccess '王明'
EXEC sp_addlogin '李村','123'
EXEC sp_grantdbaccess '李村'
EXEC sp_addlogin '李永','123'
EXEC sp_grantdbaccess '李永'
EXEC sp_addlogin '罗杰','123'
EXEC sp_grantdbaccess '罗杰'
EXEC sp_addlogin '李红','123'
EXEC sp_grantdbaccess '李红'
EXEC sp_addlogin '李刚','123'
EXEC sp_grantdbaccess '李刚'
EXEC sp_addlogin '李勇','123'
EXEC sp_grantdbaccess '李勇'
EXEC sp_addlogin '刘星','123'
EXEC sp_grantdbaccess '刘星'
EXEC sp_addlogin '张新','123'
EXEC sp_grantdbaccess '张新'
EXEC sp_addlogin '周平','123'
EXEC sp_grantdbaccess '周平'
EXEC sp_addlogin '杨兰','123'
EXEC sp_grantdbaccess '杨兰'
/*（1）请用SQL的Grant和Revoke语句（加上视图机制）完成以下授权定义或存取控制功能，并进行相应的安全性测试；*/
/*（a）用户王明对两个表有select权力；*/
grant select on Worker to 王明
grant select on Section to 王明
/*（b）用户李勇对两个表有insert和delete权力；*/
grant insert,delete on Worker to 李勇
grant insert,delete on Section to 李勇
/*（c）每个职工只对自己的记录有select权力；*/
create view 职工 as select * from Worker where 姓名=user;
grant select on 职工 to public
/*（d）用户刘星对职工表有select权力，对工资字段具有更新权力；*/
GRANT SELECT,UPDATE(工资) ON Worker TO 刘星
/*（e）用户张新具有修改这两个表的结构的权力；*/
GRANT ALTER ON Worker TO 张新
GRANT ALTER ON Section TO 张新
/*（f）用户周平具有对两个表所有权力（对，插，改，删数据），并具有给其他用户授权的权利；*/
GRANT select,update,insert,delete ON Worker TO 周平 WITH GRANT OPTION
GRANT select,update,insert,delete ON Section TO 周平 WITH GRANT OPTION
/*（g）用户杨兰具有从每个部门职工中select最高工资，最低工资，平均工资的权力，他不能查看每个人的工资。*/
CREATE VIEW 部门工资 as select Section.名称,MAX(工资) as 最高工资,MIN(工资) as 最低工资,AVG(工资) as 平均工资
FROM Worker,Section WHERE Worker.部门号=Section.部门号 GROUP BY Section.名称
GRANT SELECT ON 部门工资 TO 杨兰
/*（2）把上面（a）～（g）的每一种情况，撤销各用户所授予的权力。*/ 
revoke select on Worker from 王明
revoke select on Section from 王明
revoke insert,delete on Worker from 李勇
revoke insert,delete on Section from 李勇
revoke select on 职工 from public
revoke SELECT,UPDATE(工资) ON Worker from 刘星
revoke ALTER ON Worker from 张新
revoke ALTER ON Section from 张新
revoke select,update,insert,delete ON Worker from 周平 CASCADE
revoke select,update,insert,delete ON Section from 周平 CASCADE
revoke SELECT ON 部门工资 from 杨兰