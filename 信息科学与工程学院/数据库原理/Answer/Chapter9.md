# Chapter9
## 9.9
(2)
```SQL
GRANT all ON Course TO user01 WITH GRANT OPTION
```
(4)
```SQL
GRANT select, delete ON Course TO user03
```
(5)
```SQL
GRANT all ON Course TO user04 WITH GRANT OPTION
```
(8)
```SQL
REVOKE select, delete ON Course FROM user05 CASCADE
--级联收回--
```
(9)
```SQL
REVOKE all ON Course FROM user02
```
